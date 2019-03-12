/*******************************************************************************
 *           Getting Jiggy with Boost.Proto - Boost'Con 2011 Tutorial
 *                                 by Joel Falcou
 *
 *                      Step 1 : Putting Expressions to Work
 *
 *             Distributed under the Boost Software License, Version 1.0.
 *                    See accompanying file LICENSE.txt or copy at
 *                       http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#include <cmath>
#include <iostream>
#include <boost/array.hpp>
#include <boost/proto/proto.hpp>

/*******************************************************************************
 * Our small analytical function EDSL starts to flesh out. It handles up to
 * three variables and classical operators. We can check if a given expression
 * is correctly formed and evaluates it. Now, what if we want to extend our
 * EDSL by adding new functions ? In this part fo the tutorial, we will introduce
 * make_expr and its wonders.
 ******************************************************************************/

/*******************************************************************************
 * We'll add cos and sin functions to our system and have them maps to call of
 * std::cos and std::sin. This works require two steps:
 *  - defining a new node in our AST and build th efunction to create it
 *  - add a way to evaluate it.
 ******************************************************************************/

/*******************************************************************************
 * First we defines small structs to represent the nodes.
 ******************************************************************************/
struct cos_tag {};
struct sin_tag {};

/*******************************************************************************
 * We also defines an evaluation point for these so we can wrap std::cos and
 * std::sin in a callable transform. We use a technique I foudn quite
 * interesting as extensibility goes: we tie the transform to the node tag and
 * specialize away.
 *
 * This invalidate the "inherits from proto::callable" and require a full blown
 * proto::is_callable specialization.
 ******************************************************************************/
template<typename Tag, typename Dummy=void>
struct compute
{};

template<typename Dummy>
struct compute<cos_tag,Dummy>
{
  typedef double result_type;

  template<class T> inline
  result_type operator()(T const& t) const
  {
    return std::cos(static_cast<double>(t));
  }
};

template<typename Dummy>
struct compute<sin_tag,Dummy>
{
  typedef double result_type;

  template<class T> inline
  result_type operator()(T const& t) const
  {
    return std::sin(static_cast<double>(t));
  }
};

namespace boost { namespace proto
{
  template<typename Tag, typename Dummy>
  struct is_callable< compute<Tag,Dummy> > : boost::mpl::true_ {};
} }

/*******************************************************************************
 * We now use make_expr to build a template cos and sin function that emits
 * the appropriate node
 ******************************************************************************/
template<typename Arg0> inline
typename boost::proto::result_of::
make_expr < cos_tag     // The node tag
          , Arg0 const& // keep the ndoe by cref
          >::type
cos( Arg0 const& arg0 )
{
  return boost::proto::make_expr<cos_tag>( boost::cref(arg0) );
}

template<typename Arg0> inline
typename boost::proto::result_of::
make_expr < sin_tag     // The node tag
          , Arg0 const& // keep the ndoe by cref
          >::type
sin( Arg0 const& arg0 )
{
  return boost::proto::make_expr<sin_tag>( boost::cref(arg0) );
}
/*******************************************************************************
 * We upgrade our grammar to allow the new node as unary expressions.
 * Bonus style point: wrap them in small template class to make them look like
 * proto grammar elements
 ******************************************************************************/
template<typename I> struct variable_tag : I {};

template<typename Grammar>
struct cos_ : boost::proto::unary_expr<cos_tag,Grammar> {};

template<typename Grammar>
struct sin_ : boost::proto::unary_expr<sin_tag,Grammar> {};

struct  analytical_function
      : boost::proto::or_
        <
        boost::proto::terminal< variable_tag<boost::proto::_> >
        , boost::proto::or_
          < boost::proto::terminal< int >
          , boost::proto::terminal< float >
          , boost::proto::terminal< double >
          >
        , cos_<analytical_function>
        , sin_<analytical_function>
        , boost::proto::or_
          < boost::proto::plus<analytical_function,analytical_function>
          , boost::proto::negate<analytical_function>
          , boost::proto::minus<analytical_function,analytical_function>
          , boost::proto::multiplies<analytical_function,analytical_function>
          , boost::proto::divides<analytical_function,analytical_function>
          >
        >
{};

/*******************************************************************************
 * We now upgrade our evaluation trasnform to handle the new node.
 * Note how we recursively call evaluate_ to process the inenr working of
 * cos_ and sin_.
 ******************************************************************************/

struct fetch_variable : boost::proto::callable
{
  template<typename Sig> struct result;

  template<typename This,typename Index,typename Vars>
  struct result<This(Index,Vars)>
  {
    typedef typename boost::remove_reference<Vars>::type  base;
    typedef typename base::const_reference                type;
  };

  template<class Index, class Vars> inline
  typename result<fetch_variable(Index,Vars)>::type
  operator()(Index const&, Vars const& v) const
  {
    return v[Index::value];
  }
};

struct  evaluate_
      : boost::proto::or_
        <
          boost::proto::when
          < boost::proto::terminal< variable_tag<boost::proto::_> >
          , fetch_variable(boost::proto::_value,boost::proto::_state)
          >
        , boost::proto::when
          < boost::proto::terminal< boost::proto::_ >
          , boost::proto::_value
          >
        , boost::proto::when
          < cos_< boost::proto::_ >
          , compute<cos_tag>(evaluate_(boost::proto::_child0))
          >
        , boost::proto::when
          < sin_< boost::proto::_ >
          , compute<sin_tag>(evaluate_(boost::proto::_child0))
          >
        , boost::proto::otherwise< boost::proto::_default<evaluate_> >
        >
{};

/*******************************************************************************
 * We keep our expression code around
 ******************************************************************************/
template<typename AST>
struct analytical_expression;

struct  analytical_domain
      : boost::proto::domain< boost::proto::generator<analytical_expression>
                            , analytical_function
                            >
{};

/*******************************************************************************
 * We keep analytical_expression the same
 ******************************************************************************/
template<typename AST>
struct  analytical_expression
      : boost::proto::extends<AST,analytical_expression<AST>,analytical_domain>
{
  typedef boost::proto::
          extends<AST,analytical_expression<AST>,analytical_domain> extendee;

  /*******************************************************************************
   * Expression must be constructible from an AST
  ******************************************************************************/
  analytical_expression(AST const& ast = AST()) : extendee(ast) {}

  BOOST_PROTO_EXTENDS_USING_ASSIGN(analytical_expression)

  typedef double result_type;

  result_type operator()(double v0) const
  {
    boost::array<double,1> that = {{v0}};
    evaluate_ callee;
    return callee(*this,that);
  }

  result_type operator()(double v0,double v1) const
  {
    boost::array<double,2> that = {{v0,v1}};
    evaluate_ callee;
    return callee(*this,that);
  }

  result_type operator()(double v0,double v1,double v2) const
  {
    boost::array<double,3> that = {{v0,v1,v2}};
    evaluate_ callee;
    return callee(*this,that);
  }
};

/*******************************************************************************
 * Same with the variable placeholders
 ******************************************************************************/
analytical_expression< boost::proto::terminal< variable_tag<boost::mpl::int_<0> > >::type > const _x;
analytical_expression< boost::proto::terminal< variable_tag<boost::mpl::int_<1> > >::type > const _y;
analytical_expression< boost::proto::terminal< variable_tag<boost::mpl::int_<2> > >::type > const _z;

/*******************************************************************************
 * Now test our analytical function computation systems
 ******************************************************************************/

int main()
{
  std::cout << (cos(_x*3.14159))(0.25) << "\n";
  std::cout << (cos(_x)*cos(_x) + sin(_x)*sin(_x))(1.23456) << "\n";
  std::cout << (_x/_y)(4.,3.) << "\n";

}

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

/*
 * TODO : Add small struct reprenseting cos and sin nodes in AST
 */

/*******************************************************************************
 * We also defines an evaluation point for these so we can wrap std::cos and
 * std::sin in a callable transform. We use a technique I foudn quite
 * interesting as extensibility goes: we tie the transform to the node tag and
 * specialize away.
 *
 * This invalidate the "inherits from proto::callable" and require a full blown
 * proto::is_callable specialization.
 ******************************************************************************/

/*
 * TODO : Add a compute callable onject computing sin and cos.
 */

/*******************************************************************************
 * We now use make_expr to build a template cos and sin function that emits
 * the appropriate node. make_expr documentation is at:
 * http://tinyurl.com/make-expr
 ******************************************************************************/

/*
 * TODO : Use make_expr to make our own sin and cos template function
 */

/*******************************************************************************
 * We upgrade our grammar to allow the new node as unary expressions.
 * Bonus style point: wrap them in small template class to make them look like
 * proto grammar elements
 ******************************************************************************/
template<typename I> struct variable_tag : I {};

/*
 * TODO : Update the grammar to accept cos and sin nodes
 */

struct  analytical_function
      : boost::proto::or_
        <
        boost::proto::terminal< variable_tag<boost::proto::_> >
        , boost::proto::or_
          < boost::proto::terminal< int >
          , boost::proto::terminal< float >
          , boost::proto::terminal< double >
          >
        , boost::proto::plus<analytical_function,analytical_function>
        , boost::proto::negate<analytical_function>
        , boost::proto::minus<analytical_function,analytical_function>
        , boost::proto::multiplies<analytical_function,analytical_function>
        , boost::proto::divides<analytical_function,analytical_function>
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

/*
 * TODO : Update the transform to accept cos and sin nodes and forward to the
 * computation callable object
 */

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
  /*
   * TODO : Test sin and cos
   */

}

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
#include <iostream>
#include <boost/array.hpp>
#include <boost/proto/proto.hpp>

/*******************************************************************************
 * So far so good, we have now a new expression class controlled by our grammar.
 * Next step is to do actual *computations* with all of these
 ******************************************************************************/

/*******************************************************************************
 * We'll first change the way we handle terminals. As we want now to handle
 * variables and be able to manipualte their value, we change the definition of
 * our terminals. We bring back a new grammar here and defines new terminals.
 ******************************************************************************/
template<typename I> struct variable_tag : I {};

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
 * We now build a Transform.
 * A Transform is a Calalble Object defined in the very same way than a Proto
 * grammar. Transform rules can be extended with a semantic action that will
 * describe what happens when a given rule is matched.
 *
 * Proto offers a lot of default transform, and we'll actually use them.
 *
 * So what happens when we encounter a node in our analytical function :
 *   - if it's a terminal, we want to extarct the corresponding value
 *   - if it's an operator , we want it to do what the C++ operators does
 ******************************************************************************/

/*******************************************************************************
 * To do so, we need to build a small helping function object to handle the
 * terminal case.
 ******************************************************************************/

/*******************************************************************************
 * We pass variable as a boost::array and use the terminal index to fetch it
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

/*******************************************************************************
 * We write our transform. To do so, we'll exploit the default transform of
 * proto and our newly written helpers.
 * Note the use of proto::when that associates a rule to its action.
 ******************************************************************************/
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
 * And we now add the required code to support feeding the value of our
 * variable to our transform
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

  /***************************************************************************
   * Provides the 3 operator() overloads and amke it a Callable Object while
   * we are at it. To do our bidding, we'll fill a proper boost::array and pass
   * it to an instance of our transform.
   **************************************************************************/
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
 * Last step, we have to redefine _x to be an analytical_expression and we
 * add its little brother _y and _z. Look at th euse of the MPL Integral
 * to pass the variable index into the soon-to-be array.
 ******************************************************************************/
analytical_expression< boost::proto::terminal< variable_tag<boost::mpl::int_<0> > >::type > const _x;
analytical_expression< boost::proto::terminal< variable_tag<boost::mpl::int_<1> > >::type > const _y;
analytical_expression< boost::proto::terminal< variable_tag<boost::mpl::int_<2> > >::type > const _z;

/*******************************************************************************
 * Now test our analytical function computation systems
 ******************************************************************************/

int main()
{
  std::cout << (_x*3 + 1./_y)(2,0.1) << "\n";
}

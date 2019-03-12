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
#include "grammar.hpp"

/*******************************************************************************
 * We now build a Transform.
 * A Transform is a Callable Object defined in the very same way than a Proto
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
 * We write our transform. To do so, we'll exploit the default transform of
 * proto and our newly written helpers.
 * Note the use of proto::when that associates a rule to its action.
 *
 * Documentation on transform is available at:
 * http://tinyurl.com/proto-transform
 ******************************************************************************/
struct  evaluate_
/*
 * TODO : Complete the transform definition
 */
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
   * Provides the operator() overload and make it a Callable Object while
   * we are at it.
   **************************************************************************/
  typedef double result_type;

  result_type operator()(double v0) const
  {
    /*
     * TODO : Complete the operator implementation
     */
  }
};

/*******************************************************************************
 * Last step, we have to redefine _x to be an analytical_expression
 ******************************************************************************/
analytical_expression< boost::proto::terminal< variable_tag >::type > const _x;

/*******************************************************************************
 * Now test our analytical function computation systems
 ******************************************************************************/

int main()
{
  /*
   * TODO : Test the computation
   */
}

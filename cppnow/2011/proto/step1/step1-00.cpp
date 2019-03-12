/*******************************************************************************
 *           Getting Jiggy with Boost.Proto - Boost'Con 2011 Tutorial
 *                                 by Joel Falcou
 *
 *                 Step 1 : Putting Expressions to Work
 *
 *             Distributed under the Boost Software License, Version 1.0.
 *                    See accompanying file LICENSE.txt or copy at
 *                       http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#include <iostream>
#include <boost/proto/proto.hpp>

/*******************************************************************************
 * Our small AST are now controlled by a Grammar that validates their behavior
 * with respect to what we want them to do. Next step will now make these
 * AST works like real calculator.
 ******************************************************************************/

/*******************************************************************************
 * First step is to turn the AST into an Expression. The thin separation between
 * each fo these terms is the following :  an AST represents a structure of
 * code, an Expression has a semantic.
 *
 * This difference is represented in Proto by the notion of **extension**.
 * AST can be **EXTENDED** to provide domain specific interface and perform
 * tasks after being built.
 ******************************************************************************/

/*******************************************************************************
 * We moved all the code from the Introduction to various headers we include here
 ******************************************************************************/
#include "grammar.hpp"

/*******************************************************************************
 * The extension mechanism of Proto expression rely on elements:
 *  - a Grammar that describes the valid expression of our EDSL
 *  - an Expression class that will provide the specific interface we look for
 *  - a Domain class that will tie the Grammar and the Expression type via
 *    a Generator
 *
 * We already have a Grammar, so we need to define our Expression and bind it
 * using a Domain.
 ******************************************************************************/

/*******************************************************************************
 * First we define the Domain that will tie our (currentl forward declared)
 * Expression type to our grammar.
 *
 * The documentation about Domain and Generator is located at
 * http://tinyurl.com/proto-domain
 *
 ******************************************************************************/
template<typename AST>
struct analytical_expression;

/*
 * TODO: Create a class analytical_domain that bounds analytical_expression to
 * the analytical_function grammar.
 */

/*******************************************************************************
 * Once done, we can build our analytical_expression class and give it our
 * interface. We want to be able to call operator() on our analytical formula
 * to evaluate them at a given set of variable.
 *
 * The documentation about Extension is located at
 * http://tinyurl.com/proto-extends
 *
 ******************************************************************************/

/*
 * TODO: Complete analytical_expression to be tied to its Domain and to provide
 * a now empty set of operator()
 */
template<typename AST>
struct analytical_expression
{
  // Some methods
};

/*******************************************************************************
 * Last step, we have to redefine _x to be an analytical_expression
 ******************************************************************************/

/*
 * TODO: Modify x_ definition to match analytical_expression
 */

/*******************************************************************************
 * Great ! Now we can still build expressions like before following the same
 * set of rules defined in the analytical_function grammar and call operator()
 * on them. Next step, makign this operator() do something useful :o
 ******************************************************************************/

int main()
{
  /*
   * TODO: Test if your new expression still pass the check_for_match
   */
}

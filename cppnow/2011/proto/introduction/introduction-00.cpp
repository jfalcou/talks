/*******************************************************************************
 *           Getting Jiggy with Boost.Proto - Boost'Con 2011 Tutorial
 *                                 by Joel Falcou
 *
 *                 Introduction : Building Expressions with proto
 *
 *             Distributed under the Boost Software License, Version 1.0.
 *                    See accompanying file LICENSE.txt or copy at
 *                       http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#include <iostream>
#include <boost/proto/proto.hpp>

/*******************************************************************************
 *  This first step will demonstrate how proto can without any effort produce
 *  a compile-time representation of a given statement involving proto terminals
 ******************************************************************************/

/*******************************************************************************
 * The main process in building an template-based Abstract Syntax Tree with
 * proto is to defines so-called terminal types that will acts as 'seed' for
 * our AST to be build. As soon as a proto object takes part in an expression,
 * the whole expression will be captured as a proto AST.
 ******************************************************************************/

/*******************************************************************************
 * This empty structure will be used as a mark-up to discriminate our terminals
 ******************************************************************************/
struct variable_tag {};

/*******************************************************************************
 * We now build our instance of a proto terminal type.
 * Note :
 *  - how we use variable_tag as a mark-up inside boost::proto terminal
 *  - the fact that _x is constructed as a POD (the infamous {{}})
 ******************************************************************************/
boost::proto::terminal< variable_tag >::type const _x = {{}};

/*******************************************************************************
 * Done ! Our very first proto terminal is now ready to use. It can't do much
 * for the moment but we'll play with it already.
 ******************************************************************************/

int main()
{
  /*****************************************************************************
   * We can build any kind of expression involving _x and any existing C++
   * operators. Note that none of these expression actually do something
   * except for capturing the AST structure.
   ****************************************************************************/
  _x %= _x + 3 * ~(_x >> 6);

  /*****************************************************************************
   * We can actually look at the underlying tree structure of such expressions
   * using the handy boost::proto::display_expr function.
   ****************************************************************************/
  boost::proto::display_expr( _x %= _x + 3 * ~(_x >> 6) );
}

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
#ifndef GRAMMAR_HPP_INCLUDED
#define GRAMMAR_HPP_INCLUDED

#include <boost/proto/proto.hpp>

/*******************************************************************************
 * Terminal type discriminator here
 ******************************************************************************/
struct variable_tag {};

/*******************************************************************************
 * We define what we want to have as valid element of our analytical
 * functions:
 *  - we want our variable
 *  - or any arihmetic values
 *  - or one of the classical computation operators: +, both -, * and /
 ******************************************************************************/
struct  analytical_function
        // The grammar is defined as a series of alternatives, this is done
        // using boost::proto::or which allows the enumeration of valid
        // grammar elements
      : boost::proto::or_
        <
        // we want our variable
        boost::proto::terminal< variable_tag >
        // or any arihmetic values
        , boost::proto::or_
          < boost::proto::terminal< int >
          , boost::proto::terminal< float >
          , boost::proto::terminal< double >
          >
        // or one of the classical computation operators:
        // +
        , boost::proto::plus<analytical_function,analytical_function>
        // both - (unary and binary one)
        , boost::proto::negate<analytical_function>
        , boost::proto::minus<analytical_function,analytical_function>
        // *
        , boost::proto::multiplies<analytical_function,analytical_function>
        // /
        , boost::proto::divides<analytical_function,analytical_function>
        >
{};

/*******************************************************************************
 * Helper function to check if a given expression matches a given grammar
 ******************************************************************************/
template<class Expression> inline void
check_for_match( Expression const& xpr )
{
  boost::proto::display_expr(xpr);

  // The meta-check
  std::cout
      << ( boost::proto::matches<Expression, analytical_function>::value
         ? "matches " : "doesn't match "
         )
      << "the analytical_function grammar\n\n";
}
#endif

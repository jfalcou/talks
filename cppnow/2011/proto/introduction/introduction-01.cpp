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
 * We are now able to builds proto AST by usign proto terminals and operators.
 * However, as demonstrated in the previous file, these ASTs don't do anything
 * more than looking pretty and having an interesting type. We're now going to
 * imbue these ASTs with actual meaning.
 ******************************************************************************/

/*******************************************************************************
 * To do so, we'll define a set of rules that will define the accepted syntax
 * of our function evaluation EDSL. This is done using a GRAMMAR
 ******************************************************************************/

/*******************************************************************************
 * We still have our terminal type discriminator here
 ******************************************************************************/
struct variable_tag {};

/*******************************************************************************
 * We know define what we want to have as valid element of our analytical
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
 * Note how the various proto element describing the operator are trivially
 * named and constructed. Note also the recursion in said operators definition.
 * This grammar is basically a copy-cat of the following BNF grammar :
 *
 * analytical_function ::= 'variable'
 *                       | 'arithmetic value'
 *                       | analytical_function + analytical_function
 *                       | -analytical_function
 *                       | analytical_function - analytical_function
 *                       | analytical_function * analytical_function
 *                       | analytical_function / analytical_function
 *
 * One last thing, note as we didn't have to define any operator precedence
 * relations. All proto overloaded operators follow the natural rules of
 * their C++ counter-part. Keep this in mind when you devise your grammar.
 ******************************************************************************/

/*******************************************************************************
 * As before, we build our little _x
 ******************************************************************************/
boost::proto::terminal< variable_tag >::type const _x = {{}};

/*******************************************************************************
 * Done ! Now we can actually verify that our proto AST conforms to our wishes
 *
 * We still can build any kind of expression involving _x and any existing C++
 * operators. But now we can statically check if this AST is conforming to our
 * grammar defined earlier. This is done using the 'match' meta-function or
 * the BOOST_PROTO_ASSERT_MATCHES/_NOT macros as shown below
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

int main()
{
  check_for_match( -(_x/2.f) + 3*_x );
  check_for_match( _x + ~_x*_x << "lol" );
}

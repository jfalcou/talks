/*******************************************************************************
 *           Getting Jiggy with Boost.Proto - Boost'Con 2011 Tutorial
 *                                 by Joel Falcou
 *
 *                             Step 2 : Transformers !
 *
 *             Distributed under the Boost Software License, Version 1.0.
 *                    See accompanying file LICENSE.txt or copy at
 *                       http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef CONSTANT_HPP_INCLUDED
#define CONSTANT_HPP_INCLUDED

struct constant_tag {};

template<int N>
struct  constant_grammar
      : boost::proto::nullary_expr< constant_tag
                                  , boost::mpl::int_<N>
                                  >
{};

struct  any_constant_grammar
      : boost::proto::nullary_expr< constant_tag
                                  , boost::proto::_
                                  >
{};

template<int N>
struct  constant_
      : analytical_expression<typename constant_grammar<N>::type>
{};

template<>
struct analytical_function_cases::case_< constant_tag > : any_constant_grammar
{};

template<>
struct    evaluate_cases
        ::case_< constant_tag >
        : boost::proto::when<any_constant_grammar, boost::proto::_value>
{};

#endif

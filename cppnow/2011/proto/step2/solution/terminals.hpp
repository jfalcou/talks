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
#ifndef TERMINALS_HPP_INCLUDED
#define TERMINALS_HPP_INCLUDED

#include <boost/proto/proto.hpp>
#include "grammar.hpp"
#include "expression.hpp"
#include "evaluate.hpp"

/*******************************************************************************
 * Variable placeholders
 ******************************************************************************/
struct variable_tag {};

template<class  N>
struct  nth_var
      : boost::proto::nullary_expr< variable_tag, N >
{};

/*******************************************************************************
 * Switch based Grammar - Variable case
 * Note how the fact to have used nullary_expr allow clean separation from the
 * consatnt case ;)
 ******************************************************************************/
template<>
struct    analytical_function_cases
        ::case_< variable_tag >
        : boost::proto::nullary_expr< variable_tag, boost::proto::_ >
{};

analytical_expression< nth_var< boost::mpl::int_<0> >::type > const _x;
analytical_expression< nth_var< boost::mpl::int_<1> >::type > const _y;
analytical_expression< nth_var< boost::mpl::int_<2> >::type > const _z;

/*******************************************************************************
 * Switch based Transform - Variable case
 ******************************************************************************/
template<>
struct    evaluate_cases
        ::case_< variable_tag >
        : boost::proto::when
          < boost::proto::nullary_expr< variable_tag, boost::proto::_ >
          , fetch_variable(boost::proto::_value,boost::proto::_state)
          >
{};

#endif

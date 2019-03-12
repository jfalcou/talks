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
#ifndef GRAMMAR_HPP_INCLUDED
#define GRAMMAR_HPP_INCLUDED

#include <boost/proto/proto.hpp>

/*******************************************************************************
 * Switch based Grammar cases
 ******************************************************************************/
struct  analytical_function_cases
{
  // The primary template matches nothing:
  template<typename Tag>
  struct case_ : boost::proto::not_<boost::proto::_> {};
};

/*******************************************************************************
 * Switch based Grammar
 ******************************************************************************/
struct  analytical_function
: boost::proto::switch_< analytical_function_cases >
{};

/*******************************************************************************
 * Switch based Grammar - Constant case
 * We use more refined if_ and and_ to check any type convertible to double
 ******************************************************************************/
template<>
struct    analytical_function_cases
        ::case_<boost::proto::tag::terminal>
        : boost::proto::and_
          < boost::proto::terminal< boost::proto::_ >
          , boost::proto::if_< boost::is_convertible< double
                                                    , boost::proto::_value
                                                    >()
                             >
          >
{};

/*******************************************************************************
 * Switch based Grammar - Operator cases
 ******************************************************************************/
template<>
struct    analytical_function_cases
        ::case_< boost::proto::tag::negate >
        : boost::proto::negate<analytical_function>
{};

template<>
struct    analytical_function_cases
        ::case_< boost::proto::tag::plus >
        : boost::proto::plus<analytical_function,analytical_function>
{};

template<>
struct    analytical_function_cases
        ::case_<boost::proto::tag::minus >
        : boost::proto::minus<analytical_function,analytical_function>
{};

template<>
struct    analytical_function_cases
        ::case_<boost::proto::tag::multiplies>
        : boost::proto::multiplies<analytical_function,analytical_function>
{};

template<>
struct    analytical_function_cases
        ::case_<boost::proto::tag::divides>
        : boost::proto::divides<analytical_function,analytical_function>
{};

#endif

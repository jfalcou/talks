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
#ifndef FUNCTIONS_HPP_INCLUDED
#define FUNCTIONS_HPP_INCLUDED

#include <cmath>
#include <boost/proto/proto.hpp>
#include "grammar.hpp"
#include "evaluate.hpp"

struct cos_tag {};
struct sin_tag {};

template<typename Tag, typename Dummy=void>
struct compute
{};

template<typename Dummy>
struct compute<cos_tag,Dummy>
{
  typedef double result_type;

  template<class T> inline
  result_type operator()(T const& t) const
  {
    return std::cos(static_cast<double>(t));
  }
};

template<typename Dummy>
struct compute<sin_tag,Dummy>
{
  typedef double result_type;

  template<class T> inline
  result_type operator()(T const& t) const
  {
    return std::sin(static_cast<double>(t));
  }
};

namespace boost { namespace proto
{
  template<typename Tag, typename Dummy>
  struct is_callable< compute<Tag,Dummy> > : boost::mpl::true_ {};
} }

template<typename Arg0> inline
typename boost::proto::result_of::
make_expr < cos_tag     // The node tag
          , Arg0 const& // keep the node by cref
          >::type
cos( Arg0 const& arg0 )
{
  return boost::proto::make_expr<cos_tag>( boost::cref(arg0) );
}

template<typename Arg0> inline
typename boost::proto::result_of::
make_expr < sin_tag     // The node tag
          , Arg0 const& // keep the node by cref
          >::type
sin( Arg0 const& arg0 )
{
  return boost::proto::make_expr<sin_tag>( boost::cref(arg0) );
}

/*******************************************************************************
 * Switch based Grammar - sin/cos cases
 ******************************************************************************/
template<>
struct    analytical_function_cases
        ::case_<cos_tag>
        : boost::proto::unary_expr<cos_tag,analytical_function>
{};

template<>
struct    analytical_function_cases
        ::case_<sin_tag>
        : boost::proto::unary_expr<sin_tag,analytical_function>
{};

/*******************************************************************************
 * Switch based evaluate_ transform - sin/cos cases
 ******************************************************************************/
template<>
struct    evaluate_cases
        ::case_<cos_tag>
        : boost::proto::when
          < boost::proto::unary_expr<cos_tag,analytical_function>
          , compute<cos_tag>(evaluate_(boost::proto::_child0))
          >
{};

template<>
struct    evaluate_cases
        ::case_<sin_tag>
        : boost::proto::when
          < boost::proto::unary_expr<sin_tag,analytical_function>
          , compute<sin_tag>(evaluate_(boost::proto::_child0))
          >
{};
#endif

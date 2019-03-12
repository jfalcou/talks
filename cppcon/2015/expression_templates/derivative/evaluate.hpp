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
#ifndef EVALUATE_HPP_INCLUDED
#define EVALUATE_HPP_INCLUDED

#include <boost/proto/proto.hpp>

/*******************************************************************************
 * Evaluator for variable terminal
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
 * Switch based evaluate_ cases
 ******************************************************************************/
struct  evaluate_;

struct  evaluate_cases
{
  // The primary template goes for the _default:
  template<typename Tag>
  struct case_ : boost::proto::_default<evaluate_> {};
};

/*******************************************************************************
 * Switch based Grammar
 ******************************************************************************/
struct  evaluate_ : boost::proto::switch_< evaluate_cases > {};

/*******************************************************************************
 * Switch based Grammar - Constant case
 * We use more refined if_ and and_ to check any type convertible to double
 ******************************************************************************/
template<>
struct    evaluate_cases
        ::case_<boost::proto::tag::terminal>
        : boost::proto::when
          < boost::proto::and_
            < boost::proto::terminal< boost::proto::_ >
            , boost::proto::if_< boost::is_convertible< double
                                                      , boost::proto::_value
                                                      >()
                               >
            >
          , boost::proto::_value
          >
{};

#endif

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
#ifndef DERIVATE_HPP_INCLUDED
#define DERIVATE_HPP_INCLUDED

#include "simplify.hpp"

/*******************************************************************************
 * Switch based derivate_ cases
 ******************************************************************************/
struct  derivate_cases
{
  // The primary template matches nothing
  template<typename Tag>
  struct case_ : boost::proto::not_<boost::proto::_> {};
};

/*******************************************************************************
 * Switch based derivate_ Transform
 ******************************************************************************/
struct  derivate_ : boost::proto::switch_< derivate_cases > {};

template<>
struct    derivate_cases
        ::case_<boost::proto::tag::terminal>
        : boost::proto::when
          < boost::proto::and_
            < boost::proto::terminal< boost::proto::_ >
            , boost::proto::if_< boost::is_convertible< double
                                                      , boost::proto::_value
                                                      >()
                               >
            >
          , constant_<0>()
          >
{};

template<>
struct    derivate_cases
        ::case_<constant_tag>
        : boost::proto::when
          < boost::proto::nullary_expr< constant_tag, boost::proto::_ >
          , constant_<0>()
          >
{};

template<>
struct    derivate_cases
        ::case_< variable_tag >
        : boost::proto::when
          < boost::proto::nullary_expr< variable_tag, boost::proto::_ >
          , boost::proto::if_
            < boost::is_same< boost::proto::_value
                            , boost::proto::_value(boost::proto::_state)
                            >()
            , constant_<1>()
            , constant_<0>()
            >
          >
{};

template<>
struct    derivate_cases
        ::case_< boost::proto::tag::negate >
        : boost::proto::when
          < boost::proto::negate< derivate_cases >
          , simplify_ ( boost::proto::functional
                        ::make_negate( derivate_(boost::proto::_child0) )
                      )
          >
{};

template<>
struct    derivate_cases
        ::case_< boost::proto::tag::plus >
        : boost::proto::when
          < boost::proto::plus< derivate_cases, derivate_cases >
          , simplify_ ( boost::proto::functional::make_plus
                        ( derivate_(boost::proto::_left)
                        , derivate_(boost::proto::_right)
                        )
                      )
          >
{};

template<>
struct    derivate_cases
        ::case_< boost::proto::tag::minus >
        : boost::proto::when
          < boost::proto::minus< derivate_cases, derivate_cases >
          , simplify_ ( boost::proto::functional::make_minus
                        ( derivate_(boost::proto::_left)
                        , derivate_(boost::proto::_right)
                        )
                      )
          >
{};

template<>
struct    derivate_cases
        ::case_< boost::proto::tag::multiplies >
        : boost::proto::when
          < boost::proto::multiplies< derivate_cases, derivate_cases >
          , simplify_ ( boost::proto::functional::make_plus
                        ( boost::proto::functional::make_multiplies
                          ( boost::proto::_left
                          , derivate_(boost::proto::_right)
                          )
                        , boost::proto::functional::make_multiplies
                          ( derivate_(boost::proto::_left)
                          , boost::proto::_right
                          )
                        )
                      )
          >
{};

template<>
struct    derivate_cases
        ::case_< boost::proto::tag::divides >
        : boost::proto::when
          < boost::proto::divides< derivate_cases, derivate_cases >
          , simplify_ ( boost::proto::functional::make_divides
                        ( boost::proto::functional::make_minus
                            ( boost::proto::functional::make_multiplies
                              ( boost::proto::_left
                              , derivate_(boost::proto::_right)
                              )
                            , boost::proto::functional::make_multiplies
                              ( derivate_(boost::proto::_left)
                              , boost::proto::_right
                              )
                            )
                        , boost::proto::functional::make_multiplies
                          ( boost::proto::_right
                          , boost::proto::_right
                          )
                        )
                      )
          >
{};

template<>
struct    derivate_cases
        ::case_< cos_tag >
        : boost::proto::when
          < boost::proto::unary_expr< cos_tag, derivate_cases >
          , simplify_ ( boost::proto::functional::make_multiplies
                        ( derivate_(boost::proto::_child0)
                        , boost::proto::functional::make_negate
                          (
                            boost::proto::functional::make_expr<sin_tag>
                            (
                              boost::proto::_child0
                            )
                          )
                        )
                      )
          >
{};

template<>
struct    derivate_cases
        ::case_< sin_tag >
        : boost::proto::when
          < boost::proto::unary_expr< sin_tag, derivate_cases >
          ,simplify_ ( boost::proto::functional::make_multiplies
                      ( derivate_(boost::proto::_child0)
                      , boost::proto::functional::make_expr<cos_tag>
                        (
                          boost::proto::_child0
                        )
                      )
                    )
          >
{};


template<int N>
struct nth_derivative
{
  template<typename Sig> struct result;

  template<typename This,typename F, typename V>
  struct  result<This(F,V)>
  {
    typedef typename boost::result_of<derivate_(F, V)>::type              base;
    typedef typename boost::result_of<nth_derivative<N-1>(base const&, V)>::type type;
  };

  template<typename F, typename V> inline
  typename result<nth_derivative<N>(F const&, V const&)>::type
  operator()( F const& f, V const& v ) const
  {
    nth_derivative<N-1> rec;
    derivate_           callee;
    return rec(callee(f,v),v);
  }
};

template<>
struct nth_derivative<1>
{
  template<typename Sig> struct result;

  template<typename This,typename F, typename V>
  struct  result<This(F,V)> : boost::result_of<derivate_(F, V)>
  {};

  template<typename F, typename V> inline
  typename result<nth_derivative<1>(F const&, V const&)>::type
  operator()( F const& f, V const& v ) const
  {
    derivate_ callee;
    return callee(f,v);
  }
};


template<int Degree,typename Function, typename Variable> inline
typename boost::result_of
	<simplify_(typename boost::result_of<nth_derivative<Degree>(Function const&
                                                                   , Variable const&
                                                                   )>::type const&
                  )
        >::type
derivate( Function const& f, Variable const& v )
{
  nth_derivative<Degree> callee;
  return simplify(callee(f,v));
}

template<typename Function, typename Variable> inline
typename boost::result_of
        <simplify_(typename boost::result_of<derivate_( Function const&
                                                      , Variable const&
                                                      )>::type const&
                  )
        >::type
derivate( Function const& f, Variable const& v )
{
  derivate_ callee;
  return simplify(callee(f,v));
}

#endif

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
#ifndef SIMPLIFY_HPP_INCLUDED
#define SIMPLIFY_HPP_INCLUDED

/*******************************************************************************
 * Switch based simplify_ cases
 ******************************************************************************/
struct  simplify_cases
{
  // The primary template matches nothing
  template<typename Tag>
  struct case_ : boost::proto::_ {};
};

/*******************************************************************************
 * Switch based simplify_ Transform
 ******************************************************************************/
struct  simplify_ : boost::proto::switch_< simplify_cases > {};

template<>
struct    simplify_cases
        ::case_< boost::proto::tag::divides >
        : boost::proto::or_<  boost::proto::when
                              < boost::proto::divides < simplify_
                                                      , constant_grammar<1>
                                                      >
                              , simplify_(boost::proto::_left)
                              >
                          , boost::proto::when
                            < boost::proto::divides < simplify_
                                                    , simplify_
                                                    >
                            , boost::proto::functional::make_divides
                              ( simplify_(boost::proto::_left)
                              , simplify_(boost::proto::_right)
                              )
                            >
                          >
{};
template<class A, class B>
struct constant_mul : constant_<A::value*B::value>
{};

template<>
struct    simplify_cases
        ::case_< boost::proto::tag::multiplies >
        : boost::proto::or_<  boost::proto::when
                              < boost::proto::multiplies< simplify_
                                                        , constant_grammar<1>
                                                        >
                              , simplify_(boost::proto::_left)
                              >
                            , boost::proto::when
                              < boost::proto::multiplies< any_constant_grammar
                                                        , any_constant_grammar
                                                        >
                              , constant_mul< boost::proto::_value(boost::proto::_left)
                                            , boost::proto::_value(boost::proto::_right)
                                            >()
                              >

                            , boost::proto::when
                              < boost::proto::multiplies< constant_grammar<1>
                                                        , simplify_
                                                        >
                              , simplify_(boost::proto::_right)
                              >
                            , boost::proto::when
                              < boost::proto::multiplies< simplify_
                                                        , constant_grammar<0>
                                                        >
                              , constant_<0>()
                              >
                            , boost::proto::when
                              < boost::proto::multiplies< constant_grammar<0>
                                                        , simplify_
                                                        >
                              , constant_<0>()
                              >
                            , boost::proto::when
                              < boost::proto::multiplies< simplify_
                                                        , simplify_
                                                        >
                              , boost::proto::functional::make_multiplies
                                ( simplify_(boost::proto::_left)
                                , simplify_(boost::proto::_right)
                                )
                              >

                            >
{};

template<>
struct    simplify_cases
        ::case_< boost::proto::tag::minus >
        : boost::proto::or_<  boost::proto::when
                              < boost::proto::minus < simplify_
                                                    , constant_grammar<0>
                                                    >
                              , simplify_(boost::proto::_left)
                              >
                            , boost::proto::when
                              < boost::proto::minus < constant_grammar<0>
                                                    , simplify_
                                                    >
                              , boost::proto::functional::make_negate
                                (
                                  simplify_(boost::proto::_right)
                                )
                              >
                            , boost::proto::when
                              < boost::proto::minus < simplify_
                                                    , simplify_
                                                    >
                              , boost::proto::functional::make_minus
                                ( simplify_(boost::proto::_left)
                                , simplify_(boost::proto::_right)
                                )
                              >
                            >
{};

template<class A, class B>
struct constant_add : constant_<A::value+B::value>
{};

template<>
struct    simplify_cases
        ::case_< boost::proto::tag::plus >
        : boost::proto::or_<  boost::proto::when
                              < boost::proto::plus< simplify_
                                                  , constant_grammar<0>
                                                  >
                              , simplify_(boost::proto::_left)
                              >
                            , boost::proto::when
                              < boost::proto::plus< any_constant_grammar
                                                  , any_constant_grammar
                                                  >
                              , constant_add< boost::proto::_value(boost::proto::_left)
                                            , boost::proto::_value(boost::proto::_right)
                                            >()
                              >
                            , boost::proto::when
                              < boost::proto::plus< constant_grammar<0>
                                                  , simplify_
                                                  >
                              , simplify_(boost::proto::_right)
                              >
                            , boost::proto::when
                              < boost::proto::plus
                                < boost::proto::multiplies< any_constant_grammar
                                                          , nth_var<boost::proto::_>
                                                          >
                                , boost::proto::multiplies< any_constant_grammar
                                                          , nth_var<boost::proto::_>
                                                          >
                                >
                              , boost::proto
                                ::if_ < boost::is_same
                                        < boost::proto::_value(boost::proto::_right(boost::proto::_left))
                                        , boost::proto::_value(boost::proto::_right(boost::proto::_right))
                                        >()
                                      , boost::proto::functional::make_multiplies
                                        ( constant_add< boost::proto::_value(boost::proto::_left(boost::proto::_left))
                                                      , boost::proto::_value(boost::proto::_left(boost::proto::_right))
                                                      >()
                                        , boost::proto::_right(boost::proto::_right)
                                        )
                                      , boost::proto::functional::make_plus
                                        ( simplify_(boost::proto::_left)
                                        , simplify_(boost::proto::_right)
                                        )
                                      >
                              >
                            , boost::proto::when
                              < boost::proto::plus< simplify_
                                                  , simplify_
                                                  >
                              , boost::proto::functional::make_plus
                                ( simplify_(boost::proto::_left)
                                , simplify_(boost::proto::_right)
                                )
                              >
                            >
{};

template<typename Function> inline
typename boost::result_of<simplify_(Function const&)>::type
simplify( Function const& f )
{
  simplify_ callee;
  return callee(f);
}

#endif

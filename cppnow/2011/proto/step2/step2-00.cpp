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

#include <iostream>
#include "functions.hpp"
#include "terminals.hpp"

/*******************************************************************************
 * our EDSL has now been refurbished and split into convenient files.
 *
 * Your task is this final settings is to define trasnforms and functions to be
 * able to compute, at compile-time, the analytical derivatives of any of our
 * analytical functions.
 *
 * Here is a plan on how to tackle this:
 *  - take a piece of paper and think about these derivation rules learned in
 *  high school. How do they relate to the original functions ? Can you spot
 *  why we dont need anythine more than a trasnform ?
 *  - There is special cases in derivatives rules. What are they and how can we
 *  capture them ?
 *  - All in all, what are we needing as a basic proto trasnform ?
 *  - Now, what's a Nth degree derivative ? Do we need extra work ?
 *  - Same question for partial derivatives ? What do we need ?
 *
 *  The following hour or so is here for you to think about these questions and
 *  try to answer them and implement something usign Proto.
 *
 *  Don't forget to tests corner cases and see for yourself :)
 ******************************************************************************/

int main()
{
}

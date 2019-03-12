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
#include "constant.hpp"
#include "derivate.hpp"
#include "simplify.hpp"

int main()
{
  boost::proto::display_expr(_x*_x*_x*(_y*_x));
  std::cout << "\n";

  boost::proto::display_expr(derivate<4>( _x*_x*_x*(_y*_x), _x ));
  std::cout << "\n";
 
  boost::proto::display_expr(simplify(derivate<4>( _x*_x*_x*(_y*_x), _x )));
  std::cout << "\n";

  std::cout << derivate( _y * _x, _x )(10,3)        << "\n";
  std::cout << derivate( (_x-1) * (_x+1), _x )(10)  << "\n";
  std::cout << derivate( 1/_x, _x )(10)             << "\n";
  std::cout << derivate( cos(_x), _x )(3.14159/2)   << "\n";
  std::cout << derivate<2>( _x*_x*_x*_x, _x )(10)   << "\n";
  std::cout << derivate<4>( cos(_x), _x )(0)        << "\n";
  std::cout << derivate( cos(_x*_y) + _z*sin(_z-_y), _x )(1,1,1)        << "\n";
  std::cout << derivate( cos(_x*_y) + _z*sin(_z-_y), _y )(1,1,1)        << "\n";
  std::cout << derivate( cos(_x*_y) + _z*sin(_z-_y), _z )(1,1,1)        << "\n";
}

#include <iostream>
#include <string>
#include <memory>

int main()
{
  // u est move-only
  auto u = std::make_unique<std::string>( "*", 10 );  

  // copie u dans la lambda
  auto ko = [u] { std::cout << *u << "\n"; }; 

  // reference u dans la lambda
  auto okish = [&u] { std::cout << *u << "\n"; }; 

  // move u dans la lambda
  auto ok = [ u{std::move(u)} ] { std::cout << *u << "\n"; }; 
}

// Courtesy of Vittorio Romero
// https://vittorioromeo.info/index/blog/cpp20_lambdas_compiletime_for.html
#include <iostream>
#include <utility>

template <auto... Xs, typename F>
constexpr void for_values(F&& f)
{
  (f.template operator()<Xs>(), ...);
}

template <auto B, auto E, typename F>
constexpr void for_range(F&& f)
{
  using t = std::common_type_t<decltype(B), decltype(E)>;

  [&f]<auto... Xs>(std::integer_sequence<t, Xs...>)
  {
    for_values<(B + Xs)...>(f);
  } (std::make_integer_sequence<t, E - B>{});
}

int main()
{
  for_range<(-5), 5>([]<auto X>()
  {
    std::cout << X << ' ';
  });
}


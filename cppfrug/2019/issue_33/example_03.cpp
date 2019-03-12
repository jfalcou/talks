// Courtesy of Björn Fahller
#include <utility>
#include <typeinfo>

template <char ...> class S {};

template <class F, std::size_t ... I>
auto S_(F f, std::index_sequence<I...>)
{
  return S<f(I)...>{};
}

#define str(x) S_([](auto i){return x[i];}, std::make_index_sequence<sizeof(x)>{});

auto s = str("foo");
auto n = typeid(s).name();

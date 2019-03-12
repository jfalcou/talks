// Courtesy of Vittorio Romero
// https://vittorioromeo.info/index/blog/cpp20_lambdas_compiletime_for.html
#include <array>

template <typename... Ts, typename F>
constexpr void for_types(F&& f)
{
    (f.template operator()<Ts>(), ...);
}

template <typename... Ts>
constexpr int size_of()
{
    int r = 0;
    for_types<Ts...>([&]<typename T>(){ r += sizeof(T); });
    return r;
}

std::array<char,size_of<int,char,char,double,void*>()> block;

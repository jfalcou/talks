#include <cstddef>
#include <utility>

template<class... Ts> 
struct aggregate_bindings : Ts... 
{ 
    aggregate_bindings(Ts... t) noexcept : Ts(t)... {} 
    using Ts::operator()...; 

    template<typename K> constexpr auto operator()(K const& k) const noexcept
    {
        return k;
    }
};

template<class... Ts> 
aggregate_bindings(Ts...) -> aggregate_bindings<Ts...>;

template<typename T> struct box {};

template<typename Key, typename Value>
constexpr auto bind(Value const& v) noexcept 
{
  return [v](box<Key> const&)  { return v; };
}

template<typename Key, typename Value>
auto bind(Value& v) noexcept
{
  return [&v](box<Key> const&) -> decltype(auto) { return v; };
}

template<int N>
struct var_t
{ 
  template<typename T>
  constexpr auto operator=(T&& v) const noexcept { return bind<var_t>(std::forward<T>(v)); }   
};

var_t<0> const x_ = {};
var_t<1> const y_ = {};
var_t<2> const z_ = {};

template<typename Storage>
struct type_map
{
  template<typename K>
  decltype(auto) operator[](K const&) const
  {
    return storage(box<K>{});
  }

  template<typename K>
  decltype(auto) operator[](K const&)
  {
    return storage(box<K>{});
  }

  Storage storage;
};

template<typename... Things>
constexpr auto make_type_map(Things const&... ts) noexcept
{
  using s_t = decltype(aggregate_bindings(ts...));
  return type_map<s_t>{aggregate_bindings(ts...)};
}

auto bidibulle()
{
  int uv; 
  auto u = make_type_map( x_ = uv, y_ = "test");

  u[x_] = 96;
 
 return u[y_][0] + uv;
}


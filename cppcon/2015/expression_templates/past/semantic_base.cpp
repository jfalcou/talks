#include <iostream>

template <typename Derived>
struct base_expr
{
  Derived const& self() const { return static_cast<const Derived&>(*this); }
  auto operator()() const { return self()(); }

  using value_type = decltype(std::declval<Derived>()());
  operator value_type() const  { return self()(); }
};

template<typename Tag, typename A>
struct unary_expr : public base_expr<unary_expr<Tag, A>>
{
  explicit unary_expr(const A& a) : ca(a) {}

  auto operator()() const { return op(ca()); }

  private:
  A ca;
  Tag op;
};

template<typename Tag, typename A, typename B>
struct binary_expr : public base_expr<binary_expr<Tag, A, B>>
{
  binary_expr(const A& a, const B& b) : ca(a), cb(b) {}

  auto operator()() const { return op(ca(), cb()); }

  private:
  A ca;
  B cb;
  Tag op;
};

template<typename Value>
struct terminal : public base_expr<terminal<Value>>
{
  terminal() = default;
  explicit terminal(const Value& a) : v(a) {}

  template<typename X>
  terminal operator=( base_expr<X> const& x )
  {
    v = x();
    return *this;
  }

  auto operator()() const { return v; }

  private:
  Value v;
};

struct plus_
{
  template<typename T, typename U> auto operator()(T const& t, U const& u) const { return t+u; }
};

struct times_
{
  template<typename T, typename U> auto operator()(T const& t, U const& u) const { return t+u; }
};

template <typename E1, typename E2>
auto operator+(base_expr<E1> const& e1, base_expr<E2> const& e2)
{
  return binary_expr<plus_,E1, E2>{e1.self(), e2.self()};
}

template <typename E1, typename E2>
auto operator*(base_expr<E1> const& e1, base_expr<E2> const& e2)
{
  return binary_expr<times_, E1, E2>{e1.self(), e2.self()};
}


int main()
{
  auto d = terminal<int>{4};

  terminal<float> u;
  u = d*d+d*d;
  std::cout << float(u);
}

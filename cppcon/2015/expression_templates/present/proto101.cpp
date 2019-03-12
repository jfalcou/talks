#include <boost/proto/proto.hpp>

boost::proto::terminal<int>::type x;

int main()
{
  auto u = x*x+x-3/~x;
  boost::proto::display_expr(u);
}

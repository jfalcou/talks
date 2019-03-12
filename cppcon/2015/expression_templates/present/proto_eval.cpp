#include <boost/proto/proto.hpp>

using boost::proto::_;
using boost::proto::or_;
using boost::proto::when;
using boost::proto::_value;
using boost::proto::otherwise;
using boost::proto::_default;
using boost::proto::terminal;

struct eval  : boost::proto::or_< when<terminal<_>,_value>
                                , otherwise< _default<eval> >
                                >
{};

int main()
{
  terminal<int>::type x{2};

  eval e;
  std::cout << e(x+x*x+3) << "\n";
}

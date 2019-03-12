#include <boost/proto/proto.hpp>

using boost::proto::_;
using boost::proto::or_;
using boost::proto::when;
using boost::proto::plus;
using boost::proto::_value;
using boost::proto::_left;
using boost::proto::_right;
using boost::proto::otherwise;
using boost::proto::_default;
using boost::proto::terminal;

struct custom : boost::proto::callable
{
  using result_type = double;

  template<typename T, typename U>
  result_type operator()(T const& t, U const& u) const
  {
     return (t+u)*100;
  }
};

struct eval  : boost::proto::or_< when<terminal<_>,_value>
                                , when< plus<eval,eval>, custom(eval(_left),eval(_right))>
                                , otherwise< _default<eval> >
                                >
{};

int main()
{
  terminal<int>::type x{2};

  eval e;
  std::cout << e((x+3)+(x*3)) << "\n";
}

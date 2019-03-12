#include <iomanip>
#include <iostream>
#include <boost/proto/proto.hpp>

using boost::proto::_;
using boost::proto::or_;
using boost::proto::plus;
using boost::proto::terminal;
using boost::proto::multiplies;

struct epa  : boost::proto::or_ < terminal<_>
                                , plus<epa,epa>
                                , multiplies<epa,epa>
                                >
{};

int main()
{
  terminal<int>::type x{2};

  std::cout << std::boolalpha << boost::proto::matches<decltype(x+x) , epa>::value << "\n";
  std::cout << std::boolalpha << boost::proto::matches<decltype(x/!x), epa>::value << "\n";
}

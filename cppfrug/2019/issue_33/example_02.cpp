// Courtesey of Markus Werle
#include <iterator>
#include <vector>

auto first = [](auto i)
{
  auto getN = [=](auto const& s)
  {
    auto b = std::begin(s);
    decltype(s) result{b, std::next(b,i)};
    return result;
  };
  return getN;
};

std::vector<int> v{1,2,4,8,16,32};
auto sub = first(3)(v);

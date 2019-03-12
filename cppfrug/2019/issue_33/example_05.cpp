// Courtesy of Serge Guelton
#include <type_traits>

#include <list>
#include <vector>
#include <array>
#include <iostream>
#include <algorithm>

auto visitor = [](auto value, auto op) {

    auto rec = [&op](auto self, auto &value) {
        if constexpr(std::is_scalar_v<std::decay_t<decltype(value)>>) {
            op(value);
        }
        else {
            std::for_each(std::begin(value), std::end(value),
                          [&self](auto & elt) { self(self, elt); } );
        }
    };

    rec(rec, value);
};

int main(int argc, char**argv) {
    std::list<std::vector<std::array<int, 4>>> some {
        {{0,1,2,3}, {4,5, 6, 7}},
        {}
    };
    visitor(some, [](auto &v) { v = -v; });
    std::cout << some.back().back().back()  << std::endl;
}

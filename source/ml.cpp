#if 0
python gen_parser.py
# g++ -std=c++11 -Wall -Wextra -pedantic -O1 ml.cpp -o ml_gcc $@ &&\
#     strip ml_gcc &&\
#     ./ml_gcc
# clang++ -std=c++11 -Wall -Wextra -pedantic -O1 ml.cpp -o ml_clang $@ &&\
#     strip ml_clang &&\
#     ./ml_clang
clang++ -std=c++11 -stdlib=libc++ -Wall -Wextra -pedantic -O1 ml.cpp -o ml_clang $@ &&\
    strip ml_clang &&\
    ./ml_clang
exit
#endif

#include <iostream>

#include "mylang_util.hpp"

using namespace mylang;

void test() {
    std::string s = "1 * (2 + y*-3 > sin 30)";
    Input sbegin = s.cbegin();
    auto x = Parser<MP_STR("expression", 10)>::parse(sbegin, s.cend());
    auto x1 = Parser<>::parse(s);

    std::cout << x->getTree() << std::endl;
    std::cout << x1->getTree() << std::endl;

    std::cout << x->getTree(2, 2) << std::endl;
    std::cout << x1->getTree(3, 0) << std::endl;
    std::cout << x1->getTree(0, 3) << std::endl;

    Pass<0> p1;
    x->runPass(&p1);

    delete x;
    delete x1;
}

int main() {
    test();

    return 0;
}

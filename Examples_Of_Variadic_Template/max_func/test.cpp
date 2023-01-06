#include "max.hpp"
#include <iostream>

int main() {
    std::cout << init_args::max({9,100,36,0,62,6666}) << std::endl;
    std::cout << vari_template_parameter::max(6,100,9,9999,0) << std::endl;
}
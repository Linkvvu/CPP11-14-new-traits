/**
 * @file override_print.cpp
 * @brief 利用可变模板参数,实现 "C" printf
 * @version 0.1
 * @date 2022-11-14
 * @reference 侯捷
 * @copyright Copyright (c) 2022
 * 
 */
#include <iostream>
#include <exception>
void print(const char* c) {
    while (*c) {
        if (*c == '%' && *(++c) != '%') {
            throw std::runtime_error("invalid format string : missing arguments");
        }
        std::cout << *c++;
    }
}

template<typename T, typename... PACK>
void print(const char* c, T cur, PACK... another) {
    while (*c) {
        if (*c == '%' && *(++c) != '%') {
            std::cout << cur;
            print(++c, another...);
            return;
        }
        else {
            std::cout << *c++;
        }
    }
    throw std::logic_error("extra arguments provided to print");
}


int main() {
    print("%d sb %f\\ end!", 5, 2.6);
    const char* p = "dshk";
}
#include <iostream>

class Str {
public:
    Str() {std::cout << "default constructor\n";}
    Str(const int& d) : data(d) {}
    Str(const Str& s) {
        data = s.data;
        std::cout << "Copy constructor\n";
    }
    Str(Str&& s) {std::cout << "Move constructor\n";}

private:
    int data = 0;
};

template<typename T>
void print(T& t) {
    std::cout << "Lvalue ref.\n";
}

template<typename T>
void print(T&& t) {
    std::cout << "Rvalue ref.\n";
}

template<typename T>
void testprint(T&& v) {
    print(v); // 此时v是函数形参，已经是一个左值，将会永远调用左值版本的print
    print(std::forward<T>(v)); // 实现完美转发
    print(std::move(v)); // 强转为右值，永远调用右值版本print
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}

int main () {
    int x = 1;
    testprint(x); // 实参为左值
    testprint(10); // 实参为右值
}
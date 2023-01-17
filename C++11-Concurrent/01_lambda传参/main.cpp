#include <thread>
#include <iostream>
#include <iomanip>

void TestFoo(int a, int b, int& c) {
    std::cout << std::setw(25) << "&c in TestFoo stack: " << &c << std::endl;
    c = a + b;
}

int main() {
    std::cout << std::left;  // 調整為左对齐

    std::cout << "當前的處理器數量：" << std::thread::hardware_concurrency() << std::endl;
    int a = 20, b = 10, c = 0;
    std::cout << std::setw(25) << "&c in main stack: " << &c << std::endl;
    std::thread trd([=, &c]() {
        std::cout << std::setw(25) << "&c in lambda block: " << &c << std::endl;
        TestFoo(a, b, c);
    }); // 用Lambda可以將參數以Reference的方式transfer給綫程
    
    trd.join(); // 主线程join等待销毁子线程
}
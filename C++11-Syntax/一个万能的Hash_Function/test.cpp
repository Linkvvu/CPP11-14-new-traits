#include <iostream>
#include <unordered_set>
#include "Hash_Function.h"

namespace test1
{

void test() {
    Customer c1(static_cast<string>("nihao"), static_cast<string>("wrold"), 100);
    std::unordered_set<Customer, CustomerHash> s;
    s.insert(c1);
    s.insert(Customer(string("JJ"), string("Lin"), 40));
}

}

namespace test2
{

void test() {
    Customer c1(static_cast<string>("Jay"), static_cast<string>("J"), 40);
    std::unordered_set<Customer> s;
    s.insert(c1);
}
    
}


int main() {
    test1::test();  // 调用了Hash_Function.h头文件中的万能hash—function
    test2::test();  // 调用了我们在std标准命名空间中为自定义类型Customer添加的hash函数
    std::cout << "Both insert sucessfully!" << std::endl;
}
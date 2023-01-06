/**
 * @file test_process.cpp
 * @brief 测试程序
 * @version 0.1
 * @date 2022-11-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "Mystr.h"
#include "Template_template_parameter.hpp"
#include <vector>


// 因为vector模板类需接收两个模板参数，故于定义的接口不吻合
// 利用 template alias(模板别名)技术，使得接口一致
template<typename T>
using Vec = std::vector<T>;

template<typename T>
using Vec1 = std::vector<T, std::allocator<T>>;
// Vec与Vec1相同，只不是Vec使用隐式了默认参数类型，Vec1显式使用了默认参数类型

int main() {
    // test_moveable(std::vector<MyStr>(), 100000);   

    /* 类模板 "std::vector" 与 模板 template 参数 "Containe" 不兼容 */
    /* error : expected a template of type 'template<class Item> class Container',
     got 'template<class _Tp, class _Alloc> class std::vector' */ 
    // test_moveable_class<std::vector, MyStr>();  // 见上面的错误信息
    test_moveable_class<Vec, MyStr>();  // 临时对象
}
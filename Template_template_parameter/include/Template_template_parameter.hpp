/**
 * @file Template_template_parameter.hpp
 * @brief 对比moveable元素与non-moveable元素的运行效率
 * @apply_NewTraits 运用模板的模板参数(强调"参数"),与模板别名特性 
 * @version 0.1
 * @date 2022-11-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/*----------------------------------------------------------------------*/
/*        method-1 : 利用萃取机(iterator-tarits)来获取模板参数的类型       */
/*----------------------------------------------------------------------*/
#ifndef TEMPLATE_TEMPLATE_PARAMETER_HPP_
#define TEMPLATE_TEMPLATE_PARAMETER_HPP_
#include <iterator>
#include <chrono>
#include "Mystr.h"

template<typename Duration>
using Time_Point = std::chrono::time_point<std::chrono::system_clock, Duration>;

template<typename T>
void test_moveable(T container_obj, long amount) {
    char buf[15] {};
    // 利用萃取机提取模板参数中的类型
    typedef typename std::iterator_traits<typename T::iterator>::value_type V1type;
    
    Time_Point<std::chrono::microseconds> StartTime = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::system_clock::now());
    for (int i = 0; i < amount; i++) {
        ::snprintf(buf, 15, "%d", rand());
        auto ite = container_obj.end();
        container_obj.insert(ite, V1type(buf));
    }
    Time_Point<std::chrono::microseconds> EndTime = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::system_clock::now());
    std::cout << "construction,micro-seconds : " << (EndTime-StartTime).count() << std::endl;
    std::cout << "Current container size = " << container_obj.size() << std::endl;
}




/*----------------------------------------------------------------------*/
/*            method-2 : 利用"模板别名" 与 "模板的‘模板参数’"解决          */
/*----------------------------------------------------------------------*/

/* 声明一个模板类，此模板参数的类型分别为：
        * 一个模板类型(即需要传入一个类型，该类型也必须是模板) --> 如,vector类型就是一个模板，可将其传入
           * 且该传入的模板类型必须只接受一个模板参数
           * 因为声明为--> template<typename T> typename Container
           * 而不是--> template<typename T1, typename T2> typename Container（若为此,则传入的模板类型必须接受两个模板参数）
        * 一个 general type
*/
template<template<typename T> 
         typename Container,  // 模板的模板参数
         
         typename Item, // 普通模板参数
         size_t amount = 100000>

class test_moveable_class {

public:
    test_moveable_class() {
        using namespace std;
        char buf[15] {};
        
        Time_Point<chrono::microseconds> StartTime = chrono::time_point_cast<chrono::microseconds>(chrono::system_clock::now());
        for (int i = 0; i < amount; i++) {
            ::snprintf(buf, 15, "%d", rand());
            ite cur_position = _Cota.end();
            _Cota.insert(cur_position, Item(buf));
        }
        Time_Point<std::chrono::microseconds> EndTime = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::system_clock::now());
        std::cout << "construction,micro-seconds : " << (EndTime-StartTime).count() << std::endl;
        std::cout << "Current container size = " << _Cota.size() << std::endl;

        output_static_data( *(_Cota.begin()) );
    }

    
private:
    Container<Item> _Cota;
    typedef typename Container<Item>::iterator ite;
};
#endif
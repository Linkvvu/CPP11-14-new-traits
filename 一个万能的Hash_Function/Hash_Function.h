/**
 * @file Hash_Function.h
 * @brief 
 * @version 0.1
 * @date 2022-11-07
 * @reference 侯捷老师-STL标准库和泛型编程
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <string>

using std::string;

class CustomerHash;

class Customer {
    friend std::hash<Customer>;
    friend CustomerHash;
private:
    string _first_name;
    string _last_name;
    int _age;

public:
    Customer(string& fn, string& ln, int age) 
        :
        _first_name(fn),
        _last_name(ln),
        _age(age) {}
    
    Customer(string&& fn, string&& ln, int age) 
        :
        _first_name(fn),
        _last_name(ln),
        _age(age) {}

// 注意：要为 Custom 类定义一个operator==，用于给相应容器的萃取机(traits)提供equal_to函数，用于判断是否相等！
        bool operator==(const Customer other) const  {
        return (_first_name == other._first_name && _last_name == other._last_name && _age == other._age);
    }
};


/*--------------------------------------------------------------------------------------------------------------*/
/*                                    写一个万能的Hash_function                                                  */
/*--------------------------------------------------------------------------------------------------------------*/

/*
 * 写可变参数模板时一定要注意顺序，因为模板并不是定义的函数，只是告诉编译器该怎么生成相应函数
 * 在被用到时才会被定义出来
 */

template<typename T>
inline void hash_combine(size_t& seed, const T& target) {
    seed ^= std::hash<T>()(target) + 0x9e3779b9 + (seed << 6) + (seed >> 2);    // 0x9e3779b9黄金比例
}

template<typename THE_LAST> // 终点函数
void hash_universal(size_t& seed, const THE_LAST& last) {
    hash_combine(seed, last);
}

template<typename T, typename... PACKS> // recursive函数
void hash_universal(size_t& seed, const T& FirstArg, const PACKS&... args) {
    hash_combine(seed, FirstArg);
    hash_universal(seed, args...);
}

template<typename... PACKS>  // 人口函数
size_t hash_universal(const PACKS&... args) {
    size_t seed = 0;
    hash_universal(seed, args...);
    return seed;
}


/**
 * @brief 基于"可变模板参数(variadic)"实现一个万用的Hash_function
 * 
 */
class CustomerHash {
public:
    std::size_t operator()(const Customer& c) const
    {
        return hash_universal(c._first_name, c._last_name, c._age);
    }
};


/*--------------------------------------------------------------------------------------------------------------*/
/*                                    在std标准命名空间中向hash函数添加自定义类型的实例化                           */
/*--------------------------------------------------------------------------------------------------------------*/

/**
 * @brief 以定义struct hash偏特化的形式，实现"自定义类型"的Hash Function
 * 
 */
namespace std
{

template<>
struct hash<Customer> {
public:
    size_t operator()(const Customer& c) const noexcept
    {
        return hash<string>()(c._first_name) + hash<string>()(c._last_name)
            + hash<int>()(c._age);
    }
};

}

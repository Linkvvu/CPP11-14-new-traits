/**
 * @file Mystr.h
 * @brief declaration Mystr class
 * @version 0.1
 * @date 2022-11-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef MYSTR_H_
#define MYSTR_H_

#include <iostream>
#include <cstring>
#include <iomanip>

class MyStr {
public:
    static size_t DCtor;
    static size_t arg_Ctor;
    static size_t Copy_Ctor;
    static size_t Move_Ctor;
    static size_t Copy_assign;
    static size_t Move_assign;
    static size_t Destroy;

public:
    MyStr() = delete;
    /* copy constructor */

    MyStr(const char* str) {
        arg_Ctor++;
        _len = strlen(str);
        init_data(str);
    }

    MyStr(const MyStr& s) : _len(s._len) {
        Copy_Ctor++;
        init_data(s._contents);
    }

    MyStr(MyStr&& s) noexcept : _len(s._len) {
        Move_Ctor++;
        // 浅拷贝
        _contents = s._contents;
        // 切断原对象与其成员的联系
        s._contents = nullptr;
        s._len = 0;
    }

    // copy assign
    MyStr& operator=(const MyStr& s) {
        Copy_assign++;
        if (this == &s) { /* 若为自身则什么都不做 */ 
            return *this;
        }
        if (_contents != nullptr) {delete[] _contents;}
        _len = s._len;
        init_data(s._contents);
        return *this;
    }

    MyStr& operator=(MyStr&& s) noexcept {
        Move_assign++;
        if (this == &s) { /* 若为自身则什么都不做 */ 
            return *this;
        }
        if (_contents != nullptr) {delete[] _contents;}
        _len = s._len;
        _contents = s._contents; /* 浅拷贝 */
        
        // 切断原对象与其成员的联系
        s._len = 0;
        s._contents = nullptr; 
        return *this;
    }

    ~MyStr() {
        Destroy++;
        if (_contents != nullptr) {
            delete[] _contents;
        }
    }

private:
    inline void init_data(const char* data) /* 深拷贝 */ {
        _contents = new char[_len+1];
        strncpy(_contents, data, _len);
        _contents[_len] = '\0';
    }

    char* _contents = nullptr;
    size_t _len = 0;
};

template<typename T>
void output_static_data(const T& cur) {
    const size_t wide = 8;
    using std::cout;
    using std::endl;
    using std::setw;

    cout << typeid(cur).name() << "---" << endl;
    cout << setw(8) << "DCtor=" << std::left << setw(wide) << T::DCtor
         << setw(8) << "arg_Ctor=" << std::left << setw(wide) << T::arg_Ctor
         << setw(8) << "Copy_Ctor=" << std::left << setw(wide) << T::Copy_Ctor
         << setw(8) << "Move_Ctor=" << std::left << setw(wide) << T::Move_Ctor
         << setw(8) << "Copy_assign=" << std::left << setw(wide) << T::Copy_assign 
         << setw(8) << "Move_assign=" << std::left << setw(wide) << T::Move_assign
         << setw(8) << "Destroy=" << std::left << setw(wide) << T::Destroy
         << std::endl;
}
#endif
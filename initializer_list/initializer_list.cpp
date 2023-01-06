#include <iostream>
#include <initializer_list>
#include <vector>

class Basic {
protected:
    Basic() {std::cout << "Basic constructor was call\n";};
private:
    Basic(const Basic& ref) {}
    // Basic& operator[](Basic& ref) { return Basic a;}
};

class child : public Basic // 继承了BASIC类的特性，默认没有拷贝构造(被隐藏),但子类可自己定义拷贝构造
{
public:
    child() 
    : Basic() 
    {
        std::cout << "child default constructor was call\n";
    }

    child(const int a, const int b) 
        :
        Basic(),
        _a(a),
        _b(b)
        {std::cout << "child arguments constructor was call\n";}
    
    child(const std::initializer_list<int>& x) 
    // explicit 需显示的调用该构造函数，如:child b {5,6} (调用构造函数)
    // 而不能隐式的参与转换(运算)如：child e = {2,6} (参与运算)
    { 
        std::cout << "initializer_list constructor was call\n";
    }
    child (child&&) { std::cout << "child move constructor was called\n"; }
    // child(const child& x) : Basic() {
    //     std::cout << "child copy constructor was call\n";
    // }  /*可自定义默认的拷贝构造*/
private:
    int _a;
    int _b;
};

int main() {
    child a; // 调用默认构造
    child b {5,6};  // 调用initializer_list初始化列表构造
    child c {5,5,5,100}; // 调用initializer_list初始化列表构造
    //! child d = {10,4,5,5}; // ERROR:converting to 'child' from initializer list would use explicit constructor 'child::child(std::initializer_list<int>)'
    //! child e = {2,6}; // ERROR:converting to 'child' from initializer list would use explicit constructor 'child::child(std::initializer_list<int>)'
    child k = child{2,6};
    std::cout << std::endl;
    child f ({3,6,8,'x'}); // 调用initializer_list初始化列表构造
    //! child g {3.8}; // ERROR:从 "double" 到 "int" 进行收缩转换无效
    child h {'h'}; // OK: 没有进行收缩转换，char 1字节 --扩充-->为int 4字节
    //! child i(a); // ERROR:由于基础BASIC其特性，无法引用 函数 "child::child(child &)" (已隐式声明) -- 它是已删除的函数
}

/*
ps : 由于initializer内部的数据成员只有一个指向array头部的迭代器和记录数组长度
     而不是如array对象本身，如下
    private:
      iterator			_M_array;
      size_type			_M_len;
    
并且没有定义拷贝构造，故其默认的拷贝构造函数为浅拷贝！

若一个类中定义了形参为initializer_list的构造函数，则 'class tmp{5,6,9}' 语法“只能”调用形参为initializer_list的构造函数
若一个类中没有定义形参为initializer_list的构造函数，则初始化列表将会选择合适的constructor，将列表中的各元素作为参数逐个传入合适的构造函数
*/
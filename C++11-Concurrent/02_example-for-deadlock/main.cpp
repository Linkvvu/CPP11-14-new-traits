/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief 银行转账案例-理解concurrent的死锁问题
 * @version 0.1
 * @date 2023-01-17
 * @copyright Copyright (c) 2023
 *
 */

#include <iostream>
#include <thread>
#include <mutex>

struct BackAccount {
    BackAccount(const int balance, const std::string& name)
        : _balance(balance)
        , _name(name) { }

    mutable std::mutex _Mutex;
    mutable int _balance;
    std::string _name;
};

// a向b转账
void transferMoney(const BackAccount& a, const BackAccount& b, const int money) {
    /***********************************临界区******************************************/
    std::lock(a._Mutex, b._Mutex /*....*/);  // 以同样的顺序lock多个锁, 且只负责加锁不负责解锁
    
    // lock_guard默认操作为：加锁 且离开作用域解锁
    // 设置std::adopt_lock标签，表示该mutex已被锁，lock_guard无需加锁
    {
        std::lock_guard<std::mutex> lockA(a._Mutex, std::adopt_lock);
        std::lock_guard<std::mutex> lockB(b._Mutex, std::adopt_lock);
        if (a._balance < money) {
            return;
        }
        a._balance -= money;
        b._balance += money;
    } // 避免做IO操作时mutex还在lock，让CPU干等
    std::cout << a._name << " 向 " << b._name << "转账：&" << money << std::endl; 
    // std::cout链式掉用，之间可能存在线程切换导致输出混乱
    /*********************************************************************************/
}
#if nullptr
namespace BadExample
{
    void transferMoney(const BackAccount& a, const BackAccount& b, const int money) { 
        /*
            若以此调用该函数，则可能会产生死锁
            BadExample::transferMoney(person1, person2, 100);
            BadExample::transferMoney(person2, person1, 100);
            或
            BadExample::transferMoney(person1, person1, 100);
        */
        std::lock_guard<std::mutex> lockA(a._Mutex);
        std::lock_guard<std::mutex> lockB(b._Mutex);
        if (a._balance < money) {
            return;
        }
        a._balance -= money;
        b._balance += money;
        std::cout << a._name << " 向 " << b._name << "转账：&" << money << std::endl;
    }
    
} // namespace BadExample
#endif

int main() {
    BackAccount person1(500, "周杰伦"), person2(100, "陈冠希");

    std::cout << "转账前：" << std::endl << std::endl;
    std::cout << "person 1 Asset = " << person1._balance;
    std::cout << "\t\t";
    std::cout << "person 2 Asset = " << person2._balance;
    std::cout << std::endl;

    std::thread trd([&]() {
        transferMoney(person2, person1, 100);
    });
    transferMoney(person1, person2, 300);

    trd.join();
    
    std::cout << "转账后：" << std::endl;
    std::cout << "person 1 Asset = " << person1._balance;
    std::cout << "\t\t";
    std::cout << "person 2 Asset = " << person2._balance;
}
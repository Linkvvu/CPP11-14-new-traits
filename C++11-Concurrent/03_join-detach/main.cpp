#include <iostream>
// #define Use_CXX_STANDARD_11_Thread

// Conclusion： C++11的线程库中存在父子关系，若父线程退出，则子线程也会退出
//              POSIX线程接口：仅存在[主线程---其他线程]关系，无父子关系

#ifdef Use_CXX_STANDARD_11_Thread
#include <thread>
#include <chrono>

    void testSleep() {
        std::cout << "三层子线程进入\n";
        std::this_thread::sleep_for(std::chrono::seconds(3));
        std::cout << "三层子线程退出\n"; 
    }

    void foo() {
        std::thread trd(testSleep);
        trd.detach(); // 即使detach后，若父线程退出，则子线程依然会退出
    }

    int main() {
        std::thread trd(foo);
        // trd.detach(); // 即使detach后，若父线程退出，则子线程依然会退出
        trd.join();
        std::cout << "二层子线程已经退出\n";
        std::cout << "主线程 Bye";
        return 0;
    }
#else 
    /* POSIX 接口 
        pthread_exit(nullptr)：只针对于主线程设计(猜测)，若主线程调用此函数，则只是主线程退出，进程不会结束
        POSIX线程接口：仅存在[主线程---其他线程]关系，无父子关系
        C++11 thread库：存在线程父子关系
    */

    #include <pthread.h>
    #include <windows.h>

    void* SleepTest(void*) {
        std::cout << "三层子线程进入\n";
        ::Sleep(3000);
        std::cout << "三层子线程退出\n";
        return nullptr;
    }

    void* foo(void*) {    
        ::pthread_t second_trd;
        ::pthread_create(&second_trd, nullptr, &SleepTest, nullptr);
        ::pthread_detach(second_trd);
        // ::pthread_exit(nullptr);  // 非主线程的线程调用pthread_exit()与return效果相同
        return nullptr;
    }

    int main() {
        ::pthread_t second_trd;
        ::pthread_create(&second_trd, nullptr, &foo, nullptr);
        ::pthread_join(second_trd, nullptr);
        std::cout << "二层子线程已经退出\n";
        std::cout << "主线程 Bye\n";
        ::pthread_exit(nullptr);  // 只是主线程退出，子线程不会退出
        // return 0; 若retur而非pthread_exit()，则整个进程退出
    }

#endif // Use_C++_STANDARD_11_Thread



/*

CPP11库 输出:
三层子线程进入
二层子线程已经退出
主线程 Bye    //可由此看出，二层线程(B)退出，其子线程三层线程(C)就直接退出，没有输出[三层子线程退出]

POSIX库 输出:
三层子线程进入
二层子线程已经退出
主线程 Bye
三层子线程退出   //二层线程(B)退出，三层线程(C)没有直接退出，故说明无父子关系，只有[main线程与其他线程关系]

*/

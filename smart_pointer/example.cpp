#include <iostream>
#include <memory>
#include <fstream>

struct Mydeleter1 {
    void operator()(std::ofstream* fs) const {
        fs->close();
    }
};

void Mydeleter2(std::ofstream* fs) {
    std::cout << "ok\n";
}

char buf[4] {};
int main() {
    // std::unique_ptr<std::ofstream, Mydeleter1> u_i_1(new std::ofstream("./temp.txt", std::ios::out & std::ios::app));
    // std::cout << sizeof(u_i_1);
    // u_i_1->write("1 \0", 2);
    std::unique_ptr<std::ofstream, void(*)(std::ofstream* fs)> u_i_2(new std::ofstream("./temp.txt", std::ios::out & std::ios::app), Mydeleter2);
    u_i_2->write("dasda",3);
}
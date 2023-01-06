#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
using namespace std;

class A {
public:
	A(int a = 3, double b = 4): _a(a), _b(b){}
	virtual void display(int a) {
		cout << "Base --- int" << endl;
	}
    void display(double a) {
        cout << "base --- double" << endl;
    }

    void display(float a) {
        cout << "base --- float" << endl;
    }
private:
	int _a;
	double _b;
};

class B : public A {
public:
	using A::A;
    using A::display;
    
    int display(string x) {
        std::cout << "child child --- int\n";
        return 0;
    }

private:
    double _m;
};

class C :public B{
    private:

    public: 
	using B::B;

};

void func() {
    char xx[10];
    static unsigned x = 0;
    std::cout << "ok --- " << ++x << std::endl;
    std::istream_iterator<int, char> x(std::cin);
    C c {5,6};
}

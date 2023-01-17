#include <initializer_list>
#include <algorithm>

namespace init_args
{

template<typename T>
T max(const std::initializer_list<T>& args) {
    T res = *args.begin();
    for (const T& item : args) {
        res < item ? res = item : res;
    }
    return res;
}

}

namespace vari_template_parameter
{

int max(const int last) {
    return last;
}

template<typename... PACK>
int max(const int first, const PACK... args) {
    return std::max(first, vari_template_parameter::max(args...));
}

}
#include <iostream>
#include <tuple>
#include <vector>

template<int IDX, int MAX, typename... PACK>
struct output_tuple {

    static void print(std::ostream& out, const std::tuple<PACK...>& t) {
        out << std::get<IDX>(t) << (IDX+1 == MAX ? "" : ",");
        output_tuple<IDX+1, MAX, PACK...>::print(std::cout, t);
    }

};

template<int MAX, typename... PACK>
struct output_tuple<MAX, MAX, PACK...> {
    static void print(std::ostream& out, const std::tuple<PACK...>& t) {    }
};

template<typename... PACK>
std::ostream& operator<<(std::ostream& out, const std::tuple<PACK...>& t) {
    out << "[";
    output_tuple<0, sizeof...(PACK), PACK...>::print(out, t);
    out << "]";
    return out;
}

int main() {
    std::cout << std::make_tuple(7.5, 6 , "dddd");
}
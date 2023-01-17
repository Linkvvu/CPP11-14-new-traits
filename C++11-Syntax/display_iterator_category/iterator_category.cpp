#include <iostream>
#include <typeinfo>
#include <iterator>     // std::iterator_traits
#include <array>
#include <vector>
#include <list>
#include <deque>
#include <queue>
#include <stack>
#include <forward_list>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

void _display_category(std::random_access_iterator_tag) {
    std::cout << "It`s : random_access_iterator_tag\n";
}

void _display_category(std::bidirectional_iterator_tag) {
    std::cout << "It`s : bidirectional_iterator_tag\n";
}

void _display_category(std::forward_iterator_tag) {
    std::cout << "It`s : forward_iterator_tag\n";
}

void _display_category(std::output_iterator_tag) {
    std::cout << "It`s : output_iterator_tag\n";
}

void _display_category(std::input_iterator_tag) {
    std::cout << "It`s : input_iterator_tag\n";
}

template<typename I>
void display_category(I ite) {
    typename std::iterator_traits<I>::iterator_category cagy;
    _display_category(cagy);

    std::cout << "typeid(ite).name : " << typeid(ite).name() << std::endl << std::endl;
}

int main() {
    using namespace std;
	cout << "test_iterator_category()..........\n" << std::endl;
  	
  	display_category(array<int,10>::iterator());
  	display_category(vector<int>::iterator());
  	display_category(list<int>::iterator());	
  	display_category(forward_list<int>::iterator());  
  	display_category(deque<int>::iterator());
    // display_category(queue<int>::iterator());    实质上是适配器-adapter 无迭代器
    // display_category(stack<int>::iterator());    同上

  	display_category(set<int>::iterator());
  	display_category(map<int,int>::iterator());
  	display_category(multiset<int>::iterator());
  	display_category(multimap<int,int>::iterator());
  	display_category(unordered_set<int>::iterator());
  	display_category(unordered_map<int,int>::iterator());
  	display_category(unordered_multiset<int>::iterator());
  	display_category(unordered_multimap<int,int>::iterator());	  
	    	
  	display_category(istream_iterator<int>());
    display_category(ostream_iterator<int>(cout));

}

/**
 * @OutPut
 * 
 * 
test_iterator_category()..........

It`s : random_access_iterator_tag
typeid(ite).name : Pi

It`s : random_access_iterator_tag
typeid(ite).name : N9__gnu_cxx17__normal_iteratorIPiSt6vectorIiSaIiEEEE

It`s : bidirectional_iterator_tag
typeid(ite).name : St14_List_iteratorIiE

It`s : forward_iterator_tag
typeid(ite).name : St18_Fwd_list_iteratorIiE

It`s : random_access_iterator_tag
typeid(ite).name : St15_Deque_iteratorIiRiPiE

It`s : bidirectional_iterator_tag
typeid(ite).name : St23_Rb_tree_const_iteratorIiE

It`s : bidirectional_iterator_tag
typeid(ite).name : St17_Rb_tree_iteratorISt4pairIKiiEE

It`s : bidirectional_iterator_tag
typeid(ite).name : St23_Rb_tree_const_iteratorIiE

It`s : bidirectional_iterator_tag
typeid(ite).name : St17_Rb_tree_iteratorISt4pairIKiiEE

It`s : forward_iterator_tag
typeid(ite).name : NSt8__detail14_Node_iteratorIiLb1ELb0EEE

It`s : forward_iterator_tag
typeid(ite).name : NSt8__detail14_Node_iteratorISt4pairIKiiELb0ELb0EEE

It`s : forward_iterator_tag
typeid(ite).name : NSt8__detail14_Node_iteratorIiLb1ELb0EEE

It`s : forward_iterator_tag
typeid(ite).name : NSt8__detail14_Node_iteratorISt4pairIKiiELb0ELb0EEE

It`s : input_iterator_tag
typeid(ite).name : St16istream_iteratorIicSt11char_traitsIcExE

It`s : output_iterator_tag
typeid(ite).name : St16ostream_iteratorIicSt11char_traitsIcEE

 * 
 */
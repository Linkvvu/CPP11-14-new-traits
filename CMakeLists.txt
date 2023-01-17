cmake_minimum_required(VERSION 3.0)

project(C++-11_TRAITS)

set(CMAKE_CXX_FLAGS "-std=c++11 -O0 -fno-elide-constructors")

add_subdirectory(C++11-Syntax/一个万能的Hash_Function)

add_subdirectory(C++11-Syntax/display_iterator_category)

add_subdirectory(C++11-Syntax/display_compiler_Version)

add_subdirectory(C++11-Syntax/initializer_list)

add_subdirectory(C++11-Syntax/Template_template_parameter)

add_subdirectory(C++11-Syntax/Examples_Of_Variadic_Template)

add_subdirectory(C++11-Syntax/lvalue-rvalue-rvalue_reference)

add_subdirectory(C++11-Syntax/smart_pointer)

add_subdirectory(C++11-Syntax/using_in_class)
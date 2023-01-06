cmake_minimum_required(VERSION 3.0)

project(C++-11_TRAITS)

set(CMAKE_CXX_FLAGS "-std=c++11 -O0 -fno-elide-constructors")

add_subdirectory(一个万能的Hash_Function)

add_subdirectory(display_iterator_category)

add_subdirectory(display_compiler_Version)

add_subdirectory(initializer_list)

add_subdirectory(Template_template_parameter)

add_subdirectory(Examples_Of_Variadic_Template)

add_subdirectory(lvalue-rvalue-rvalue_reference)

add_subdirectory(smart_pointer)

add_subdirectory(using_in_class)
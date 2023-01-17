/* initialize static member variables to class 'Mystr' */
#include "Mystr.h"

size_t MyStr::DCtor = 0;
size_t MyStr::Copy_Ctor = 0;
size_t MyStr::arg_Ctor = 0;
size_t MyStr::Move_Ctor = 0;    
size_t MyStr::Copy_assign = 0;
size_t MyStr::Move_assign = 0;
size_t MyStr::Destroy = 0;
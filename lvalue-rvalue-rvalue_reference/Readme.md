### 左值 - 右值 - 将亡值

```
        表达式
        /   \
       /     \
    泛左值   右值
     /  \     / \
    /    \   /   \
  左值   将亡值  纯右值
```

#### 左值：

* 左值是可寻址的变量，有持久性；
* 一般具有名称

#### 右值：
* 右值一般是不可寻址的常量
* 一般不具有名称
* 函数返回的**非引用值**，如`int void func();`
* 无名临时对象，短暂性的(纯右值)，可对其赋值，但这种操作无意义，因为临时对象当当前表达式结束时对自动析构
  
* 直接字面量值,如(8, 6.5)等
  
  字符串常量是右值，可对其取地址，其本质是一个const char数组，存放在静态数据区(.rodata段)

```cpp
左值和右值主要的区别之一是左值可以被修改、取地址、赋值，而右值不能。
特殊的：
* const int x = 10中，x是左值，但一般情况下为常量
* 字符串常量是左值，可对其取地址，存放在静态数据区(.rodata段)
* 临时对象是纯右值，一般情况下虽可对其取地址/赋值，但表达式执行完后将会被析构
```

#### 将亡值
“将亡值”概念的产生，是由右值引用的产生而引起的，**将亡值就是即将要被进行“移动语义”的值**

所谓的将亡值表达式，就是下列表达式：
* **返回右值引用**的函数的调用表达式
* 转换为右值引用的转换函数/`static_cast`强转的调用表达式
  
**以上两种表达式的返回结果结果都是不具名的右值引用,(不具名)故它们属于右值**,

**这种右值常用来完成移动构造或移动赋值的特殊任务，扮演着“将亡”的角色**

##### 两种将亡值：
> * 泛左值->将亡值：
>   ```cpp
>   int a = 10; // a为左值
>   static_cast<int&&>(a); // 将左值强转为右值引用
>   // 上一句等价于std::move(a) , 此时既是左值又是将亡值
>   ```
> * 右值->将亡值：
>   ```cpp
>   int&& a = 10; 
>   /* 10是纯右值，a为左值，只是a右值引用指向一个右值 */
>   /* 右值10的生命周期被延长，它此时为将亡值 */ 
>   ```
> 

### 左值引用 - 右值引用
#### 左值引用：
相当于给变量取“别名（alias）”，

其本质是一个常指针，`int * const x = ...`

```cpp
与常指针相同的：
1. 引用必须初始化
2. 初始化后，引用的指向(point to)不能修改
```

左值引用只能引用左值！

#### 右值引用：
就是必须绑定到右值的引用，其延长了右值的生命，使得该右值与这个右值引用共存亡  

```cpp
// 错误函数书写
A&& f() { 
    return A(); //Warn:返回的右值引用所引用的对象被虚构
}
```
`特殊的：若函数返回右值引用，若函数一个临时对象->retrun obj()，当函数结束时，临时对象本应被续命，但是因为其离开了作用域(函数退栈)，则该临时对象会被析构，故返回的右值引用实际上只是引用了一个被析构的对象`



C++11之后提出了"右值引用"以实现**移动意义**

需要注意的是：
```cpp
void func(int& arg) {}
void func(int&& arg) {}
-----------------------------------------------------
int&& a = 10; // 右值引用a 只不过是引用了一个字面值(右值)10
func(a); // called void func(int& arg)，因为a为左值
func(10); // called void func(int&& arg), 因为10为右值

/**
 * 此时右值引用'a'为左值，只不过其引用了一个字面值(右值)
 * 此时这个字面值的生命被延长，若引用的是临时对象(纯右值)，则该临时对象暂时不会destroy
 * 
```
**右值的概念其实很微妙，一旦某个右值，有了名字，也就在内存中有了位置，它就变成了1个左值。**

#### "右值引用"与"const左值引用"的区别：
* 我们已经清楚，右值引用只能引用右值，左值引用只能引用左值
  
const左值引用与左值引用不同的是，其可以引用右值
```cpp
    int a = 100;
    std::cout << "a :" << &a << std::endl; // a :0x61fe10
    // int& x = 10;  ERROR:非常量引用的初始值必须为左值
    const int& aa = 10;
    std::cout << "a& :" << &aa << std::endl; // a& :0x61fe14
```
由上述例子可知，const左值引用在指向一个左值时，先在**栈区开辟**一个值为10的**无名整型量**，此时**这个10实质上已为左值**，再将引用aa与这个整型量进行绑定

-----

### 万能引用
在自动类型推导下，如**模板参数T**/**auto**/等情形下，若写成`T&& arg`或`auto&& arg`，通过所传递实参的左右值category，会有以下两种情况

* 当参数(或赋值者)为**左值**时：
  
  ```cpp
  int x = 10; // x为左值
  auto&& arg = x; // 将左值assign给arg，自动类型推导出类型为" int& "
  // 由引用折叠得： int& + && -> int& -> 故此时函数的参数类型为左值引用
  ```
* 当参数(或赋值者)为**右值**时：
  
  ```cpp
  template<typename T>
  void func(T&& arg) {...} 
  //此处的·T&& arg·并不是右值引用，因为模板参数T的类型还没决定，故此处为万能引用
  ----------------------------
  func(20); // called func，且实参为右值，则T的类型被推导为" int "
  // 由引用折叠得: int&& -> 故此时函数的形参类型为右值引用
  ```

其实，所谓的万能引用，只不过是T/auto的参数类型还不确定，其类型可能是`左值引用`,`右值`，`右值引用等等`，只有**根据实参的"左右值属性"确定了T的类型后，再结合T后面的&&，通过引用折叠，进而确定出最终的形参类型**

**通过万能引用，可令一个模板函数既能接收左值也能接收右值！**

万能引用通过引用折叠后其类型也一定是左/右值引用

#### 引用折叠
模板参数T|实际参数类型|最终类型
-|-|-
T&|R 右值|R&
T&|R& 左值引用|R&
T&|R&& 右值引用|R&
|||
T&&|R 右值|R&&
T&&|R& (即R为左值)|R&
T&&|R&& 右值引用|R&&
### 完美转发 - perfect forward

写在前面：**注意：函数形参一定是左值！！！**

#### 什么是完美转发？
因为函数形参一定是左值，若右值作为函数实参，其右值属性就会被隐藏，故需要还原其函数实参的左右值属性

#### C++为什么需要完美转发？

从一个简单的例子出发，假设有这样一种情况；用户一般使用testForward函数，testForward什么也不做，只是简单的转调至print函数

```cpp
template<typename T>
void print(T& t) {
    std::cout << "Lvalue ref.\n";
}

template<typename T>
void print(T&& t) {
    std::cout << "Rvalue ref.\n";
}

template<typename T>
void testprint(T&& v) {
    print(v); // 此时v是函数形参，已经是一个左值，将会永远调用左值版本的print
    print(std::forward<T>(v)); // 实现完美转发
    print(std::move(v)); // 强转为右值，永远调用右值版本print
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}

int main () {
    int x = 1;
    testprint(x); // 实参为左值
    testprint(std::move(x)); // 实参为右值
}
```
OutPut:
```cpp
Lvalue ref.
Lvalue ref.
Rvalue ref.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Lvalue ref.
Rvalue ref.
Rvalue ref.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
```
* 
  用户希望`testForwad(x)`最终调用的是左值版本，而`testprint(std::move(x))`最终调用的是右值版本print

  可是，testForward中，右值引用v引用了实参，v为函数形参，故v为左值。

  所以`print(v)`永远调用左值版本，与用户本意不符。`print(std::move(v))`,永远调用右值版本

发现，本质问题在于，左值右值再函数调用时，都转化成了左值，使得函数调用无法判断参数类型属性

在STL中，随处可见这种问题。比如C++11引入的`emplace_back`，它接受左值也接受右值作为参数，接着，它转调用了空间配置器的`construct`函数，而`construct`又转调用了`placement new`，`placement new`根据参数是左值还是右值，决定调用拷贝构造函数还是移动构造函数。

这里要保证从`emplace_back`到`placement new`，参数的左值和右值属性保持不变。

#### 完美转发的原理
std::forward不是独自运作的，在我的理解里，`完美转发 = std::forward + 万能引用 + 引用折叠`.三者合一才能实现完美转发的效果。

std::forward的正确运作的前提，是引用折叠机制，为`T&&`类型的万能引用中的模板参数T赋了一个恰到好处的值。我们用T去指明std::forward的模板参数，从而使得std::forward返回的是正确的类型。

回到上面的例子，`print(std::forward<T>(v));`一句实现了完美转发，我们来看看标准库中该函数做了什么：
```cpp
template<typename _Tp>
constexpr _Tp&& forward(typename std::remove_reference<_Tp>::type& __t) noexcept
{ return static_cast<_Tp&&>(__t); }
```
```cpp
template<typename T>
void testprint(T&& v) {
    print(v); // 此时v是函数形参，已经是一个左值，将会永远调用左值版本的print
    print(std::forward<T>(v)); // 实现完美转发
    print(std::move(v)); // 强转为右值，永远调用右值版本print
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
}
-------------------------------------
testprint(x); // 实参为左值
testprint(std::move(x)); // 实参为右值
```
* 我们跟随`testprint(x)`的视角进行解析
  
  x是一个左值，传递给万能引用，则模板参数T的类型为`int&`,引用折叠后(&+&& -> &)，此时函数实例化为`void testprint(int& v)`

  此时在`testprint`函数调用`std::forward<T>(v)`,forward函数的模板参数T就为`int&`

  此时函数`forward`的返回值`_Tp&&`推导为`int&`,即实例化为`constexpr int& forward(int& __t)`,故成功提取了左值`x`的category，其调用左值版本print()

* 我们跟随`testprint(std::move(x))`的视角进行解析
  
  x原本是左值，经过`std::move()`强转转换`static_cast<int&&>(x)`为右值

  传递给万能引用，则模板参数T的类型为`int`,此时函数实例化为`void testprint(int&& v)`

  此时在`testprint`函数调用`std::forward<T>(v)`,forward函数的模板参数T就为`int`
  
  此时函数`forward`的返回值`_Tp&&`推导为`int&&`,即实例化为`constexpr int&& forward(int& __t)`,故成功提取了右值`x`的category，其调用右值版本print()

至此完成了完美转发

综上所述：完美转发需要配合着万能引用，利用引用折叠语法实现。

此外标准库还有一个接收右值的`forward`版本，与上述过程类似

> Reference:[  GeT Left ](https://lamforest.github.io/2021/04/29/cpp/wan-mei-zhuan-fa-yin-yong-zhe-die-wan-neng-yin-yong-std-forward/)
### std::move与std::forward的区别
#### std::move()
```cpp
template<typename _Tp>
constexpr typename std::remove_reference<_Tp>::type&& move(_Tp&& __t) noexcept
{ return static_cast<typename std::remove_reference<_Tp>::type&&>(__t); }
```

* 由返回类型`std::remove_reference<_Tp>::type&&`可知，该函数返回一个**无名的右值引用**(即**将亡值**)
* 函数的形参是**万能引用**，可接收左值/右值
* 功能：将实参**强转转换**为一个将亡值,故用来完成移动语义

#### std::forward()
```cpp
template<typename _Tp>
constexpr _Tp&& forward(typename std::remove_reference<_Tp>::type& __t) noexcept
{ return static_cast<_Tp&&>(__t); }
```

* 函数形参:接收一个左值
* 功能：通过传入实参_Tp的category判断，利用**引用折叠语法**，判断应返回的类型
  * 若原值属性为左值,则转发函数(上例为`void testprint(T&& v)`)所推导出的模板参数类型T为`int&`，再将T类型传入`std::forward`中,`_Tp&&`->`int&`为左值引用，则`static_cast<_Tp&&>(__t)`转换为左值进行转发
    * 如，`_Tp`为`int&`，则通过引用折叠，强转为左值


  * 若原值属性为右值,则转发函数(上例为`void testprint(T&& v)`)所推导出的模板参数类型T为`int`，转发函数的形参为`int&& v`即**有名的右值引用**(左值)，再将`T(int)`传入`std::forward`中，`_Tp&&`->`int&&`为左值引用，则`static_cast<_Tp&&>(__t)`转换为右值进行转发
    * 如，`_Tp`为`int`，则通过引用折叠，强转为右值

注意：调用`std::forward()`必须指定模板参数类型`T`，其不能自动类型推导

综上所述：

**`std::forward`函数根据"初始值"的左右值属性进行类型转换，实现完美转发**

**`std::move`函数则是接收一个类型属性为左/右值的实参，将其强转为"无名的右值引用(右值)"**


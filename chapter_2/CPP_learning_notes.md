## CPP学习日记---（二）

### 内存分区

- 代码区：函数体的二进制代码
- 全局区：全局变量、静态变量、常量
- 栈区：编译器自动分配、释放：函数参数、局部变量
- 堆区：程序员自己分配和释放（或者OS回收）

程序编译结束后，未执行前，只有代码区和全局区

执行期间出现堆区和栈区

#### 代码区

> 存放CPU的机器指令

- 共享：内存中只需要一份可执行代码，可以多次使用
- 只读：防止程序被意外修改

#### 全局区

> 全局变量、静态变量、常量

程序结束后，由OS释放分配的内存

#### 栈区

函数主体会调用栈区用来存储局部变量、函数参数等

嵌套调用时会嵌套调用栈区

> 编译器只会保留一次局部变量的返回地址
>
> 之后会进行内存回收（或清空）

示例

```c++
int* func(){
    int a = 10;
    return &a;
}
int main(){
    int *p=func();
    cout<<*p<<endl;
    cout<<*p<<endl;//出现乱码
    return 0;
}
```

#### 堆区

由程序员分配或者释放(`new` or `malloc`等)

```c++
int* func(){
    int *a = new int(10);//指针也在栈区内，但保存的数据在堆区
    return a;
}
int main(){
    int *p=func();
    cout<<*p<<endl;
    return 0;
}
```

### 继承

> 和java类似，派生类可以继承基类的各种public或者protect方法
>
> 也可以选择进行重构

但是不管是java还是cpp都不能自动继承：

- java中要使用super函数实现子类继承父类的函数
- cpp中的派生类要重新调用父类的函数实现继承，同时可以选择是否覆写

在底层编译过程中，两者都保证了在子类（派生类）初始化之前，父类（基类）已经正确初始化，但两者也有区别：

- java是先分配了一整块内存用来存放子类对象的所有数据，然后层层调用构造函数，实现初始化
- cpp虽然也是分配了整块内存，但它会将基类的子对象存入内存，直接当作派生类的成员变量，然后从基类开始，层层调用构造函数

内存视图(java)

```markdown
[ Dog对象 ]
[ 对象头信息 | age | name ]
```

内存视图(cpp)

```markdown
[ Dog对象 ]
[ Animal部分: age | Dog部分: name ]
```

> java是通过JVM再运行时动态分配和管理内存实现的初始化
>
> cpp是编译时静态确定的内存布局

这里的继承类的声明和实例的创建为了符合规范，我们将声明放在对应的`hpp`头文件中

将相应的实现放在对应的`cpp`文件中

在进行编译时，可以使用g++直接编译，如`g++ -o mytest extern.cpp my_class.cpp`

如果文件过多或者依赖过多的情况下，可以使用CMakeLists.txt进行辅助构建，样例如下：

```cmake
# 设置CMake的最小版本要求
cmake_minimum_required(VERSION 3.10)

# 项目名称
project(my_project)

# 设置标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 添加可执行文件
add_executable(output extern.cpp my_class.cpp)
```

当然，在我们的构建过程中，如果有很多固定依赖（写好了很多库的组件）

> 动态库的使用场景和优点：
>
> *长期不需要修改，且需要共用或者重用*
>
> *动态库的存在可以实现减少内存开销*
>
> *如果有功能需要更新，可以不需要重新修改整个构建文件（CMakeLists.txt)，只需要更新链接文件的功能即可*

我们可以在构建文件中加上库文件搜索路径

```cmake
# 库文件路径
link_directories(/path/to/liberary)

# 链接动态库到可执行文件
target_link_liberaries(my_program example)
```

在目录中，example可以是dll文件（windows下）也可以是so文件（Linux下），不需要额外声明后缀，CMake会自动处理链接

基类的关键字会影响派生类的成员权限：

- public：基类的public -》派生类的public；基类的protected-》派生类的protected；基类的private 不能直接被派生类访问，只能通过基类的public 和 protected 成员（函数）来访问

  派生类访问

  ![image-20240213190921325](https://typora-zrx.oss-cn-beijing.aliyuncs.com/img/2024/02/13/20240213-190924.png)

  调用基类成员访问

  ![image-20240213191026894](https://typora-zrx.oss-cn-beijing.aliyuncs.com/img/2024/02/13/20240213-191030.png)

  tips: 这里的secret记得初始化（不然是空的）

- protected：基类的public 和 protected 都会成为派生类的 protected成员

- private：私有继承的话，派生类可以访问基类的保护和私有成员函数，但是不能直接访问其成员变量

  因为基类的成员变量已经成了派生类的私有成员变量，不能直接访问，得通过接口才行

用4.0生成了一个比较完整的样例

```c++
#include <iostream>

// 基类 Base
class Base {
public:
    int publicVar;
    Base() : publicVar(1), protectedVar(2), privateVar(3) {}

    void publicMethod() {
        std::cout << "Public method of Base" << std::endl;
    }

    void protectedMethod() {
        std::cout << "Protected method of Base" << std::endl;
    }

private:
    int privateVar;

protected:
    int protectedVar;
};

// 公有继承
class PublicDerived : public Base {
public:
    void accessBaseMembers() {
        std::cout << "PublicVar from Base: " << publicVar << std::endl;
        std::cout << "ProtectedVar from Base: " << protectedVar << std::endl;
        // 无法访问 privateVar
        // std::cout << "PrivateVar from Base: " << privateVar << std::endl;
        publicMethod();     // 可以访问公有成员函数
        protectedMethod(); // 可以访问保护成员函数
    }
};

// 保护继承
class ProtectedDerived : protected Base {
public:
    void accessBaseMembers() {
        std::cout << "PublicVar from Base: " << publicVar << std::endl;
        std::cout << "ProtectedVar from Base: " << protectedVar << std::endl;
        // 无法访问 privateVar
        // std::cout << "PrivateVar from Base: " << privateVar << std::endl;
        publicMethod();     // 可以访问公有成员函数
        protectedMethod(); // 可以访问保护成员函数
    }
};

// 私有继承
class PrivateDerived : private Base {
public:
    void accessBaseMembers() {
        // 无法访问 publicVar 和 protectedVar
        // std::cout << "PublicVar from Base: " << publicVar << std::endl;
        // std::cout << "ProtectedVar from Base: " << protectedVar << std::endl;
        // 无法访问 privateVar
        // std::cout << "PrivateVar from Base: " << privateVar << std::endl;
        publicMethod();     // 可以访问公有成员函数
        protectedMethod(); // 可以访问保护成员函数
    }
};

int main() {
    PublicDerived publicObj;
    publicObj.accessBaseMembers();

    ProtectedDerived protectedObj;
    protectedObj.accessBaseMembers();

    PrivateDerived privateObj;
    privateObj.accessBaseMembers();

    return 0;
}
```

CPP与java不同，java只能单继承，但可以通过继承接口实现“多继承”

CPP可以直接实现继承多基类，同时由于上述的多种继承方式，我们可以在继承不同基类时选择不同的继承方式

> CPP由于可以直接实现继承多基类，容易导致命名冲突和代码耦合
>
> 例如，假设有两个基类 A 和 B，它们都有一个名为 `foo()` 的成员函数，并且一个类 C 继承了这两个基类。如果在类 C 中调用 `foo()` 函数，编译器无法确定应该调用哪一个基类的 `foo()` 函数，因此会产生命名冲突。

### 重载

> 主要分为函数重载和运算符重载

#### 函数重载

函数重载和java类似，主要使用在同一函数不同参数的情景，

**原理**：CPP函数重载的底层原理主要是，同名不同参的函数本身的函数签名是不同的，所以编译器首先会根据函数签名来锁定函数，再进行重载解析来判断

- 调用是否合法（其实就包括下列几种情况）
- （或者是否有模板的使用）
- （或者需要进行隐式类型转换）

同一函数不同参数是为了实现不同功能

实现方式就是重载函数

![image-20240215104039382](https://typora-zrx.oss-cn-beijing.aliyuncs.com/img/2024/02/15/20240215-104123.png)

![image-20240215104051324](https://typora-zrx.oss-cn-beijing.aliyuncs.com/img/2024/02/15/20240215-104125.png)

#### 运算符重载

> 其实原理和刚才的函数重载类似

底层原理：运算符函数在面向对象编程中可以视为特殊的成员函数，由关键字operator实现

基本的样式如下：

```c++
my_class operator+(const my_class& a){
    my_class result;
    result.value= this.value + a.value;
    return result;
}
```

tips：

问题：`my_class test_one` 和 `my_class* test_one = new my_class();` 的区别？

- type不同，一个是对象，一个是指针
- 内存分配机制不同，对象的初始化是在栈中初始化的，内存的回收说在程序运行结束自动回收；指针的初始化是在堆中进行的，内存的回收需要程序员自行回收（delete）

可以进行重载的运算符有很多，算术运算符、逻辑运算符、关系运算符、单目运算符（正负、指针、取地址）、自增自减运算符、赋值（构造函数）等

### 参考资料

[黑马教程](https://www.bilibili.com/video/BV1et411b73Z?p=84&vd_source=a733c3f0d600237b1444ffb02c86d655)

[菜鸟教程](https://www.runoob.com/cplusplus/cpp-polymorphism.html)

[仓库地址](https://github.com/zrxxzz/CPP_Learning)

[博客地址](https://www.zrxp4ul.com/)



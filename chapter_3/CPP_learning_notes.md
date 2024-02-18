## CPP学习日记---（三）

### 多态

> 经典面经题，当时没答好很难受

简单理解的话，所谓的多态无非是派生类重写基类的一些成员函数

但是，这里有一点值得注意，如下面的代码段所示，我们在调用派生类方法时，如果直接使用了派生类的对象指针（或对象）

那么会直接调用派生类定义的成员函数，而不是调用覆盖或者重写的函数

```c++
//second_class.cpp
//错误示范（没加virtual关键字）
int second_class::test_base_method(){
    std::cout<<"here is base class "<<std::endl;
    return 0;
}

int first_child::test_base_method(){
    std::cout<<"here is child class"<<std::endl;
    return 1;
}
```

```c++
//main.cpp
second_class* base_one = new second_class(2023);
first_child* derived_one = new first_child(2024);
//调用基类函数
cout<<base_one->test_base_method()<<endl;
//切换指针，指向派生类
base_one = &(*derived_one);
//试图调用派生类函数
cout<<base_one->test_base_method()<<endl;
//直接调用派生类函数
cout<<derived_one->test_base_method()<<endl;
```

输出结果：

![image-20240216160343163](https://typora-zrx.oss-cn-beijing.aliyuncs.com/img/2024/02/16/20240216-160346.png)

可以看到，没有virtual并不能实现多态功能

**原理**：此时的`test_base_method()`已经在编译的时候被绑定为基类的版本，即API静态链接到了基类的函数

**多态的核心**：通过**基类**的指针或者引用去调用**派生类**重写的方法

> 而不是说直接调用派生类同名函数就算多态

加入virtual后即可实现多态

![image-20240216160358548](https://typora-zrx.oss-cn-beijing.aliyuncs.com/img/2024/02/16/20240216-160401.png)

这样同名同参，实现效果也可以不一样

#### 底层原理

- 加入virtual关键字后，编译器在编译后会创建**虚函数表**和**虚函数表指针**

- 每个对象在实例化的时候，如果所在类含有虚函数，那么会创建一张对应的虚函数表，包含了各个虚函数指针

- 在Base类调用`test_base_method()`时，会通过虚函数指针查看指向的虚函数表，从而决定调用Base类还是Derived类

- 所以这里的函数在编译过程中并不会直接链接到某个实现，而是在运行时去根据指针指向的类型（虚函数表指针具体指向哪张虚函数表）来**动态链接**到那个实现

> tips：在定义的时候可能还没想好虚函数要具体实现什么
>
> 可以先定义一个纯虚函数 like `virtual int area() = 0;`
>
> 其中的 `=0 ` 向编译器声明了该虚函数为纯虚函数

#### 动态链接

这里的动态链接和我之前的异构计算笔记中的动态链接有点像，但又不太一样

CPP虚函数的动态链接

- 感觉像是mini版的编译动态链接库（缩小成了一张表），在编译时并不去链接对应的实现，而在调用时才根据指针指向的类型（或者说虚函数表指针指向的表）动态链接对应的实现

异构计算笔记中的动态链接是指编译时刻的动态链接

- 编译阶段：编译器会检查这些外部库的引用
- 链接阶段：静态链接会将对应库的实现合并进可执行文件，而动态链接只负责保留动态链接库的引用，而不是将代码合并
- 运行时阶段：当程序运行时需要调用动态链接库中的接口时，动态链接库会被加载进内存，然后OS的动态链接器会解析调用的引用，然后找到实际内存地址进行实现

### 接口（抽象类）

和java的接口不同，CPP的接口是抽象类

抽象类无法实例化，而且接口的派生类必须重写基类的纯虚函数

![报错图](https://typora-zrx.oss-cn-beijing.aliyuncs.com/img/2024/02/16/20240216-194925.png)

![image-20240216194942394](https://typora-zrx.oss-cn-beijing.aliyuncs.com/img/2024/02/16/20240216-194945.png)

和正常的接口设计一致，CPP的接口可以说是函数与变量的集合，可以用来概括一些类的行为和特征

比如可以定义一个接口，含有吃饭、睡觉等成员纯虚函数

动物继承时需要重写相应的代码实现

#### 友元函数

> 之前讲过一次，但当时只是浅浅使用了一下
>
> 而且只用到了友元函数三条实现方式中的一条

友元函数的主要实现方式：

- 全局函数：在类内声明该函数为友元函数，允许它访问类内的一些私有或者保护变量

- 友元类：允许一类对象对另一类对象对该类进行访问（所有成员）

- 成员函数做友元：不建议使用

  因为这样往往会形成循环依赖问题(我就遇到了)，例子如下

  ```c++
  class first_child :public second_class{
  public:
      first_child(int _public_value);
      ~first_child()=default;
      int test_base_method() override;
      //下面这行声明会报错
      friend void friend_class::visit(first_child* first_child_test);
      //friend class friend_class;
      //void test_pure_virtual_method() override;
  };
  
  class friend_class :public second_class{
  public:
      void visit(first_child* first_child_test);
      friend_class();
      friend_class(int _public_value);
      ~friend_class()=default;
  };
  ```

  如果先声明`first_child`就会报错未声明`friend_class`

  如果先声明`friend_class`就会报错未声明`first_child`

  虽然可以前向声明一部分，再补充声明，但这已经得不偿失了，不如直接声明`friend class friend_class;`

> tips: 友元类可以不用先声明

原理和更详细的例子如下（4.0提供）

```c++
class A {
    friend class B; // B可以是之前未声明的类
public:
    void doSomething() {}
};

class B {
public:
    void accessA(A& a) {
        a.doSomething(); // B可以访问A的私有和保护成员
    }
};
```

在这个例子中，即使在`B`被声明之前，`A`已经将`B`声明为友元。这是允许的，因为友元关系告诉编译器`B`将能够访问`A`的非公共成员，但这并不要求`B`在声明`A`时已经完全定义。

然而，当你试图声明一个类的特定成员函数为另一个类的友元时（如 `friend void B::someFunction();`），编译器需要知道那个成员函数的完整签名，这通常要求友元类至少已经部分定义，特别是当友元函数是类的成员函数时。这就是为什么在尝试声明`friend_class::visit`为`first_child`的友元时出现了错误，因为编译器在处理`first_child`的定义时还没有遇到`friend_class`的完整定义，包括`visit`函数的声明。

#### static 关键字

> 在面向对象编程中，static 关键字主要分为以下几种用途：
>
> 静态成员变量、静态成员函数、静态局部变量、静态链接和静态持续性

- 静态局部变量：

  这点其实和面向对象编程关系不算很大，因为这在我们面向过程编程中也遇到过

  实现效果就是函数内部的静态局部变量在第一次调用后就初始化，然后生命周期持续到程序结束：这意味着每次进入该函数，静态局部变量都保持着上次离开时的状态

- 静态成员变量：

  其实就是静态局部变量放在了类中，实现的效果类似：程序开始时初始化，静态成员变量一直生存到程序结束

  属于类本身，可以直接通过类进行访问

- 静态成员函数：

  也属于类本身，可以直接通过类进行调用

  同时不能访问类内部的非静态成员（因为static没有this指针，不需要特定实例就能调用）

- 静态链接：

  给当前声明（或定义）增加static关键字会将当前变量或者成员函数限制在当前文件中，其他文件不可访问，否则会报错如下：
  
  ![image-20240217201414958](https://typora-zrx.oss-cn-beijing.aliyuncs.com/img/2024/02/17/20240217-201418.png)

**底层原理：**

上一章说过CPP运行的内存分区，其中的全局区就存储着这些静态变量

同时，静态成员函数也是如此，其原理或者表现形式和全局函数很像，只不过作用域只局限在类内

#### 菱形继承问题

> 问题背景：一个类通过两条路径继承自同一个基类（继承路径中出现环了）
>
> ```markdown
> 	Base
>    /    \
> Derived1 Derived2
>    \    /
>   MostDerived
> ```

**问题严重性：**

如果Base类中有成员变量被Derived1，Derived2同时继承，那么到最后的MostDerived 类就会出现冲突（歧义）

如果进行再次定义的话，很可能会出现数据冗余（因为这个派生类需要一份数据即可）

**解决办法：**虚拟继承

> 底层原理：
>
> 编译器在检测到虚拟继承时，会添加隐藏的虚拟指针和虚拟表
>
> 虚拟指针指向虚拟表，虚拟表包含了指向基类的数据成员的指针
>
> 当派生类继承这两个类时，内部的数据成员会直接指向共同基类的数据成员
>
> 这样就避免了数据冗余和访问歧义

**实现方式：**

```c++
class Derived1 : virtual Base{/**/}
class Derived2 : virtual Base{/**/}
```

---

本来应该再写一点的，但是面向对象应该到这里就结束了

我们下一章再见

### 参考资料

[黑马教程](https://www.bilibili.com/video/BV1et411b73Z?p=134&vd_source=a733c3f0d600237b1444ffb02c86d655)

[菜鸟教程](https://www.runoob.com/cplusplus/cpp-polymorphism.html)

[仓库地址](https://github.com/zrxxzz/CPP_Learning)

[博客地址](https://www.zrxp4ul.com/)
#include<iostream>
#include"my_class.hpp"
using namespace std;

int main(){
    my_class* base_one = new my_class(0);
    //base_one->test_method();
    sub_class* test_one = new sub_class(10);
    my_class stack_value;
    //测试不同初始化(栈内初始化和堆内初始化)
    //cout<<"stack :"<<stack_value.max_size<<endl;
    //测试派生类成员函数
    //cout<<"the value from sub_method: "<<test_one->sub_method()<<endl;
    test_one->sub_method();
    test_one->sub_method(true);
    //(sub_class*)(new my_class(10));
    cout<<"sub_class's value is "<<test_one->get_size()<<endl;
    delete base_one;
    delete test_one;
    return 0;
}


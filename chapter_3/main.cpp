#include "second_class.hpp"
#include "test_static_class.hpp"
using namespace std;
int main(){
    second_class* base_one = new second_class(2023);
    first_child* derived_one = new first_child(2024);
    friend_class* friend_one = new friend_class(100);
    // 测试继承
    // cout<<"here is a public value from derived class:"<< derived_one->public_value<<endl;
    // 测试多态
    // cout<<base_one->test_base_method()<<endl;
    // base_one = &(*derived_one);
    // cout<<base_one->test_base_method()<<endl;
    // cout<<derived_one->test_base_method()<<endl;
    // 测试友元
    // cout<<" the value from friend_one: "<<friend_one->public_value<<endl;
    // friend_one->visit(derived_one);
    // 测试static
    static_class* static_one = new static_class();
    static_class::static_function();
    // 测试函数静态变量
    outside_static_function(10);
    outside_static_function(20);
    delete base_one;
    delete derived_one;
    delete friend_one;
    delete static_one;
    return 0;
}
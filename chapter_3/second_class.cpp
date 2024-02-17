#include "second_class.hpp"

second_class::second_class(int _public_value){
    this->public_value = _public_value;
    this->protected_value = _public_value-1;
}

int second_class::test_base_method(){
    std::cout<<"here is base class "<<std::endl;
    return 0;
}

first_child::first_child(int _public_value):second_class(_public_value){ }

int first_child::test_base_method(){
    std::cout<<"here is child class"<<std::endl;
    return 1;
}

friend_class::friend_class(int _public_value):second_class(_public_value){ 
    this->protected_value=666;
}

void friend_class::visit(first_child* first_child_test){
    std::cout<<"the protecded value from first_child class: "<<first_child_test->protected_value<<std::endl;
}

// 继承接口时，必须要重写纯虚函数
// void first_child::test_pure_virtual_method(){
//     std::cout<<"hello"<<std::endl;
// }
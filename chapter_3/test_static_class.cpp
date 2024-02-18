#include "test_static_class.hpp"
#include <iostream>
void outside_static_function(int tmp_to_add){
    static int outside_static_value=0;//只在第一次调用的时候初始化，之后都不会执行赋值操作
    std::cout<<"hey! the last value is: "<<outside_static_value<<std::endl;
    outside_static_value+=tmp_to_add;
    std::cout<<"hey! now, the value is: "<<outside_static_value<<std::endl;
} 

int static_class::static_value = 2025;

void static_class::static_function(){
    std::cout<<"hey! here is a static value from static_class: "<<static_value<<std::endl;
}
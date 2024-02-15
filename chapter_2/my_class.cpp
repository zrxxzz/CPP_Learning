#include "my_class.hpp"

char my_class::test_method(){
    std::cout<<"here is private value: "<<this->secret<<std::endl;
    return this->secret[0];
}

my_class::my_class(int _size){
    this->max_size=_size;
    this->secret='A';
}

my_class::my_class(){
    this->max_size=100;
    this->secret='A';
}

my_class::~my_class(){
}

sub_class::sub_class(int _size): my_class(_size){
}

int sub_class::get_size(){
    return this->max_size;
}

int sub_class::sub_method(){
    return test_method();
}
void sub_class::sub_method(bool flag){
    if(flag)std::cout<<"here is a overload test: "<<flag<<std::endl;
}
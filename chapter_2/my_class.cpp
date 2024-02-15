#include "my_class.hpp"

void my_class::test_method(){
    std::cout<<"here is private value: "<<this->secret<<std::endl;
}

my_class::my_class(int _size){
    this->max_size=_size;
    this->secret='A';
}

my_class::~my_class(){
}

sub_class::sub_class(int _size): my_class(_size){
}

int sub_class::get_size(){
    return this->max_size;
}

#include "my_class.hpp"

void my_class::test_method(){

}

my_class::my_class(int _size){
    this->max_size=_size;
    std::cout<<this->secret;
}

my_class::~my_class(){
}

sub_class::sub_class(int _size): my_class(_size){
}

int sub_class::get_size(){
    return this->max_size;
}

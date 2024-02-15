#include<iostream>
#include"my_class.hpp"
using namespace std;

int main(){
    my_class* base_one = new my_class(0);
    base_one->test_method();
    sub_class* test_one = new sub_class(10);
    //(sub_class*)(new my_class(10));
    cout<<"sub_class's value is "<<test_one->get_size()<<endl;
    return 0;
}


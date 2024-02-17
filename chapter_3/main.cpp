#include "second_class.hpp"
using namespace std;
int main(){
    second_class* base_one = new second_class(2023);
    first_child* derived_one = new first_child(2024);
    friend_class* friend_one = new friend_class(100);
    // cout<<base_one->test_base_method()<<endl;
    // base_one = &(*derived_one);
    // cout<<base_one->test_base_method()<<endl;
    // cout<<derived_one->test_base_method()<<endl;
    cout<<" the value from friend_one: "<<friend_one->public_value<<endl;
    friend_one->visit(derived_one);
    delete base_one;
    delete derived_one;
    delete friend_one;
    return 0;
}
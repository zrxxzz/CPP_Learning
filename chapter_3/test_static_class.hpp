#ifndef TEST_STATIC_CLASS_H
#define TEST_STATIC_CLASS_H
#include <iostream>

class static_class{
private:
    int private_value;
public:
    static_class()=default;
    ~static_class()=default;
    static int static_value;
    static void static_function();
    
};
void outside_static_function(int tmp_to_add);
#endif
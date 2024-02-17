#ifndef MYCLASS_H
#define MYCLASS_H
#include <string>
#include <iostream>
class my_class
{
private:
    /* data */
    std::string secret;
public:
    int max_size;
    int signal;
    char test_method();
    my_class();
    my_class(int _size);
    ~my_class()=default;
};

class sub_class : public my_class{
public:
    sub_class(int _size);
    ~sub_class()=default;
    int get_size();
    int sub_method();
    void sub_method(bool flag);
};


#endif

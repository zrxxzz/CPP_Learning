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
    void test_method();
    my_class(int _size);
    ~my_class();
};

class sub_class : public my_class{
public:
    sub_class(int _size);
    int get_size();
};


#endif

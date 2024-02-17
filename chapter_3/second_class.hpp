#ifndef SECOND_CLASS_H
#define SECOND_CLASS_H
#include <iostream>

class second_class{
private:
    int private_value;
protected:
    int protected_value;
public:
    int public_value;
    second_class(int _public_value);
    ~second_class()=default;
    int public_base_method();
    virtual int test_base_method();
    //纯虚函数定义后，该类成为接口（抽象类）无法实例化
    //virtual void test_pure_virtual_method()=0;
};

class first_child :public second_class{
public:
    first_child(int _public_value);
    ~first_child()=default;
    int test_base_method() override;
    //friend void friend_class::visit(first_child* first_child_test);
    friend class friend_class;
    //void test_pure_virtual_method() override;
};

class friend_class :public second_class{
public:
    void visit(first_child* first_child_test);
    friend_class();
    friend_class(int _public_value);
    ~friend_class()=default;
};



#endif
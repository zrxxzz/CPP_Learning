#ifndef SIMPLE_SHARED_PTR_H
#define SIMPLE_SHARED_PTR_H
#include <iostream>

template <typename T>
class simpleSharedPtr{
private:
    T* _ptr; //指针
    size_t* _count;//引用计数

    void release(){
        if(_count&& --(*_count)==0){
            delete _ptr;
            delete _count;
            std::cout<<"testing over!!"<<std::endl;
        }
    };

public:
    explicit simpleSharedPtr(T* ptr = nullptr) : _ptr(ptr),_count(ptr ? new size_t(1):nullptr){}
    
    simpleSharedPtr(const simpleSharedPtr& other) : _ptr(other._ptr),_count(other._count){
        if(_count){
            ++(* _count);
        }
    }

    simpleSharedPtr& operator=(const simpleSharedPtr& other){
        if(this!=&other){
            release();
            _ptr=other._ptr;
            _count=other._count;
            if(_count){
                ++(*_count);
            }
        }
        return *this;
    }
    
    ~simpleSharedPtr() {
        if (_count != nullptr) {
            std::cout << "the " << *_count << " one comes to the end!!!" << std::endl;
        } else {
            std::cout << "Pointer already reset or never initialized." << std::endl;
        }
        release();
    }


    T& operator*(){return *_ptr;}
    T* operator->(){return _ptr;}
    T* get()const {return _ptr;}
    size_t use_count()const{ return _count?*_count:0;}

    void reset(T* ptr=nullptr){
        release();
        if(ptr){
            this->_ptr=ptr;
            this->_count= new size_t(1);
        }else{
            this->_ptr=nullptr;
            this->_count=nullptr;
        }
    }
};


#endif
#ifndef TEMPLATE_CLASS_H
#define TEMPLATE_CLASS_H
#include <vector>
#include <stdexcept>
template <typename T>
const T& MIN(const T& a,const T& b){
    return a<b?a:b;
}

template <class T>
class template_test
{
    private:
        std::vector<T> elems;
        /* data */
    public:
        void push(const T&);
        void pop();
        const T top();
        const bool empty(){return elems.empty();};
};

template <class T>
void template_test<T>::push(const T& elem){
    elems.push_back(elem);
}

template <class T>
void template_test<T>::pop(){
    if(elems.empty()){
        throw std::out_of_range("you can't pop cause it's empty");
    }
    elems.pop_back();
}

template <class T>
const T template_test<T>::top(){
    if (elems.empty()) { 
        throw std::out_of_range("Stack<>::top(): empty stack"); 
    }
    return elems.back();
}




#endif
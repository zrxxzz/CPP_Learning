#include <iostream>
#include "mingw.future.h"
#include "mingw.thread.h"
#include <chrono>

using namespace std;
class test{
public:
    int val;
    int num;
    int* ptr;
    void setval(int _val){
        this->ptr=new int(_val);
    }
    test(int a,int b) : val(a),num(b){
    }
    test(const test& other){
        ptr = new int(*other.ptr);
    }
    ~test(){
        delete ptr;
        cout<<"now its coming to the end"<<endl;
    }
    friend int get_pri_val(const test& rect);
    friend ostream &operator<<(ostream &output, const test &rect);
private:
    int sval=6666;
};


int get_pri_val(const test& rect){
        return rect.sval;
    }

ostream &operator<<(ostream &output, const test &rect){
    output<<"public: "<<rect.num<<"private: "<<rect.sval;
    return output;
}

int main(){
    

    auto mytest = new test(5,10);
    
    mytest->setval(6);
    auto another_test = new test(*mytest);
    another_test->setval(33);
    // cout<<*mytest->ptr<<" "<<*another_test->ptr<<endl;
    
    auto ref_capture = [&mytest]() {
        // 模拟延迟，增加悬空引用发生的可能性
        this_thread::sleep_for(chrono::seconds(1));
        //cout << *mytest->ptr << endl; // 访问悬空引用的风险
    };
    
    auto future = async(launch::async, ref_capture);

    //cout<<"private_value: "<<get_pri_val(*mytest)<<endl;
    cout<< *mytest <<endl;

    delete mytest;
    delete another_test;
    future.get();
    return 0;
}


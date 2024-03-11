#include <iostream>
#include <vector>
#include <string>
#include <mutex>
#include <thread>
#include "simple_shared_ptr.hpp"
std::mutex mtx;
int counter =0;
void try_increase_counter_with_lock_guard() {
    // std::lock_guard<std::mutex> guard(mtx); // 如果不加的话，会出现线程抢占公共资源情况
    std::unique_lock<std::mutex> ulock(mtx); // unique_lock 和 lock_guard 二选一
    ulock.unlock();
    ++counter; 
    std::cout << std::this_thread::get_id() << " increased counter to " << counter << std::endl;
}
int main(){
    /*测试vector*/
    // std::vector<int> test;
    // std::cout<<test.capacity()<<std::endl;
    // for(int i=0;i<20;i++){
    //     test.push_back(i);
    //     std::cout<<i<<": "<<test.capacity()<<std::endl;
    // }
    /*测试string*/
    // std::string strTest;
    // std::cout<<strTest.capacity()<<std::endl;
    // for(int i=0;i<20;i++){
    //     strTest.append("c");
    //     std::cout<<i<<": "<<strTest.capacity()<<std::endl;
    // }
    /*测试锁*/
    // std::vector<std::thread> threads;
    // for (int i = 0; i < 10; ++i) {
    //     threads.push_back(std::thread(try_increase_counter_with_lock_guard));
    // }

    // for (auto& th : threads) {
    //     th.join();
    // }
    /*测试手写的shared_ptr*/
    {
        simpleSharedPtr<int> test(new int(10));
        std::cout<<"now the count is: "<<test.use_count()<<std::endl;
        std::cout<<"the test ptr is: "<<test.get()<<std::endl;
        simpleSharedPtr<int> other1=test;
        std::cout<<"now the count is: "<<test.use_count()<<std::endl;
        // delete &other1; //会出现double free 问题
        other1.reset();
        simpleSharedPtr<int> other2(test);
        std::cout<<"now the count is: "<<test.use_count()<<std::endl;
        std::cout<<"now the value is: "<<*test<<std::endl;
        
    }
    
    return 0;
}
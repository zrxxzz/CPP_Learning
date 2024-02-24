#ifndef MULTI_THREAD_H
#define MULTI_THREAD_H
#include <iostream>
#include <thread>
void* pthread_test(void *thread_id){
    std::cout<<"here is a message from posix thread: "<<*((int*)thread_id) <<std::endl;
    return 0;
}

void std_thread_test(int i){
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout<<"here is a message from std thread: "<<i<<std::endl;
}

#endif
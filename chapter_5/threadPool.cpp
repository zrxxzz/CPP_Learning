#include "threadPool.hpp"

threadPool::threadPool(size_t threads): stop(false){
    for(size_t i=0;i<threads;++i){
        workers.emplace_back(
            [this]{
                while (true){
                    std::function<void()> task;
                    {   
                        std::unique_lock<std::mutex> u_lock(this->queue_mutex);
                        this->condition.wait(u_lock,
                            [this]{return this->stop||!this->tasks.empty();});
                        if(this->stop&&this->tasks.empty()) return;
                        task=tasks.front();tasks.pop();
                    }
                    task();
                }
            }
        );
    }
}


threadPool::~threadPool(){
    {
        std::unique_lock<std::mutex> u_lock(queue_mutex);
        stop=true;
    }
    condition.notify_all();
    for(std::thread& worker:workers){
        worker.join();
    }
}
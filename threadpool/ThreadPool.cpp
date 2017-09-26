//
// Created by GlebDrozdov on 24.09.2017.
//

#include "ThreadPool.h"
#include <iostream>

ThreadPool::ThreadPool(size_t num_threads) {
    for (size_t i = 0; i < num_threads; ++i) {
        //fill our vector by threads
        _workers.emplace_back(&ThreadPool::do_function, this);
    }
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(_mutex);
        // _mutex.lock();
        _stop = true;
        // _mutex.unlock();
    }
    _condition.notify_all();

    for (auto &_worker : _workers)
        _worker.join();
}

void ThreadPool::do_function() {

    std::function<void()> task;
    while (true) {
        std::unique_lock<std::mutex> lock(_mutex);

        while (!_stop && tasks.empty()) {
            _condition.wait(lock);//deadlock произойдёт , потому что поток ожидает пробуждения, а он залочен
        }

        if(!tasks.empty()) {
            task = tasks.front();
            tasks.pop();
            lock.unlock();
            task();
        }
        if (_stop) {
            break;
        }

    }
}


void ThreadPool::execute(std::function<void()> const &foo) {
    std::unique_lock<std::mutex> lock(_mutex);
    tasks.push(foo);
    _condition.notify_one();

}

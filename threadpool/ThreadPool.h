//
// Created by GlebDrozdov on 24.09.2017.
//

#ifndef CPP_UNIVERSITY_COURSE_THREADPOOL_H
#define CPP_UNIVERSITY_COURSE_THREADPOOL_H


#include <cstdio>
#include <functional>
#include <thread>
#include <queue>
#include <atomic>
#include <mutex>
#include <condition_variable>

class ThreadPool {

public:
    explicit ThreadPool(size_t num_threads);

    ~ThreadPool();

    void execute(std::function<void()> const &foo);


private:
    void do_function();

    std::vector<std::thread> _workers;
    std::queue<std::function<void()>> tasks;
    std::mutex _mutex;
    std::condition_variable _condition;
    bool _stop;


};

/*
 * ThreadPool(size_t num_threads);
~ThreadPool();
void execute(std::function<void()> const & foo);
};*/



#endif //CPP_UNIVERSITY_COURSE_THREADPOOL_H

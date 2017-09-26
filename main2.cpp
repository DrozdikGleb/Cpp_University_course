//
// Created by GlebDrozdov on 26.09.2017.
//
#include <c++/iostream>
#include <c++/thread>
#include "future_and_promise/Future.h"
#include "future_and_promise/Promise.h"
#include "future_and_promise/Shared_State.h"


Promise<int> promise;

void f1() {
   // promise.set(10);
    std::exception_ptr e;
    promise.setException(e);
    Future<int> future = promise.getFuture();
    try {
        future.get();

    }catch (...){
        std::cout<<"smth wrong";
    }


}

void f2() {
   // std::cout << promise.getFuture().get();
}

int main() {
    std::thread thread1(f1);
    //std::thread thread2(f2);
    thread1.join();
   // thread2.join();

    return 0;
}
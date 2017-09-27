//
// Created by GlebDrozdov on 26.09.2017.
//
#include <c++/iostream>
#include <c++/thread>
#include "future_and_promise/Future.h"
#include "future_and_promise/Promise.h"




void f1() {
   // promise.set(10);
    //check double set value
    Promise<int> promise;
    try {
        promise.set(10);
        promise.set(10);
    }
    catch (std::exception const &exception){
        std::cout<<exception.what()<<'\n';
    }

    //check set exception method
    Promise<int> promise2;
    std::exception_ptr e;
    promise2.setException(e);
    Future<int> future2 = promise2.getFuture();
    try {
        future2.get();
    }
    catch (...) {
        std::cout << "was error\n";
    }

   /* Future <int> future2;
    future2.get();*/


}


int main() {
    std::thread thread1(f1);
    //std::thread thread2(f2);
    thread1.join();
   // thread2.join();

    return 0;
}
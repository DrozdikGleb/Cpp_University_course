//
// Created by GlebDrozdov on 26.09.2017.
//
#include <c++/iostream>
#include <c++/thread>
#include "future_and_promise/Future.h"
#include "future_and_promise/Promise.h"




void f1() {
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
    catch (std::exception const &exception2) {
        std::cout <<exception2.what()<<'\n' ;
    }
 //check execution get method without promise
    Future <int> future3;
    try {
        future3.get();
    }catch(std::exception const &exception1){
        std::cout<<exception1.what()<<'\n';
    }

    Future <int> future4;
    Promise <int>promise4;
    promise4.set(10);

    promise4.getFuture()




}


int main() {
    std::thread thread1(f1);
    //std::thread thread2(f2);
    thread1.join();
   // thread2.join();

    return 0;
}
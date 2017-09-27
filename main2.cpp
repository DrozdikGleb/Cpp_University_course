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
    catch (std::exception const &exception) {
        std::cout << exception.what() << '\n';
    }

    //check set exception method
    Promise<int> promise2;
    Future<int> future2 = promise2.getFuture();
    try {
        std::string("abc").substr(10);
    } catch (...) {
        promise2.setException(std::current_exception());
    }
    try {
        future2.get();
    }
    catch (std::exception const &exception2) {
        std::cout << exception2.what() << '\n';
    }
    //check execution get method without promise
    try {
        Future<int> future3;
        future3.get();
    } catch (std::exception const &exception2) {
        std::cout << exception2.what() << '\n';
    }

    //simple example of promise and future
    Promise<int> promise4;
    promise4.set(10);
    std::cout << promise4.getFuture().get();


}

int main() {
    std::thread thread1(f1);
    thread1.join();
    return 0;
}
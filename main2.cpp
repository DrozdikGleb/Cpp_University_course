//
// Created by GlebDrozdov on 26.09.2017.

#include <c++/iostream>
#include <c++/thread>
#include <c++/future>

#include "future_and_promise/Future.h"
#include "future_and_promise/Promise.h"


void f1() {
    //check double set value
    std::cout<<"check double set value"<<'\n';
    Promise<int> promise;
    try {
        promise.set(10);
        promise.set(10);
    }
    catch (std::exception const &exception) {
        std::cout << exception.what() << '\n';
    }
    std::cout<<"/////////////////////"<<'\n';
    //check set exception method
    std::cout<<"check set exception method"<<'\n';
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
    std::cout<<"/////////////////////"<<'\n';

    //simple example of promise and future
    std::cout<<"simple example of promise and future"<<'\n';
    Promise<int> promise4;
    promise4.set(10);
    std::cout << promise4.getFuture().get();


}
int main() {
    Promise<int&> p;

    std::thread thread1(f1);
    thread1.join();
    return 0;
}
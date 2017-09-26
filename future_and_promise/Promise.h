//
// Created by GlebDrozdov on 24.09.2017.
//

#ifndef CPP_UNIVERSITY_COURSE_PROMISE_H
#define CPP_UNIVERSITY_COURSE_PROMISE_H


#include <c++/exception>
#include "Shared_State.h"
#include "Future.h"

template <typename T>
class Promise {

    Shared_State <T> *state_ptr;

public:
    Promise(Promise &&) = default;
    Promise &operator= (Promise &&) = default;

    Promise(Promise &) = delete;
    Promise &operator= (Promise &) = delete;
    Promise();
    ~Promise();
    Future<T> getFuture();
    void set(const T&);
    void set(const T&&);
    void setException(const std::exception_ptr &);

};
template<typename T>
Future <T> Promise<T>::getFuture() {
    std::unique_lock<std::mutex> lock(state_ptr->mutex);
    return Future<T>(state_ptr);
}

template<typename T>
Promise<T>::Promise() {
    state_ptr = new Shared_State<T>();
    state_ptr->promise_exists = true;
}
template <typename T>
Promise<T>::~Promise() {
    state_ptr->promise_exists = false;
    state_ptr->was_error=false;
}

template<typename T>
void Promise<T>::set(const T &value) {
    std::unique_lock<std::mutex> lock(state_ptr->mutex);
    if(state_ptr->is_Ready){
        throw std::runtime_error("value already set");
    }
    state_ptr->value = value;
    state_ptr->is_Ready = true;
    state_ptr->condiional_variable.notify_one();
}

template<typename T>
void Promise<T>::set(const T &&value) {
    set(value);
}

template <typename T>
void Promise<T>::setException(const std::exception_ptr & e) {
    std::unique_lock<std::mutex> lock(state_ptr->mutex);
    state_ptr->error=e;
    state_ptr->was_error=true;
}


#endif //CPP_UNIVERSITY_COURSE_PROMISE_H

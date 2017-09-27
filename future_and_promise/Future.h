//
// Created by GlebDrozdov on 24.09.2017.
//
#include <c++/iostream>
#include "Shared_State.h"

#ifndef CPP_UNIVERSITY_COURSE_FUTURE_H
#define CPP_UNIVERSITY_COURSE_FUTURE_H

template<typename T>
class Promise;

template<typename T>
class Future {

    friend class Promise<T>;

    Shared_State<T> *state_ptr;

    explicit Future(Shared_State<T> *ptr) {
        state_ptr = ptr;
    }

public:
    Future(Future &&) = default;
    //Future& operator=(Future &&) = default;

    Future(Future const &) = delete;
    //Future &operator= (Future const &) = delete;


    T get() const;

    bool isReady() const;

    void wait() const;

};

template<typename T>
T Future<T>::get() const {
    if (state_ptr->was_error) {
        throw state_ptr->error;
    }
    wait();
    return state_ptr->value;
}

template<typename T>
bool Future<T>::isReady() const {
    return state_ptr->is_Ready;
}

template<typename T>
void Future<T>::wait() const {
    std::unique_lock<std::mutex> lock(state_ptr->mutex);
    if (state_ptr->is_Ready) {
        return;
    }
    if (!state_ptr->promise_exists) {
        throw std::runtime_error("promise doesnt exists");
    }
    state_ptr->condiional_variable.wait(lock);
}


#endif //CPP_UNIVERSITY_COURSE_FUTURE_H

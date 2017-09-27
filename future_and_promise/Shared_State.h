//
// Created by GlebDrozdov on 26.09.2017.
//

#ifndef CPP_UNIVERSITY_COURSE_SHARED_STATE_H
#define CPP_UNIVERSITY_COURSE_SHARED_STATE_H

#include <c++/mutex>
#include <c++/condition_variable>
#include <c++/atomic>

template<typename T>
struct Shared_State {
    std::mutex mutex;
    std::condition_variable condiional_variable;
    std::exception_ptr error;
    T value;
    std::atomic_bool has_Value;

    Shared_State() {
        has_Value = false;
    }
};

#endif //CPP_UNIVERSITY_COURSE_SHARED_STATE_H

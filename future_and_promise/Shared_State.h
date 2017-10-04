//
// Created by GlebDrozdov on 26.09.2017.
//

#ifndef CPP_UNIVERSITY_COURSE_SHARED_STATE_H
#define CPP_UNIVERSITY_COURSE_SHARED_STATE_H

#include <c++/mutex>
#include <c++/condition_variable>
#include <c++/atomic>
template<typename>
class Promise;

template<typename>
class Future;

class State {
public:
    std::exception_ptr error;
    std::mutex mutex;
    std::condition_variable condiional_variable;
    std::atomic_bool has_Value;
};

template<typename T>
class Shared_State : public State {
public:
    T value;
};


template<>
class Shared_State<void> : public State {
};

template<typename T>
class Shared_State<T &> : public State {
public:
    T *value;
};

#endif //CPP_UNIVERSITY_COURSE_SHARED_STATE_H

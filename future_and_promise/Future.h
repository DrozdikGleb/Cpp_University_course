//
// Created by GlebDrozdov on 24.09.2017.
//
#include <c++/iostream>
#include "Shared_State.h"

#ifndef CPP_UNIVERSITY_COURSE_FUTURE_H
#define CPP_UNIVERSITY_COURSE_FUTURE_H
template<typename T>
class Future {

private:
    friend class Promise<T>;

    std::shared_ptr<Shared_State<T>> state_ptr = nullptr;

    explicit Future(std::shared_ptr<Shared_State<T>> ptr) {
        state_ptr = ptr;
    }


public:
    Future(Future<T> &&future)noexcept : state_ptr(std::move(future.state_ptr)) {
    };

    Future &operator=(Future<T> &&future) noexcept {
        state_ptr = std::move(future.state_ptr);
        return *this;
    };

    Future(Future const &) = delete;

    Future &operator=(Future const &) = delete;


    T get() const {
        if (state_ptr == nullptr) {
            throw std::runtime_error("value is not set and promise doesn't exist");
        }
        wait();
        if (state_ptr->error) {
            std::rethrow_exception(state_ptr->error);
        }
        return state_ptr->value;
    };

    bool isReady() const {
        return state_ptr->has_Value;
    };

    void wait() const {
        if (state_ptr->has_Value) {
            return;
        }
        std::unique_lock<std::mutex> lock(state_ptr->mutex);
        while (!state_ptr->has_Value) {
            state_ptr->condiional_variable.wait(lock);
        }
    };

};

template<typename T>
class Future<T &> {

private:
    friend class Promise<T &>;

    std::shared_ptr<Shared_State<T&>> state_ptr = nullptr;

    explicit Future(std::shared_ptr<Shared_State<T&>> ptr) {
        state_ptr = ptr;
    }

public:
    Future(Future &&future) noexcept {
        state_ptr = std::move(future.state_ptr);
    };

    Future &operator=(Future &&future) noexcept {
        *this = std::move(future);
        return *this;
    };

    Future(Future const &) = delete;

    Future &operator=(Future const &) = delete;

    T &get() const {
        if (state_ptr == 0) {
            throw std::runtime_error("value is not set and promise doesn't exist");
        }
        if (state_ptr->error) {
            std::rethrow_exception(state_ptr->error);
        }
        wait();
        return *state_ptr->value;
    };

    bool isReady() const {
        return state_ptr->has_Value;
    };

    void wait() const {
        if (state_ptr->has_Value) {
            return;
        }
        std::unique_lock<std::mutex> lock(state_ptr->mutex);
        while (!state_ptr->has_Value) {
            state_ptr->condiional_variable.wait(lock);
        }
    };

};

template<>
class Future<void> {

private:
    friend class Promise<void>;

    std::shared_ptr<Shared_State<void>> state_ptr = nullptr;

    explicit Future(std::shared_ptr<Shared_State<void>> ptr) {
        state_ptr = std::move(ptr);
    }

public:
    Future(Future &&future) noexcept {
        state_ptr = std::move(future.state_ptr);
    };

    Future& operator=(Future &&future) noexcept {
        state_ptr = std::move(future.state_ptr);
        return *this;
    }

    Future(Future const &) = delete;

    Future &operator=(Future const &) = delete;

    void get() const {
        if (state_ptr == nullptr) {
            throw std::runtime_error("value is not set and promise doesn't exist");
        }
        if (state_ptr->error) {
            std::rethrow_exception(state_ptr->error);
        }
        wait();
    };

    bool isReady() const {
        return state_ptr->has_Value;
    };

    void wait() const {
        if (state_ptr->has_Value) {
            return;
        }
        std::unique_lock<std::mutex> lock(state_ptr->mutex);
        while (!state_ptr->has_Value) {
            state_ptr->condiional_variable.wait(lock);
        }
    };

};




#endif //CPP_UNIVERSITY_COURSE_FUTURE_H

//
// Created by GlebDrozdov on 24.09.2017.
//

#ifndef CPP_UNIVERSITY_COURSE_PROMISE_H
#define CPP_UNIVERSITY_COURSE_PROMISE_H


#include <c++/exception>
#include "Shared_State.h"
#include "Future.h"


template<typename T>
class Promise {
private:
    std::shared_ptr<Shared_State<T>> state_ptr = nullptr;

public:

    Promise(Promise &&promise) noexcept : state_ptr(std::move(promise.state_ptr)) {
        state_ptr->has_promise = true;
    };

    Promise &operator=(Promise &&promise) noexcept {
        state_ptr = std::move(promise.state_ptr);
        state_ptr->has_promise = true;
        return *this;
    };

    Promise(Promise const &) = delete;

    Promise &operator=(Promise const &) = delete;

    Promise() : state_ptr(std::make_shared<Shared_State<T>>()) {
        state_ptr->has_promise=true;
    };

    Future<T> getFuture() {
        return Future<T>(state_ptr);
    };

    ~Promise() {
        if(state_ptr) {
            state_ptr->has_promise = false;
            state_ptr->condiional_variable.notify_one();
        }
    }

    void set(const T &value) {
        std::unique_lock<std::mutex> lock(state_ptr->mutex);
        state_ptr->value = value;
        if (state_ptr->has_Value) {
            throw std::runtime_error("value already set");
        }
        state_ptr->has_Value = true;
        state_ptr->condiional_variable.notify_one();
    };

    void set(T &&value) {
        std::unique_lock<std::mutex> lock(state_ptr->mutex);
        if (state_ptr->has_Value) {
            throw std::runtime_error("value already set");
        }
        state_ptr->value = std::move(value);
        state_ptr->has_Value = true;
        state_ptr->condiional_variable.notify_one();
    };

    void setException(const std::exception_ptr &e) {
        std::unique_lock<std::mutex> lock(state_ptr->mutex);
        if (state_ptr->error != nullptr) {
            throw std::runtime_error("exception already set");
        }
        state_ptr->error = e;
        state_ptr->has_Value = true;
        state_ptr->condiional_variable.notify_one();
    };

};

template<typename T>
class Promise<T &> {
private:
    std::shared_ptr<Shared_State<T &>> state_ptr = nullptr;

public:
    Promise(Promise &&promise)noexcept {
        state_ptr = std::move(promise.state_ptr);
    };

    Promise &operator=(Promise &&promise)noexcept {
        state_ptr = std::move(promise.state_ptr);
        return *this;
    };

    Promise(Promise const &) = delete;

    Promise &operator=(Promise const &) = delete;

    Promise() : state_ptr(std::make_shared<Shared_State<T &>>()) {
    };

    Future<T &> getFuture() {
        std::unique_lock<std::mutex> lock(state_ptr->mutex);
        return Future<T &>(state_ptr);
    };

    void set(T &value) {
        std::unique_lock<std::mutex> lock(state_ptr->mutex);
        if (state_ptr->has_Value) {
            throw std::runtime_error("value already set");
        }
        state_ptr->value = &value;
        state_ptr->has_Value = true;
        state_ptr->condiional_variable.notify_one();
    };

    void setException(const std::exception_ptr &e) {
        std::unique_lock<std::mutex> lock(state_ptr->mutex);
        state_ptr->error = e;
    };

};

template<>
class Promise<void> {
private:
    std::shared_ptr<Shared_State<void>> state_ptr = nullptr;

public:
    Promise(Promise &&promise)noexcept {
        state_ptr = std::move(promise.state_ptr);
    };

    Promise &operator=(Promise &&promise)noexcept {
        state_ptr = std::move(promise.state_ptr);
        return *this;
    };

    Promise(Promise const &) = delete;

    Promise &operator=(Promise const &) = delete;

    Promise() : state_ptr(std::make_shared<Shared_State<void>>()) {
    };

    ~Promise() {
        state_ptr->has_promise = false;
    }

    Future<void> getFuture() {
        std::unique_lock<std::mutex> lock(state_ptr->mutex);
        return Future<void>(state_ptr);
    };

    void set() {
        std::unique_lock<std::mutex> lock(state_ptr->mutex);
        if (state_ptr->has_Value) {
            throw std::runtime_error("value already set");
        }
        state_ptr->has_Value = true;
        state_ptr->condiional_variable.notify_one();
    };

    void setException(const std::exception_ptr &e) {
        std::unique_lock<std::mutex> lock(state_ptr->mutex);
        state_ptr->error = e;
    };

};








#endif //CPP_UNIVERSITY_COURSE_PROMISE_H

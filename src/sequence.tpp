#pragma once

#include <stdexcept>
#include "sequence.hpp"

template <typename T>
Sequence<T>* Sequence<T>::map(T(*mapper)(const T& elem)) const {
    ISequenceBuilder<T>* builder = this->create_builder();
    IEnumerator<T>* it = this->get_enumerator();

    try {
        while (it->move_next()) {
            builder->append(mapper(it->get_current()));
        }
        Sequence<T>* result = builder->build();
        delete it;
        delete builder;
        return result;
    }
    catch (...) {
        delete it;
        delete builder;
        throw;
    }
}

template <typename T>
T Sequence<T>::reduce(T(*reducer)(const T&, const T&), const T& initial_value) const {
    T result = initial_value;
    IEnumerator<T>* it = this->get_enumerator();

    try {
        while (it->move_next()) {
            result = reducer(it->get_current(), result);
        }
        delete it;
        return result;
    }
    catch (...) {
        delete it;
        throw;
    }
}

template <typename T>
Sequence<T>* Sequence<T>::where(bool (*predicate)(const T&)) const {
    ISequenceBuilder<T>* builder = this->create_builder();
    IEnumerator<T>* it = this->get_enumerator();

    try {
        while (it->move_next()) {
            const auto& item = it->get_current();
            if (predicate(item)) {
                builder->append(item);
            }
        }
        Sequence<T>* result = builder->build();
        delete it;
        delete builder;
        return result;
    }
    catch (...) {
        delete it;
        delete builder;
        throw;
    }
}

template <typename T>
Sequence<T>* Sequence<T>::get_subsequence(int start_index, int end_index) const {
    int len = this->get_size();
    if (start_index < 0 || start_index >= len || end_index < 0 || end_index >= len || start_index > end_index) {
        throw std::out_of_range("GetSubsequence: index out of range");
    }

    ISequenceBuilder<T>* builder = this->create_builder();
    IEnumerator<T>* it = this->get_enumerator();

    try {
        int current_index = 0;
        while (it->move_next()) {
            const auto& item = it->get_current();
            if (current_index >= start_index && current_index <= end_index) {
                builder->append(item);
            }
            if (current_index > end_index) break;
            current_index++;
        }
        Sequence<T>* result = builder->build();
        delete it;
        delete builder;
        return result;
    }
    catch (...) {
        delete it;
        delete builder;
        throw;
    }
}

template <typename T>
Sequence<T>* Sequence<T>::concat(const Sequence<T>* other) const {
    if (!other) return this->clone();

    ISequenceBuilder<T>* builder = this->create_builder();
    IEnumerator<T>* it1 = this->get_enumerator();
    IEnumerator<T>* it2 = nullptr;

    try {
        while (it1->move_next()) {
            builder->append(it1->get_current());
        }
        delete it1;
        it1 = nullptr;

        it2 = other->get_enumerator();
        while (it2->move_next()) {
            builder->append(it2->get_current());
        }
        delete it2;
        it2 = nullptr;

        Sequence<T>* result = builder->build();
        delete builder;
        return result;
    }
    catch (...) {
        if (it1) delete it1;
        if (it2) delete it2;
        delete builder;
        throw;
    }
}

template <class T>
Option<T> Sequence<T>::try_get(int index) const {
    if (index < 0 || index >= this->get_size()) {
        return Option<T>();
    }
    return Option<T>(this->get(index));
}

template <class T>
Option<T> Sequence<T>::try_get_first() const {
    return this->try_get(0);
}

template <class T>
Option<T> Sequence<T>::try_get_last() const {
    return this->try_get(this->get_size() - 1);
}



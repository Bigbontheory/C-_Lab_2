#pragma once

#include "listsequence.hpp"

template <typename T>
ListSequence<T>::ListSequence() : items(new LinkedList<T>()) {}

template <typename T>
ListSequence<T>::ListSequence(T* data, int count) : items(new LinkedList<T>(data, count)) {
}

template <typename T>
ListSequence<T>::ListSequence(const LinkedList<T>& list): items(new LinkedList<T>(list)) {
}

template <typename T>
ListSequence<T>::ListSequence(const ListSequence<T>& other): items(new LinkedList<T>(*(other.items))) {
}

template <typename T>
ListSequence<T>::~ListSequence() {
    delete items;
}

template <typename T>
int ListSequence<T>::get_size() const {
    return items->get_size();
}

template <typename T>
Sequence<T>* ListSequence<T>::append_internal(const T& item) {
    items->append(item);
    return this;
}

template <typename T>
Sequence<T>* ListSequence<T>::prepend_internal(const T& item) {
    items->prepend(item);
    return this;
}

template <typename T>
Sequence<T>* ListSequence<T>::insert_at_internal(const T& item, int index) {
    if (index < 0 || index > this->get_size()) {
        throw std::out_of_range("Index out of range");
    }
    items->insert_at(item, index);
    return this;
}

template <typename T>
Sequence<T>* ListSequence<T>::append(const T& item) {
    return this->instance()->append_internal(item);
}

template <typename T>
Sequence<T>* ListSequence<T>::prepend(const T& item) {
    return this->instance()->prepend_internal(item);
}

template <typename T>
Sequence<T>* ListSequence<T>::insert_at(const T& item, int index) {
    return this->instance()->insert_at_internal(item, index);
}

template <typename T>
Sequence<T>* ListSequence<T>::remove_at(int index) {
    if (index < 0 || index >= this->get_size()) {
        throw std::out_of_range("Index out of range");
    }
    items->remove_at(index);
    return this;
}

template <typename T>
const T& ListSequence<T>::operator[](int index) const {
    return this->get(index);
}

template <typename T>
const T& ListSequence<T>::get_first() const {
    if (this->get_size() == 0) {
        throw std::out_of_range("Index out of range");
    }
    return items->get_first();
}

template <typename T>
const T& ListSequence<T>::get_last() const {
    if (this->get_size() == 0) {
        throw std::out_of_range("Index out of range");
    }
    return items->get_last();
}

template <typename T>
const T& ListSequence<T>::get(int index) const {
    if (index < 0 || index >= this->get_size()) {
        throw std::out_of_range("Index out of range");
    }
    return items->get(index);
}



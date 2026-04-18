#pragma once

#include "arraysequence.hpp"
#include <stdexcept>

template <class T>
class ArrayEnumerator : public IEnumerator<T> {
private:
    const ArraySequence<T>* sequence;
    int current_index;

public:
    explicit ArrayEnumerator(const ArraySequence<T>* seq) : sequence(seq), current_index(-1) {}
    bool move_next() override {
        if (current_index + 1 < sequence->get_size()) {
            current_index++;
            return true;
        }
        else {
            current_index = sequence->get_size();
            return false;
        }
    }
    const T& get_current() const override {
        if (current_index < 0 || current_index >= sequence->get_size()) {
            throw std::out_of_range("IEnumerator: (call move_next() first)");
        }
        return sequence->get(current_index);
    }

    void reset() override {
        current_index = -1;
    }
};

template <class T>
IEnumerator<T>* ArraySequence<T>::get_enumerator() const {
    return new ArrayEnumerator<T>(this);
}

template <typename T>
ArraySequence<T>::ArraySequence() : items(new DynamicArray<T>()) {}

template <typename T>
ArraySequence<T>::ArraySequence(int size) : items(new DynamicArray<T>(size)) {}

template <typename T>
ArraySequence<T>::ArraySequence(const LinkedList<T>& list) : items(new DynamicArray<T>()) {
    int count = list.get_size();
    items->resize(count);
    for (int i = 0; i < count; ++i) {
        items->set(i, list.get(i));
    }
}

template <typename T>
ArraySequence<T>::ArraySequence(T* data, int count)
    : items(new DynamicArray<T>(data, count)) {
}

template <typename T>
ArraySequence<T>::ArraySequence(const ArraySequence<T>& other): items(new DynamicArray<T>(*(other.items))) {
}

template <typename T>
int ArraySequence<T>::get_size() const {
    return items->get_size();
}

template <typename T>
ArraySequence<T>::~ArraySequence() {
    delete items;
}

template <typename T>
const T& ArraySequence<T>::get_first() const {
    if (this->get_size() == 0) {
        throw std::out_of_range("Index out of range");
    }
    return items->get(0);
}

template <typename T>
const T& ArraySequence<T>::get_last() const {
    int size = this->get_size();
    if (size == 0) {
        throw std::out_of_range("Index out of range");
    }
    return items->get(size - 1);
}

template <typename T>
Sequence<T>* ArraySequence<T>::append_internal(const T& item) {
    int old_size = this->get_size();
    items->resize(old_size + 1);
    items->set(old_size, item);
    return this;
}

template <typename T>
Sequence<T>* ArraySequence<T>::prepend_internal(const T& item) {
    int old_size = this->get_size();
    items->resize(old_size + 1);

    for (int i = old_size; i > 0; --i) {
        items->set(i, items->get(i - 1));
    }

    items->set(0, item);

    return this;
}

template <typename T>
Sequence<T>* ArraySequence<T>::insert_at_internal(const T& item, int index) {
    int current_size = this->get_size();
    if (index < 0 || index > current_size) {
        throw std::out_of_range("Index out of range;");
    }

    if (index == 0) {
        return this->prepend_internal(item);
    }

    if (index == current_size) {
        return this->append_internal(item);
    }

    items->resize(current_size + 1);
    for (int i = current_size; i > index; --i) {
        items->set(i, items->get(i - 1));
    }

    items->set(index, item);
    return this;
}

template <typename T>
Sequence<T>* ArraySequence<T>::remove_at_internal(int index) {
    if (index < 0 || index >= this->get_size()) {
        throw std::out_of_range("Index out of range;");
    }
    items->remove_at(index);
    return this;
}



template <typename T>
const T& ArraySequence<T>::get(int index) const {
    if (index < 0 || index >= this->get_size()) {
        throw std::out_of_range("Index out of range;");
    }

    return items->get(index);
}

template <typename T>
Sequence<T>* ArraySequence<T>::append(const T& item) {
    return this->instance()->append_internal(item);
}

template <typename T>
Sequence<T>* ArraySequence<T>::prepend(const T& item) {
    return this->instance()->prepend_internal(item);
}

template <typename T>
Sequence<T>* ArraySequence<T>::insert_at(const T& item, int index) {
    return this->instance()->insert_at_internal(item, index);
}

template <typename T>
Sequence<T>* ArraySequence<T>::remove_at(int index) {
    return this->instance()->remove_at_internal(index);
}
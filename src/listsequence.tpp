#pragma once

#include <stdexcept>

template <typename T>
class ListEnumerator : public IEnumerator<T> {
private:
    typename LinkedList<T>::Node* head;
    typename LinkedList<T>::Node* current;
    bool is_started;

public:
    explicit ListEnumerator(typename LinkedList<T>::Node* head_ptr)
        : head(head_ptr), current(nullptr), is_started(false) {
    }

    bool move_next() override {
        if (!is_started) {
            current = head;
            is_started = true;
        }
        else if (current != nullptr) {
            current = current->next;
        }
        return current != nullptr;
    }

    const T& get_current() const override {
        if (!current) throw std::out_of_range("Enumerator: out of bounds");
        return current->value;
    }

    void reset() override {
        current = nullptr;
        is_started = false;
    }
};

template <typename T>
IEnumerator<T>* ListSequence<T>::get_enumerator() const {
    return new ListEnumerator<T>(this->items->get_head());
}

template <typename T>
ListSequence<T>::ListSequence() : items(new LinkedList<T>()) {}

template <typename T>
ListSequence<T>::ListSequence(T* data, int count) : items(new LinkedList<T>(data, count)) {}

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
const T& ListSequence<T>::get(int index) const {
    if (index < 0 || index >= this->get_size()) {
        throw std::out_of_range("Index out of range");
    }
    IEnumerator<T>* en = this->get_enumerator();
    for (int i = 0; i <= index; ++i) {
        en->move_next();
    }
    const T& value = en->get_current();
    delete en;
    return value;
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


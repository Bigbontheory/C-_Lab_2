#pragma once 

#include "LinkedList.hpp"
#include <stdedxcept>

template<typename T>
typename LinkedList<T>::Node* LinkedList<T>::get_node(int index) const {
    Node* current;
    if (index < size / 2) {
        current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
    }
    else {
        current = tail;
        for (int i = size - 1; i > index; --i) {
            current = current->prev;
        }
    }
    return current;
}
    
template <typename T>
void LinkedList<T>::clear() {
    Node* current = head;
    while (current != nullptr) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
    tail = nullptr;
    size = 0;
}

template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), size(0) {}

template <typename T>
LinkedList<T>::LinkedList(const T* items, int count) : LinkedList() {
    if (count < 0) {
        throw std::invalid_argument("LinkedList: count cannot be negative");
    }
    if (items == nullptr && count > 0) {
        throw std::invalid_argument("LinkedList: source items pointer is nullptr");
    }
    try {
        for (int i = 0; i < count; ++i) {
            this->append(items[i]);
        }
    }
    catch (...) {
        this->clear();
        throw;
    }
}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& other) : LinkedList() {
    Node* current = other.head;
    try {
        while (current != nullptr) {
            this->append(current->value);
            current = current->next;
        }
    }
    catch (...) {
        this->clear();
        throw;
    }
}

template <typename T>
LinkedList<T>::LinkedList(LinkedList&& other) noexcept : head(other.head), tail(other.tail), size(other.size) {
    other.head = nullptr;
    other.tail = nullptr;
    other.size = 0;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>&& other) noexcept {
    if (this != &other) {
        clear();

        head = other.head;
        tail = other.tail;
        size = other.size;

        other.head = nullptr;
        other.tail = nullptr;
        other.size = 0;
    }
    return *this;
}


template <typename T>
LinkedList<T>::~LinkedList() {
    this->clear();
}

template <typename T>
void LinkedList<T>::append(const T& item) {
    Node* new_node = new Node(item);
    if (head == nullptr) {
        head = new_node;
        tail = head;
    }
    else {
        tail->next = new_node;
        new_node->prev = tail;
        tail = tail->next;
    }
    size++;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other) {
    if (this == &other) return *this;

    Node* new_head = nullptr;
    Node* new_tail = nullptr;
    Node* src = other.head;
    int new_size = 0;

    try {
        while (src != nullptr) {
            Node* node = new Node(src->value);
            if (!new_head) {
                new_head = new_tail = node;
            }
            else {
                node->prev = new_tail;
                new_tail->next = node;
                new_tail = node;
            }
            src = src->next;
            new_size++;
        }
    }
    catch (...) {
        while (new_head) {
            Node* temp = new_head;
            new_head = new_head->next;
            delete temp;
        }
        throw;
    }

    this->clear();

    head = new_head;
    tail = new_tail;
    size = new_size;

    return *this;
}

template <typename T>
void LinkedList<T>::prepend(const T& item) {
    Node* new_node = new Node(item);
    if (head == nullptr) {
        head = new_node;
        tail = head;
    }
    else {
        head->prev = new_node;
        new_node->next = head;
        head = head->prev;
    }
    size++;
}

template <typename T>
void LinkedList<T>::insert_at(const T& item, int index) {
    if (index > size || index < 0) {
        throw std::out_of_range("Index out of range;");
    }
    if (index == 0) {
        prepend(item);
        return;
    }
    if (index == size) {
        append(item);
        return;
    }
    Node* new_node = new Node(item);
    Node* current = get_node(index);

    new_node->next = current;
    new_node->prev = current->prev;
    current->prev->next = new_node;
    current->prev = new_node;
    size++;
}

template<typename T>
void LinkedList<T>::remove_at(int index) {
    Node* node_to_delete;
    if (index >= size || index < 0) {
        throw std::out_of_range("Invalid index");
    }
    if (index == 0) {
        node_to_delete = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        }
        else {
            tail = nullptr;
        }
    }
    else if (index == size - 1) {
        node_to_delete = tail;
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        }
        else {
            head = nullptr;
        }
    }
    else {
        node_to_delete = get_node(index);
        node_to_delete->prev->next = node_to_delete->next;
        node_to_delete->next->prev = node_to_delete->prev;
    }
    size--;
    delete node_to_delete;
}

template <typename T>
const T& LinkedList<T>::get(int index) const {
    if (index < 0 || index >= size) {
        throw std::out_of_range("LinkedList: Index out of range");
    }

    return get_node(index)->value;
}

template <typename T>
LinkedList<T>* LinkedList<T>::get_sublist(int startindex, int endindex) const {
    if (startindex < 0 || endindex > size || startindex > endindex) {
        throw std::out_of_range("Index out of range");
    }

    LinkedList<T>* sublist = new LinkedList<T>();
    Node* current = get_node(startindex);

    try {
        for (int i = startindex; i < endindex; ++i) {
            sublist->append(current->value);
            current = current->next;
        }
    }
    catch (...) {
        delete sublist;
        throw;
    }

    return sublist;
}

template <typename T>
LinkedList<T>* LinkedList<T>::concat(LinkedList<T>* list) const {
    LinkedList<T>* result = new LinkedList<T>(*this);

    if (list != nullptr) {
        Node* current = list->head;
        try {
            while (current != nullptr) {
                result->append(current->value);
                current = current->next;
            }
        }
        catch (...) {
            delete result;
            throw;
        }
    }

    return result;
}





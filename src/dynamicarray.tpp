#pragma once

#include "dynamicarray.hpp"
#include <stdexcept>

template <typename T>
DynamicArray<T>::DynamicArray() : data(nullptr), size(0), capacity(0) {}

template <typename T>
DynamicArray<T>::DynamicArray(int size) :data(nullptr), size(size), capacity(size) {
	if (size < 0) {
		throw std::invalid_argument("size cannot be negative");
	}
		if (size > 0) {
		this->data = new T[size]();
	}
}

template <typename T>
DynamicArray<T>::DynamicArray(const T* item, int count) : data(nullptr), size(count), capacity(count) {
	if (count < 0) throw std::invalid_argument("count < 0");
	if (count > 0) {
		if (item == nullptr) throw std::invalid_argument("item is nullptr");
		this->data = new T[this->capacity];
		for (int i = 0; i < this->size; ++i) {
			this->data[i] = item[i];
		}
	}
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& other)
	: data(nullptr), size(other.size), capacity(other.capacity) {

	if (this->capacity > 0) {
		this->data = new T[this->capacity];
		for (int i = 0; i < this->size; ++i) {
			this->data[i] = other.data[i];
		}
	} 
}

template <typename T>
DynamicArray<T>::DynamicArray(DynamicArray<T>&& other) noexcept
	: data(other.data), size(other.size), capacity(other.capacity) {

	other.data = nullptr;
	other.size = 0;
	other.capacity = 0;
}



template <typename T> 
DynamicArray<T>::~DynamicArray() {
	delete []data;
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& other) {
    if (this == &other) {
        return *this;
    }

    T* new_data = nullptr;

    try {
        if (other.capacity > 0 && other.data!=nullptr) {
            new_data = new T[other.capacity];
            for (int i = 0; i < other.size; ++i) {
                new_data[i] = other.data[i];
            }
        }
    } 
    catch (...) {
        delete[] new_data;
        throw;
    }

    delete[] this->data;

    this->data = new_data;
    this->size = other.size;
    this->capacity = other.capacity;

    return *this;
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(DynamicArray<T>&& other) noexcept {
	if (this != &other) {
		delete[] data;

		data = other.data;
		size = other.size;
		capacity = other.capacity;

		other.data = nullptr;
		other.size = 0;
		other.capacity = 0;
	}
	return *this;
}

template <typename T>
const T& DynamicArray<T>::get(int index) const {
	if (index >= size || index < 0) {
		throw std::out_of_range("Index out of range");
	}
	return data[index];
}	

template <typename T>
T& DynamicArray<T>::get(int index) {
    if (index >= size || index < 0) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template <typename T>
int DynamicArray<T>::get_size() const{
		return size;
}

template <typename T>
void DynamicArray<T>::remove_at(int index) {
	if (index >= size || index < 0) {
		throw std::out_of_range("Index out of range");
	}
	for (int i = index; i < size-1; ++i) {
		data[i] = data[i + 1];
	}
	size--;
}

template <typename T>
void DynamicArray<T>::set(int index, const T& value) {
	if (index >= size || index < 0) {
		throw std::out_of_range("Index out of range");
	}
	data[index] = value;
}

template <typename T>
void DynamicArray<T>::resize(int new_size) {
    if (new_size < 0) {
        throw std::invalid_argument("new_size cannot be negative");
    }

    if (new_size == 0) {
        delete[] data;
        data = nullptr;
        size = 0;
        capacity = 0;
        return;
    }
    if (new_size <= capacity) {
        if (new_size > size && data != nullptr) {
            for (int i = size; i < new_size; ++i) {
                data[i] = T();
            }
        }
        size = new_size;
        return;
    }
    int new_capacity = (capacity == 0) ? new_size : capacity * 2;
    if (new_size > new_capacity) {
        new_capacity = new_size;
    }

    T* new_data = new T[new_capacity]();

    try {
        if (data != nullptr) {
            for (int i = 0; i < size; ++i) {
                new_data[i] = data[i];
            }
        }
    }
    catch (...) {
        delete[] new_data;
        throw;
    }

    delete[] data;
    data = new_data;
    size = new_size;
    capacity = new_capacity;
}
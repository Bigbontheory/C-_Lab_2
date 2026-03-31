#pragma once

#include "DynamicArray.hpp"
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
DynamicArray<T>::DynamicArray(T* item, int count) : data(nullptr), size (count), capacity(count) {
	if (count < 0) {
		throw std::invalid_argument("count cannot be negative");
	}

	if (item == nullptr && size > 0) {
		throw std::invalid_argument("item cannot be nullptr");
	}
	
	if (this->capacity > 0)
		this->data = new T[this->capacity];
	for (int i = 0; i < this->size; ++i){
		this->data[i] = item[i];
	}
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& other) : data(nullptr),  size(other.size), capacity(other.capacity) {
	if (this->capacity > 0) {
		this->data = new T[this->capacity];
	}
	for (int i = 0; i < this->size; ++i) {
		this->data[i] = other.data[i];
	}
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

    T* newData = nullptr;

    try {
        if (other.capacity > 0) {
            newData = new T[other.capacity];
            for (int i = 0; i < other.size; ++i) {
                newData[i] = other.data[i];
            }
        }
    } 
    catch (...) {
        delete[] newData;
        throw;
    }

    delete[] this->data;

    this->data = newData;
    this->size = other.size;
    this->capacity = other.capacity;

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
			throw  std::invalid_argument("new_size cannot be negative");
		}
		if (new_size == 0) {
			delete[]data;
			data = nullptr;
			size = 0;
			capacity = 0;
			return;
		}
		if (new_size <= capacity) {
			if (new_size > size) {
				for (int i = size; i < new_size; ++i) {
					data[i] = T();
				}
			}
			size = new_size;
			return;
		}

		int new_capacity;
		if (new_size > capacity * 2) {
			new_capacity = new_size;
		}
		else {
			new_capacity = capacity * 2;
		}

		T* new_data = new T[new_capacity]();

			try {
				for (int i = 0; i < size; ++i) {
					new_data[i] = data[i];
				}
			}
		catch (...) {
			delete[]new_data;
			throw;
		}
		delete[]data;
		data = new_data;
		size = new_size;
		capacity = new_capacity;
	}

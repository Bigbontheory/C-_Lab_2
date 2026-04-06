#pragma once

template<class T> 
class DynamicArray {
public: 
	DynamicArray();
	explicit DynamicArray(int size);
	DynamicArray(T* items, int count);
	DynamicArray(const DynamicArray<T>& other); 
	~DynamicArray();

	DynamicArray<T>& operator=(const DynamicArray<T>& other);

	// getters
	const T& get(int index) const;
	int get_size() const;

	//operations
	void set (int index, const T& value);
	void resize(int new_size);
	void remove_at(int index)

private: 
	T* data;
	int size;
	int capacity;
};

#include "DynamicArray.tpp"
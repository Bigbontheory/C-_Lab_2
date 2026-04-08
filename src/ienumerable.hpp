#pragma once
#include "ienumerator.hpp"

template<typename T>
class IEnumerable {
public:
	virtual ~IEnumerable() = default;
	virtual IEnumerator<T>* get_enumerator() const = 0;
};
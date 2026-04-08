#pragma once


template<typename T>
class IEnumerator {
public:
	virtual bool move_next() = 0;
	virtual const T& get_current() const = 0;
	virtual void reset() = 0;
	
	virtual ~IEnumerator() = default;
};


#pragma once

template <class T>
class ICollection {
public:
    virtual ~ICollection() = default;

    virtual const T& get(int index) const = 0;
    virtual int get_size() const = 0;

    virtual ICollection<T>* clone() const = 0;
};
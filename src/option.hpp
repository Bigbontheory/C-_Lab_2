#pragma once

#include <stdexcept>

template <class T>
class Option {
public:
    Option() : has_value_(false) {}
    Option(const T& val) : value(val), has_value_(true) {}

    bool has_value() const {
        return has_value_;
    }

    bool is_none() const {
        return !has_value_;
    }
    
    const T& get_value() const {
        if (!has_value_) {
            throw std::runtime_error("get_value: Option has no value");
        }
        return value;
    }


private:
    T value;
    bool has_value_;
};
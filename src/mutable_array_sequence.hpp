#pragma once
#include "arraysequence.hpp"

template<typename T>
class MutableArraySequence : public ArraySequence<T>{
protected:
    ArraySequence<T>*instance() override {
        return this;
    }

public:

    MutableArraySequence() : ArraySequence<T>() {}
    MutableArraySequence(T* items, int count) : ArraySequence<T>(items, count) {}
    MutableArraySequence(const LinkedList<T>& list) : ArraySequence<T>(list) {}
    MutableArraySequence(const ArraySequence<T>& seq) : ArraySequence<T>(seq) {}

    virtual Sequence<T>*clone() const override {
        return new MutableArraySequence<T>(*this);
    }

    virtual ISequenceBuilder<T>* create_builder() const override {
        return new SequenceBuilder<T, MutableArraySequence<T>>();
    }
};
#pragma once
#include "arraysequence.hpp"

template <typename T>
class ImmutableArraySequence : public ArraySequence<T> {
protected:
    ArraySequence<T>* instance() override {
        return new ImmutableArraySequence<T>(*this);
    }

public:
    ImmutableArraySequence() : ArraySequence<T>() {}
    ImmutableArraySequence(T* items, int count) : ArraySequence<T>(items, count) {}
    ImmutableArraySequence(const LinkedList<T>& list) : ArraySequence<T>(list) {}
    ImmutableArraySequence(const ArraySequence<T>& seq) : ArraySequence<T>(seq) {}
    
    virtual Sequence<T>* clone() const override {
        return new ImmutableArraySequence<T>(*this);
    }

    virtual ISequenceBuilder<T>* create_builder() const override {
        return new SequenceBuilder<T, ImmutableArraySequence<T>>();
    }

    virtual ~ImmutableArraySequence() = default;
};

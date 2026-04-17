#pragma once
#include "listsequence.hpp"

template<typename T>
class ImmutableListSequence : public ListSequence<T> {
protected:
    ListSequence<T>* instance() override {
        return new ImmutableListSequence<T>(*this);
    }

public:
    ImmutableListSequence() : ListSequence<T>() {}
    ImmutableListSequence(T* items, int count) : ListSequence<T>(items, count) {}
    ImmutableListSequence(const LinkedList<T>& list) : ListSequence<T>(list) {}
    ImmutableListSequence(const ListSequence<T>& seq) : ListSequence<T>(seq) {}

    virtual Sequence<T>* clone() const override {
        return new ImmutableListSequence<T>(*this);
    }

    virtual ISequenceBuilder<T>* create_builder() const override {
        return new SequenceBuilder<T, ImmutableListSequence<T>>();
    }
};
#pragma once
#include "listsequence.hpp"

template<typename T>
class MutableListSequence : public ListSequence<T> {
protected:
    ListSequence<T>* instance() override {
        return this;
    }

public:
    MutableListSequence() : ListSequence<T>() {}
    MutableListSequence(T* items, int count) : ListSequence<T>(items, count) {}
    MutableListSequence(const LinkedList<T>& list) : ListSequence<T>(list) {}
    MutableListSequence(const ListSequence<T>& seq) : ListSequence<T>(seq) {}

    virtual Sequence<T>* clone() const override {
        return new MutableListSequence<T>(*this);
    }

    virtual ISequenceBuilder<T>* create_builder() const override {
        return new SequenceBuilder<T, MutableListSequence<T>>();
    }
};
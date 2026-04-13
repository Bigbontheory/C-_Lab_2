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

    class Builder : public ISequenceBuilder<T> {
    private:
        MutableArraySequence<T>* seq;

    public:
        Builder() {
            seq = new MutableArraySequence<T>();
        }

        virtual ISequenceBuilder<T>* append(const T& item) override {
            seq->append_internal(item);
            return this;
        }

        virtual Sequence<T>* build() override {
            Sequence<T>* res = seq;
            seq = nullptr;
            return res;
        }

        virtual ~Builder() {
            if (seq) {
                delete seq;
            }
        }

    };

    virtual ISequenceBuilder<T>* create_builder() const override {
        return new Builder();
    }
};
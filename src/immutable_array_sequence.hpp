#pragma once
#include "array_sequence.hpp"

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
   
    class Builder : public ISequenceBuilder<T> {
    private:
        ImmutableArraySequence<T>* seq;

    public:
        Builder() {
            seq = new ImmutableArraySequence<T>();
        }

        virtual ~Builder() {
            if (seq) {
                delete seq;
            }
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
    };

    virtual ISequenceBuilder<T>* create_builder() const override {
        return new Builder();
    }

    virtual ~ImmutableArraySequence() = default;
};

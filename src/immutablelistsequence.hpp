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

    class Builder : public ISequenceBuilder<T> {
    private:
        ImmutableListSequence<T>* seq;

    public:
        Builder() {
            seq = new ImmutableListSequence<T>();
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
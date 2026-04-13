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

    class Builder : public ISequenceBuilder<T> {
    private:
        MutableListSequence<T>* seq;

    public:
        Builder() {
            seq = new MutableListSequence<T>();
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
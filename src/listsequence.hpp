#include "sequence.hpp"
#include "linkedlist.hpp"
#include "ienumerator.hpp"

template <typename T>
class ListSequence : public Sequence<T> {
protected:
    LinkedList<T>* items;

    virtual ListSequence<T>* instance() = 0;

    Sequence<T>* append_internal(const T& item);
    Sequence<T>* prepend_internal(const T& item);
    Sequence<T>* insert_at_internal(const T& item, int index);

public:
    template <typename U, typename SeqType>
    friend class SequenceBuilder;

    ListSequence();
    ListSequence(T* data, int count);
    ListSequence(const LinkedList<T>& list);
    ListSequence(const ListSequence<T>& seq);
    virtual ~ListSequence();

    IEnumerator<T>* get_enumerator() const override;

    virtual const T& get(int index) const override;
    virtual int get_size() const override;
    virtual const T& get_first() const;
    virtual const T& get_last() const;

    virtual Sequence<T>* remove_at(int index) override;
    virtual Sequence<T>* append(const T& item) override;
    virtual Sequence<T>* prepend(const T& item) override;
    virtual Sequence<T>* insert_at(const T& item, int index) override;

    virtual const T& operator[](int index) const override;


#include "listsequence.tpp"

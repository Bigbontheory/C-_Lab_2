#pragma once

#include <stdexcept>
#include "ienumerable.hpp"
#include "icollection.hpp"
#include "sequencebuilder.hpp"
#include "option.hpp"


template<typename T>
class Sequence : public IEnumerable<T>, public ICollection<T> {
public: 
	virtual ~Sequence() {};
	
	virtual Sequence<T>* clone() const override = 0;

	virtual const T& get_first() const = 0;
	virtual const T& get_last() const = 0;
	const T& operator[](int index) const { return this->get(index); }

	virtual Option<T> try_get_first() const;
	virtual Option<T> try_get_last() const;
	virtual Option<T> try_get(int index) const;
	
	virtual Sequence<T>* get_subsequence(int start_index, int end_index) const;
	
	virtual Sequence<T>* append(const T& item) = 0;
	virtual Sequence<T>* prepend(const T& item) = 0;
	virtual Sequence<T>* insert_at(const T& item, int index) = 0;
	virtual Sequence<T>* remove_at(int index) = 0;
	
	virtual Sequence<T>* concat(const Sequence<T>* other) const;
	virtual Sequence<T>* map (T(*mapper)(const T& elem)) const;
	virtual Sequence<T>* where(bool (*predicate)(const T&)) const;
	virtual T reduce(T(*reducer)(const T&, const T&), const T& initial_value) const;
	
	virtual IEnumerator<T>* get_enumerator() const override = 0;
	
	virtual ISequenceBuilder<T>* create_builder() const = 0;
};

#include "sequence.tpp"

#pragma once
#include "isequencebuilder.hpp"

template <typename T, typename SeqType>
class SequenceBuilder : public ISequenceBuilder<T> {
private:
	SeqType* seq;
public:
	SequenceBuilder() : seq(new SeqType()) {}

	virtual ~SequenceBuilder() {
		if (seq) delete seq;
	}

	void append(const T& item) override {
		seq->append_internal(item);
	}

	Sequence<T>* build() override {
		Sequence<T>* res = seq;
		seq = nullptr;
		return res;
	}
};
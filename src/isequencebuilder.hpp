template<typename T>
class Sequence;

template <typename T>
class ISequenceBuilder {
public:
	virtual ~ISequenceBuilder() = default;
	virtual void append(const T & item) = 0;
	virtual Sequence<T>* build() = 0;
};


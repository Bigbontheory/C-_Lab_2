#pragma once

template <typename T> class ListEnumerator;

template <class T>
class LinkedList {

private:
	struct Node {
		T value;
		Node* next;
		Node* prev;

		explicit Node(const T& value) : value(value), next(nullptr), prev(nullptr) {}
	};
	Node* head;
	Node* tail;
	int size;
	
	Node* get_node(int index) const;

	friend class ListEnumerator<T>;

public:
	Node* get_head() const { return head; }
	LinkedList(const T* item, int count);
	LinkedList();
	LinkedList(const LinkedList<T>& list);
	~LinkedList();
	const T& get_first() const;
	const T& get_last() const;
	int get_size() const;

	LinkedList<T>* get_sublist(int start_index, int end_index) const;
	LinkedList<T>& operator=(const LinkedList<T>& other);

	void append(const T& item);
	void prepend(const T& item);
	void insert_at(const T& item, int index);
	void remove_at(int index);
	void clear();
	LinkedList<T>* concat(LinkedList<T>* list) const;
};

template <typename T>
class ListEnumerator : public IEnumerator<T> {
private:
	typename LinkedList<T>::Node* head;
	typename LinkedList<T>::Node* current;
	bool is_started;

public:
	explicit ListEnumerator(typename LinkedList<T>::Node* head_ptr)
		: head(head_ptr), current(nullptr), is_started(false) {
	}

	bool move_next() override {
		if (!is_started) {
			current = head;
			is_started = true;
		}
		else if (current != nullptr) {
			current = current->next;
		}
		return current != nullptr;
	}

	const T& get_current() const override {
		if (!current) throw std::out_of_range("Enumerator: out of bounds");
		return current->value;
	}

	void reset() override {
		current = nullptr;
		is_started = false;
	}
};

#include "linkedlist.tpp"
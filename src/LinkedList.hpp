	#pragma once
template <class T>
class LinkedList {

protected:
	Node* get_head() const { return head; }
public:
	LinkedList(const T* item, int count);
	LinkedList();
	LinkedList(const LinkedList& list);
	~LinkedList();

	const T& get_first() const;
	const T& get_last() const;
	int get_size() const;
	
	LinkedList<T>* get_sublist(int start_index, int end_index) const;

	void append(const T& item);
	void prepend(const T& item);
	void insert_at(const T& item, int index);
	void remove_at(int index);
	void clear();
	LinkedList<T>* concat(LinkedList<T>* list) const;

private:
	struct Node {
		friend class ListEnumerator<T>;
		T value;
		Node* next;
		Node* prev;

		explicit Node(const T& value) : value(value), next(nullptr), prev(nullptr) {}
	};
	Node* get_node(int index) const;
	Node* head;
	Node* tail;
	int size;

};

#include "linkedlist.tpp"
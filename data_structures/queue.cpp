#ifndef QUEUE_H
#define QUEUE_H

#include <cassert>
#include "singly-linked_list.h"

template <typename data_type>
class Queue {
	public:
		Queue();
		bool is_empty();
		int get_size();
		void enqueue(data_type data);
		data_type dequeue();
		data_type front();
		bool contains(data_type data);
		void clear();
	private:
		SinglyLinkedList<data_type> linked_list;
};

template <typename data_type>
Queue<data_type>::Queue() {
	linked_list = SinglyLinkedList<data_type>();
}

template <typename data_type>
bool Queue<data_type>::is_empty() {
	return linked_list.is_empty();	
}

template <typename data_type>
int Queue<data_type>::get_size() {
	return linked_list.get_size();
}

template <typename data_type>
bool Queue<data_type>::contains(data_type data) {
	return linked_list.contains(data);
}

template <typename data_type>
void Queue<data_type>::clear() {
	linked_list.clear();
}

template <typename data_type>
void Queue<data_type>::enqueue(data_type data) {
	linked_list.push_back(data);
}

template <typename data_type>
data_type Queue<data_type>::dequeue() {
	data_type data = linked_list[0];
	linked_list.pop_front();
	return data;
}

template <typename data_type>
data_type Queue<data_type>::front() {
	return linked_list[0];
}

#endif
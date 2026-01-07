#ifndef STACK_H
#define STACK_H

#include "singly-linked_list.h"

template <typename data_type>
class Stack {
	public:
		Stack();
		bool is_empty();
		int get_size();
		void push(data_type data);
		data_type pop();
		data_type peek();
		bool contains(data_type data);
		void clear();
	private:
		SinglyLinkedList<data_type> linked_list;
};

template <typename data_type>
Stack<data_type>::Stack() {
	linked_list = SinglyLinkedList<data_type>();
}

template <typename data_type>
bool Stack<data_type>::is_empty() {
	return linked_list.is_empty();	
}

template <typename data_type>
int Stack<data_type>::get_size() {
	return linked_list.get_size();
}

template <typename data_type>
void Stack<data_type>::push(data_type data) {
	linked_list.push_back(data);
}

template <typename data_type>
data_type Stack<data_type>::pop() {
	data_type data = linked_list[linked_list.get_size()-1];
	linked_list.pop_back();
	return data;
}

template <typename data_type>
data_type Stack<data_type>::peek() {
	return linked_list[linked_list.get_size()-1];
}

template <typename data_type>
bool Stack<data_type>::contains(data_type data) {
	return linked_list.contains(data);
}

template <typename data_type>
void Stack<data_type>::clear() {
	linked_list.clear();
}

#endif
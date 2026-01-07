#ifndef SINGLY_LIST_H
#define SINGLY_LIST_H

#include <stdexcept>

template <typename data_type>
class SinglyLinkedList {
	public:
		SinglyLinkedList();
		~SinglyLinkedList();

		int get_size();
		bool is_empty();
		void push_front(data_type data);
		void push_back(data_type data);
		void pop_front();
		void pop_back();
		void clear();
		void insert(data_type data, int index);
		void remove_at(int index);
		bool contains(data_type data);

		data_type& operator[](const int index);
	private:
		template <typename>
		class Node {
			public:
				data_type data;
				Node* next;
				Node(data_type data = data_type(), Node* next = nullptr)
				: data(data), next(next) {

				}
		};
		int size;
		Node<data_type> *head;
};

template <typename data_type>
SinglyLinkedList<data_type>::SinglyLinkedList() {
	size = 0;
	head = nullptr;
}
template <typename data_type>
SinglyLinkedList<data_type>::~SinglyLinkedList() {
	clear();
}

template <typename data_type>
int SinglyLinkedList<data_type>::get_size() {
	return size;
}

template <typename data_type>
bool SinglyLinkedList<data_type>::is_empty() {
	return size == 0;
}

template <typename data_type>
void SinglyLinkedList<data_type>::push_back(data_type data) {
	size++;
	if (head == nullptr) {
		head = new Node<data_type>(data);
		return;
	}
	Node<data_type> *current = this->head;
	while (current->next != nullptr) {
		current = current->next;
	}
	current->next = new Node<data_type>(data);
}

template <typename data_type>
void SinglyLinkedList<data_type>::pop_front() {
	if (is_empty()) return;
	Node<data_type> *prev_head = head;
	head = head->next;
	delete prev_head;
	size--;
}

template <typename data_type>
void SinglyLinkedList<data_type>::pop_back() {
	if (is_empty()) return;
	remove_at(size-1);
}

template <typename data_type>
void SinglyLinkedList<data_type>::clear() {
	while (size) {
		pop_front();
	}
}

template <typename data_type>
void SinglyLinkedList<data_type>::push_front(data_type data) {
	head = new Node<data_type>(data, head);
	size++;
}

template <typename data_type>
void SinglyLinkedList<data_type>::insert(data_type data, int index) {
	if (index == 0) {
		push_front(data);
		return;
	}
	Node<data_type> *current = this->head;
	for (int i = 0; i < index-1; i++) {
		current = current->next;
	}
	current->next = new Node<data_type>(data, current->next);
	size++;
}

template <typename data_type>
void SinglyLinkedList<data_type>::remove_at(int index) {
	if (index == 0) {
		pop_front();
		return;
	}
	if (is_empty()) return;
	Node<data_type> *current = this->head;
	for (int i = 0; i < index-1; i++) {
		current = current->next;
	};
	Node<data_type> *prev = current->next;
	current->next = prev->next;
	delete prev;
	size--;
}

template <typename data_type>
bool SinglyLinkedList<data_type>::contains(data_type data) {
	if (is_empty()) return false;
	Node<data_type> *current = this->head;
	while (current != nullptr) {
		if (current->data == data) {
			return true;
		}
		current = current->next;
	}
	return false;
}

template <typename data_type>
data_type &SinglyLinkedList<data_type>::operator[](const int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }

	Node<data_type>* current = head;
	for (int i = 0; i < index; i++) {
		current = current->next;
	}
	return current->data;
}

#endif
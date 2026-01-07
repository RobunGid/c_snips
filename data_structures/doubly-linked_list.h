#ifndef DOUBLY_LIST_H
#define DOUBLY_LIST_H

#include <stdexcept>

template <typename data_type>
class DoublyLinkedList {
	public:
		DoublyLinkedList();
		~DoublyLinkedList();

		int get_size();
		void push_front(data_type data);
		void push_back(data_type data);
		void pop_front();
		void pop_back();
		void clear();
		void insert(data_type value, int index);
		void remove_at(int index);
		bool contains(data_type data);
		bool is_empty();

		data_type& operator[](const int index);
	private:
		template <typename>
		class Node {
			public:
				data_type data;
				Node* next;
				Node* prev;
				Node(data_type data = data_type(), Node* next = nullptr, Node* prev = nullptr)
				: data(data), next(next), prev(prev) {

				}
		};
		int size;
		Node<data_type> *head;
		Node<data_type> *tail;
};

template <typename data_type>
DoublyLinkedList<data_type>::DoublyLinkedList() {
	size = 0;
	head = nullptr;
	tail = nullptr;
}
template <typename data_type>
DoublyLinkedList<data_type>::~DoublyLinkedList() {
	clear();
}

template <typename data_type>
int DoublyLinkedList<data_type>::get_size() {
	return size;
}

template <typename data_type>
void DoublyLinkedList<data_type>::push_back(data_type data) {
	if (tail) {
		Node<data_type> *newNode = new Node<data_type>(data, nullptr, tail);
		tail->next = newNode;
		tail = newNode;
		size++;
	} else {
		Node<data_type> *newNode = new Node<data_type>(data, nullptr, nullptr);
		tail = newNode;
		head = newNode;
		size++;
	}

}

template <typename data_type>
void DoublyLinkedList<data_type>::push_front(data_type data) {
	if (head) {
		Node<data_type> *newNode = new Node<data_type>(data, head, nullptr);
		head->prev = newNode;
		head = newNode;
		size++;
	} else {
		Node<data_type> *newNode = new Node<data_type>(data, nullptr, nullptr);
		tail = newNode;
		head = newNode;
		size++;
	}
}

template <typename data_type>
void DoublyLinkedList<data_type>::pop_back() {
	if (size == 0) {
		return;
	}
	Node<data_type> *prev_tail = tail;
	if (size > 1) {
		tail = tail->prev;
		tail->next = nullptr;
	} else {
		tail = nullptr;
		head = nullptr;
	}
	delete prev_tail;
	size--;

}

template <typename data_type>
void DoublyLinkedList<data_type>::clear() {
	while (size) {
		pop_front();
	}
}

template <typename data_type>
void DoublyLinkedList<data_type>::insert(data_type data, int index) {
	if (index < 0 || index > size) return;
	if (index == 0) {
		push_front(data);
		return;
	}
	if (index == size) {
		push_back(data);
		return;
	}

	if (index < size / 2) {
		Node<data_type>* current = head;
		for (int i = 0; i < index - 1; i++) {
			current = current->next;
		}
		Node<data_type>* nextNode = current->next;
		Node<data_type>* newNode = new Node<data_type>(data, nextNode, current);
		current->next = newNode;
		nextNode->prev = newNode;
	} else {
		Node<data_type>* current = tail;
		for (int i = size - 1; i > index; i--) {
			current = current->prev;
		}
		Node<data_type>* prevNode = current->prev;
		Node<data_type>* newNode = new Node<data_type>(data, current, prevNode);
		prevNode->next = newNode;
		current->prev = newNode;
	}

	size++;
}

template <typename data_type>
void DoublyLinkedList<data_type>::pop_front() {
	if (size == 0) {
		return;
	}
	Node<data_type> *prev_head = head;
	head = head->next;
	if (head) {
		head->prev = nullptr;
	}
	delete prev_head;
	size--;
	if (size == 1) {
		tail = head;
	}
	if (tail && size == 0) {
		tail = nullptr;
		delete tail;
	}
}

template <typename data_type>
void DoublyLinkedList<data_type>::remove_at(int index) {
	if (index == 0) {
		pop_front();
		return;
	}
	if (index+1 == size) {
		pop_back();
		return;
	}
	if (index < size/2) {
		Node<data_type> *current = head;
		for (int i = 0; i < index-1; i++) {
			current = current->next;
		};
		Node<data_type> *prev = current->next;
		current->next = prev->next;
		prev->next->prev = current;
		delete prev;
		size--;
	} else {
		Node<data_type> *current = tail;
		for (int i = size-1; i > index+1; i--) {
			current = current->prev;
		}
		Node<data_type> *prev = current->prev;
		current->prev = prev->prev;
		prev->prev->next = current;
		delete prev;
		size--;
	}

}

template <typename data_type>
data_type &DoublyLinkedList<data_type>::operator[](const int index) {
	if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }

	if (index < size / 2) {
		Node<data_type>* current = head;
		for (int i = 0; i < index; i++) {
			current = current->next;
		}
		return current->data;
	} else {
		Node<data_type>* current = tail;
		for (int i = 0; i < (size-index-1); i++) {
			current = current->prev;
		}
		return current->data;
	}
}

template <typename data_type>
bool DoublyLinkedList<data_type>::contains(data_type data) {
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
bool DoublyLinkedList<data_type>::is_empty() {
	return size == 0;
}

#endif
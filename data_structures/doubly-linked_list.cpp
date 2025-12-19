#include <iostream>
#include <vector>
#include <cassert>

template <typename data_type>
class DoublyLinkedList {
	public:
		DoublyLinkedList();
		~DoublyLinkedList();

		int getSize();
		void push_front(data_type data);
		void push_back(data_type data);
		void pop_front();
		void pop_back();
		void clear();
		void insert(data_type value, int index);
		void removeAt(int index);

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
int DoublyLinkedList<data_type>::getSize() {
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
	tail = tail->prev;
	tail->next = nullptr;
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
void DoublyLinkedList<data_type>::insert(data_type value, int index) {
	if (index == 0) {
		push_front(value);
		return;
	}
	if (index < size / 2) {
		Node<data_type> *current = head;
		for (int i = 0; i < index-1; i++) {
			current = current->next;
		}
		current->next = new Node<data_type>(value, current->next);
		size++;
	} else {
		Node<data_type> *current = tail;
		for (int i = size-1; i > index-1; i--) {
			current = current->prev;
		}
		current->next = new Node<data_type>(value, current->next);
		current->next->prev = current;
		size++;
	}

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
}

template <typename data_type>
void DoublyLinkedList<data_type>::removeAt(int index) {
	if (index == 0) {
		pop_front();
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
	int counter;
	counter = 0;
	Node<data_type> *current;
	current = head;
	while (current != nullptr) {
		if (counter == index) {
			return current->data;
		}
		current = current->next;
		counter++;
	}
}

int main() {
    DoublyLinkedList<int> list;

    assert(list.getSize() == 0);

    list.pop_front();
    list.pop_back();
    assert(list.getSize() == 0);

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    assert(list.getSize() == 3);
    assert(list[0] == 1);
    assert(list[1] == 2);
    assert(list[2] == 3);

    list.push_front(10);
    assert(list[0] == 10);
    assert(list.getSize() == 4);

    list.insert(99, 2);
    assert(list[2] == 99);
    assert(list.getSize() == 5);

    list.removeAt(2);
    assert(list[2] == 2);
    assert(list.getSize() == 4);

    list.insert(555, 4);
    assert(list[4] == 555);
    assert(list.getSize() == 5);

    list.pop_back();
    assert(list.getSize() == 4);
    assert(list[3] == 3);

    list.pop_front();
    assert(list.getSize() == 3);
    assert(list[0] == 1);

    list.clear();
    assert(list.getSize() == 0);

    for (int i = 0; i < 10; i++) list.push_back(i);
    assert(list.getSize() == 10);
    for (int i = 0; i < 10; i++) assert(list[i] == i);

    list.removeAt(0);
    assert(list[0] == 1);

    list.removeAt(list.getSize() - 1);
    assert(list.getSize() == 8);
    assert(list[7] == 8);

    list.insert(123, 5);
    assert(list[5] == 123);
}

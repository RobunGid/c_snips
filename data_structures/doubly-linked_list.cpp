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
void DoublyLinkedList<data_type>::removeAt(int index) {
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


void test_constructor() {
	DoublyLinkedList<int> list;
	assert(list.getSize() == 0);
}

void test_push_back() {
	DoublyLinkedList<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	assert(list.getSize() == 3);
	assert(list[0] == 1);
	assert(list[1] == 2);
	assert(list[2] == 3);
}

void test_push_front() {
	DoublyLinkedList<int> list;
	list.push_front(1);
	list.push_front(2);
	list.push_front(3);
	assert(list.getSize() == 3);
	assert(list[0] == 3);
	assert(list[1] == 2);
	assert(list[2] == 1);
}

void test_pop_back() {
	DoublyLinkedList<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.pop_back();
	assert(list.getSize() == 2);
	assert(list[0] == 1);
	assert(list[1] == 2);
}

void test_pop_front() {
	DoublyLinkedList<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.pop_front();
	assert(list.getSize() == 2);
	assert(list[0] == 2);
	assert(list[1] == 3);
}

void test_insert_middle() {
	DoublyLinkedList<int> list;
	list.push_back(1);
	list.push_back(3);
	list.insert(2, 1);
	assert(list.getSize() == 3);
	assert(list[0] == 1);
	assert(list[1] == 2);
	assert(list[2] == 3);
}

void test_insert_begin() {
	DoublyLinkedList<int> list;
	list.push_back(2);
	list.push_back(3);
	list.insert(1, 0);
	assert(list.getSize() == 3);
	assert(list[0] == 1);
}

void test_insert_end() {
	DoublyLinkedList<int> list;
	list.push_back(1);
	list.push_back(2);
	list.insert(3, 2);
	assert(list.getSize() == 3);
	assert(list[2] == 3);
}

void test_remove_middle() {
	DoublyLinkedList<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.removeAt(1);
	assert(list.getSize() == 2);
	assert(list[0] == 1);
	assert(list[1] == 3);
}

void test_remove_begin() {
	DoublyLinkedList<int> list;
	list.push_back(1);
	list.push_back(2);
	list.removeAt(0);
	assert(list.getSize() == 1);
	assert(list[0] == 2);
}

void test_remove_end() {
	DoublyLinkedList<int> list;
	list.push_back(1);
	list.push_back(2);
	list.removeAt(1);
	assert(list.getSize() == 1);
	assert(list[0] == 1);
}

void test_clear() {
	DoublyLinkedList<int> list;
	list.push_back(1);
	list.push_back(2);
	list.push_back(3);
	list.clear();
	assert(list.getSize() == 0);
}

void test_operator_modify() {
	DoublyLinkedList<int> list;
	list.push_back(1);
	list.push_back(2);
	list[1] = 42;
	assert(list[1] == 42);
}

void test_many_operations() {
	DoublyLinkedList<int> list;
	for (int i = 0; i < 1000; i++)
		list.push_back(i);
	assert(list.getSize() == 1000);
	for (int i = 0; i < 500; i++)
		list.pop_front();
	assert(list.getSize() == 500);
	for (int i = 0; i < 500; i++)
		assert(list[i] == i + 500);
}

void test_string_type() {
	DoublyLinkedList<std::string> list;
	list.push_back("a");
	list.push_back("b");
	list.push_front("c");
	assert(list.getSize() == 3);
	assert(list[0] == "c");
	assert(list[1] == "a");
	assert(list[2] == "b");
}

void test_single_element_pop() {
	DoublyLinkedList<int> list;
	list.push_back(1);
	list.pop_back();
	assert(list.getSize() == 0);
	list.push_back(2);
	list.pop_front();
	assert(list.getSize() == 0);
}

int main() {
DoublyLinkedList<int> list;
	test_constructor();
	test_push_back();
	test_push_front();
	test_pop_back();
	test_pop_front();
	test_insert_middle();
	test_insert_begin();
	test_insert_end();
	test_remove_middle();
	test_remove_begin();
	test_remove_end();
	test_clear();
	test_operator_modify();
	test_many_operations();
	test_string_type();
	test_single_element_pop();

	return 0;
}

#include <iostream>
#include <vector>

template <typename data_type>
class SinglyLinkedList {
	public:
		SinglyLinkedList();
		~SinglyLinkedList();

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
int SinglyLinkedList<data_type>::getSize() {
	return size;
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
	Node<data_type> *prev_head = head;
	head = head->next;
	delete prev_head;
	size--;
}

template <typename data_type>
void SinglyLinkedList<data_type>::pop_back() {
	removeAt(size-1);
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
void SinglyLinkedList<data_type>::insert(data_type value, int index) {
	if (index == 0) {
		push_front(value);
		return;
	}
	Node<data_type> *current = this->head;
	for (int i = 0; i < index-1; i++) {
		current = current->next;
	}
	current->next = new Node<data_type>(value, current->next);
	size++;
}

template <typename data_type>
void SinglyLinkedList<data_type>::removeAt(int index) {
	if (index == 0) {
		pop_front();
		return;
	}
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
data_type &SinglyLinkedList<data_type>::operator[](const int index) {
	int counter = 0;
	Node<data_type> *current = this->head;
	while (current != nullptr) {
		if (counter == index) {
			return current->data;
		}
		current = current->next;
		counter++;
	}
}

int main() {
 	SinglyLinkedList<int> lst;
	lst.push_back(1111);
	lst.push_back(2222);
	lst.push_back(3333);
	std::cout << lst.getSize() << std::endl;
	for (int i = 0; i < lst.getSize(); i++) {
		std::cout << i << " = " << lst[i] << std::endl;
	}
	std::cout << std::endl;
	lst.removeAt(1);
	for (int i = 0; i < lst.getSize(); i++) {
		std::cout << i << " = " << lst[i] << std::endl;
	}
	return 0;
}

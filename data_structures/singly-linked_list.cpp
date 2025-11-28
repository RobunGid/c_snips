#include <iostream>
#include <vector>

template <typename data_type>
class SinglyLinkedList {
	public:
		SinglyLinkedList();
		~SinglyLinkedList();

		int getSize();
		void push_back(data_type data);
		void pop_front();
		void clear();

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
void SinglyLinkedList<data_type>::clear() {
	while (size) {
		pop_front();
	}
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
	lst.push_back(34);
	lst.push_back(45);
	lst.push_back(56);
	std::cout << lst.getSize() << std::endl;
	for (int i = 0; i < lst.getSize(); i++) {
		std::cout << i << " = " << lst[i] << std::endl;
	}
	lst.pop_front();
	for (int i = 0; i < lst.getSize(); i++) {
		std::cout << i << " = " << lst[i] << std::endl;
	}
	lst.clear();
	std::cout << lst.getSize() << std::endl;
	return 0;
}

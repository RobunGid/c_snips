#include <iostream>
#include <vector>
#include <cassert>
#include <type_traits>

template <typename data_type>
class BTree {
	static_assert(std::is_same_v<data_type, int> || std::is_same_v<data_type, float>,
				"BTree can only be instantiated with int or float");
	public:
		BTree();
		void insert(data_type data);
		bool is_empty(void);
		bool contains(data_type data);
		data_type min(void);
		data_type max(void);
		int get_node_count(void);
		int get_height(void);
		data_type* traverse_in_order(void);
	private:
		int node_count;
		int height;
		template <typename>
		class Node {
			public:
				data_type data;
				Node* left;
				Node* right;
				int count;
				Node(data_type data = data_type(), Node* left = nullptr, Node* right = nullptr, int count = 1)
				: data(data), left(left), right(right), count(count) {

				}
		};
		Node<data_type> *root;
};

template <typename data_type>
BTree<data_type>::BTree() {
	root = nullptr;
	node_count = 0;
	height = 0;
}

template <typename data_type>
void BTree<data_type>::insert(data_type data) {
	if (is_empty()) {
		root = new Node<data_type>(data, nullptr, nullptr);
		node_count = 1;
		height = 1;
		return;
	}
	Node<data_type> *current_node = root;
	int current_height = 1;
	while ((current_node->data != data) || 
	(current_node->data > data && current_node->left == nullptr) || 
	(current_node->data < data && current_node->right == nullptr)) {
		if (current_node->data < data && current_node->right == nullptr) {
			current_node->right = new Node<data_type>(data, nullptr, nullptr);
			node_count++;
		} else if (current_node->data > data && current_node->left == nullptr) {
			current_node->left = new Node<data_type>(data, nullptr, nullptr);
			node_count++;
		} else if (current_node->data == data) {
			current_node->count++;
		} else {
			current_node = current_node->data < data ? current_node->right : current_node->left; 
			current_height++;
		}
	}
	height = current_height;
}

template <typename data_type>
bool BTree<data_type>::is_empty(void) {
	return root == nullptr;
}

template <typename data_type>
bool BTree<data_type>::contains(data_type data) {
	if (is_empty()) return false;

	Node<data_type> *current_node = root;
	while (current_node != nullptr) {
		if (current_node->data == data) {
			return true;
		}
		if (current_node->data < data) {
			current_node = current_node->right;
		} else {
			current_node = current_node->left;
		}
	}
	return false;
}

template <typename data_type>
data_type BTree<data_type>::min(void) {
	if (is_empty()) throw std::runtime_error("Tree is empty");
	Node<data_type> *current_node = root;
	while (current_node->left) {
		current_node = current_node->left;
	}
	return current_node->data;
}

template <typename data_type>
data_type BTree<data_type>::max(void) {
	if (is_empty()) throw std::runtime_error("Tree is empty");
	Node<data_type> *current_node = root;
	while (current_node->right) {
		current_node = current_node->right;
	}
	return current_node->data;
}

template <typename data_type>
int BTree<data_type>::get_node_count(void) {
	return node_count;
}

template <typename data_type>
int BTree<data_type>::get_height(void) {
	return height;
}

template <typename data_type>
data_type* BTree<data_type>::traverse_in_order(void) {
	if (is_empty()) return nullptr;
	data_type* array = new data_type[node_count];
}

int main() {
 	BTree<int> tree;

	tree.insert(1);
	tree.insert(5);
	tree.insert(10);
	tree.insert(7);

    return 0;
}

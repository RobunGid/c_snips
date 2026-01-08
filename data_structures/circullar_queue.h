#ifndef CIRCULLAR_QUEUE_H
#define CIRCULLAR_QUEUE_H

#include <stdexcept>

template <typename data_type>
class CircullarQueue {
	public:
		CircullarQueue(int elements_count);
		bool is_empty();
		bool is_full();
		int get_size();
		void enqueue(data_type data);
		data_type dequeue();
		bool contains(data_type data);
		void clear();
	private:
		data_type* array;
		int elements_count;
		int front;
		int rear;
};

template <typename data_type>
CircullarQueue<data_type>::CircullarQueue(int count) {
	array = new data_type[count+1];
	elements_count = count+1;
	front = 0;
	rear = 0;
}

template <typename data_type>
bool CircullarQueue<data_type>::is_empty() {
	return front == rear;	
}

template <typename data_type>
bool CircullarQueue<data_type>::is_full() {
	return ((rear+1) % elements_count == front);
}

template <typename data_type>
int CircullarQueue<data_type>::get_size() {
	return (rear - front);
}

template <typename data_type>
bool CircullarQueue<data_type>::contains(data_type data) {
	for (int i = front; i < rear; i++) {
		if (array[i] == data) {
			return true;
		}
	}
	return false;
}

template <typename data_type>
void CircullarQueue<data_type>::clear() {
	rear = 0;
	front = 0;
}

template <typename data_type>
void CircullarQueue<data_type>::enqueue(data_type data) {
	if (is_full()) throw std::overflow_error("Queue is filled");
	array[rear] = data;
	if (rear == 0) {
		rear = 1;
	} else {
		rear = ((rear+1) % elements_count);
	}
}

template <typename data_type>
data_type CircullarQueue<data_type>::dequeue() {
	if (is_empty()) throw std::overflow_error("Queue is empty");
	data_type data = array[front];
	front = (front+1) % elements_count;
	return data;
}
#endif
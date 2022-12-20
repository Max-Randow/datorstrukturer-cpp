// This is the second .h file you will edit
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header

#ifndef MY_PRIORITY_QUEUE_H
#define MY_PRIORITY_QUEUE_H

#include "MyException.h"
#include "MyVector.h"


template<typename T, typename C>
class MyPriorityQueue {
	MyVector<T> vector_array;
	C strictly_larger_operator;

public:
	MyPriorityQueue();

	~MyPriorityQueue();

	void push(const T& t);

	T top() const;

	void pop();

	bool empty() const;

	unsigned size() const;

private:
	// Other private members?
	MyVector<T> heap;
	void shiftUp(int index);
	void shiftDown(int index);
	void swap(int i, int j);
	
};	

template<typename T, typename C>
MyPriorityQueue<T, C>::MyPriorityQueue() {
	
}

template<typename T, typename C>
MyPriorityQueue<T, C>::~MyPriorityQueue() {

}

template<typename T, typename C>
void MyPriorityQueue<T, C>::shiftDown(int index){
	if(index < 0){
		return;
	}

	int leftChild = 2*index +1;
	int rightChild = 2*index +2;

	if(!(leftChild > heap.size()) || !(rightChild > heap.size())){
		if(strictly_larger_operator(heap[rightChild], heap[leftChild])){
			swap(leftChild,index);
			shiftDown(leftChild);
		}
		else if(strictly_larger_operator(heap[leftChild], heap[rightChild])){
			swap(rightChild,index);
			shiftDown(rightChild);
		}

	}
	return;
}
template<typename T, typename C>
void MyPriorityQueue<T, C>::swap(int i, int j){
		T temp = heap[i];
		heap[i] = heap[j];
		heap[j] = temp;
}

template<typename T, typename C>
void MyPriorityQueue<T, C>::shiftUp(int index){
	if(index < 0){
		return;
	}
	//Grab parent position in heap
	int parentPos = (index-1)/2;

	//Look at parent priority
	if(strictly_larger_operator(heap[parentPos], heap[index])){
		//Parent is lower priority than index, swap and 
		swap(parentPos, index);
		shiftUp(parentPos);
	}

}

template<typename T, typename C>
void MyPriorityQueue<T, C>::push(const T& t) {
	heap.push_back(t);
	shiftUp(size() - 1);


}

template<typename T, typename C>
T MyPriorityQueue<T, C>::top() const {
	return heap[0];
}

template<typename T, typename C>
void MyPriorityQueue<T, C>::pop() {
	heap[0] = heap[heap.numberOfElements - 1];
	heap.pop_back();

}

template<typename T, typename C>
bool MyPriorityQueue<T, C>::empty() const {
	return heap.empty();
}

template<typename T, typename C>
unsigned MyPriorityQueue<T, C>::size() const {
	return heap.size();
}

#endif	// MY_PRIORITY_QUEUE_H

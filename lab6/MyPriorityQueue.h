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
public:
    MyPriorityQueue() {};

    ~MyPriorityQueue() {};

    void push(const T& t);

    T top() const;

    void pop();

    bool empty() const;

    unsigned size() const;

private:
    C strictly_larger_operator;
    MyVector<T> heap;
    void shiftUp(int index);
    void shiftDown(int index);
    void swap(int i, int j);
    bool isLeaf(unsigned index) const;

};

template<typename T, typename C>
bool MyPriorityQueue<T, C>::isLeaf(unsigned const index) const {
    unsigned const heapSize = size();
    return (index >= heapSize/2) && (index < heapSize);
}

template<typename T, typename C>
void MyPriorityQueue<T, C>::shiftDown(int index){
    if(isLeaf(index) || index < 0){
        return;
    }

    int const leftChild = 2*index +1;
    int const rightChild = 2*index +2;
    int swapIndex = leftChild;

    // pick swapIndex to be the smallest of left and rightchild
    if(strictly_larger_operator(heap[swapIndex], heap[rightChild])) {
        swapIndex = rightChild;
    }

    if(strictly_larger_operator(heap[index], heap[swapIndex])){
        swap(index,swapIndex);
        shiftDown(swapIndex);
    }
    return;
}
template<typename T, typename C>
void MyPriorityQueue<T, C>::swap(int const i, int const j){
    T const temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
}

template<typename T, typename C>
void MyPriorityQueue<T, C>::shiftUp(int const index){
    if(index < 0){
        return;
    }
    //Grab parent position in heap.
    int const parentPos = (index-1)/2;

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
    heap[0] = heap[heap.size() - 1];
    heap.pop_back();
    shiftDown(0);
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

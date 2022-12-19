// This is the first .h file you will edit
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header

#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include "MyException.h"
#include <algorithm>
#include <cmath>

using namespace std;

template<typename T>
class MyVector {
public:
	MyVector();

	~MyVector();

	MyVector(const MyVector& other);

	MyVector& operator=(const MyVector& other);


	void push_back(const T&);

	void pop_back();

	T& operator[](unsigned i);

	const T& operator[](unsigned i) const;

	bool empty() const;

	T* begin();

	T* end();

	void clear();

	unsigned size() const;

private:
	// private members?
	unsigned capacity;
	unsigned numberOfElements;
	T* storage;
	void reserve(unsigned size);

};


/*
* Constructor for MyVector
*/
template<typename T>
MyVector<T>::MyVector() {
	storage = new T[1];
	numberOfElements = 0;
	capacity = 1;

}
/*
* increases capacity to next multiple of 2
*/
template<typename T>
void MyVector<T>::reserve(unsigned size){
	if (size < capacity){
		return;

	}

	unsigned nextPow2 = pow(2, ceil(log(size)/log(2)));
	T* temp = new T[nextPow2];
	copy(begin(), end(), temp);
	delete [] storage;
	storage = temp;
	capacity = nextPow2;
}
/*
* Deconstructor for MyVector
*/
template<typename T>
MyVector<T>::~MyVector() {
	delete[] storage;
	storage = nullptr;
	
}

/*
* Copy constuctor for MyVector. Puts a copy in other. May reserve new capacity
*/
template<typename T>
MyVector<T>::MyVector(const MyVector& other) {
	reserve(other.numberOfElements);

	copy(other.begin(), other.end(), begin());
	numberOfElements = other.numberOfElements;
}
/*
* Copy assignment for MyVector. Reserves new capacity
*/
template<typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector& other) {
	if(this == other){
		return *this;
	}

	reserve(other.numberOfElements);
	copy(other.begin(), other.end(), begin());
	numberOfElements = other.numberOfElements;

	return *this;
}

/*
* Adds new element to the back of storage, reserves new capacity
*/
template<typename T>
void MyVector<T>::push_back(const T& e) {
	if(numberOfElements == capacity){
		reserve(numberOfElements +1);
	}
	storage[numberOfElements] = e;
	numberOfElements++;
}
/*
* Removes element from storage by decreasing the numberOfElements
*/
template<typename T>
void MyVector<T>::pop_back() {
	if(numberOfElements > 0){
		numberOfElements--;
	}

}
/*
* Returns i:th element of storage
*/
template<typename T>
T& MyVector<T>::operator[](unsigned i) {
	return storage[i];
}

/*
* Returns i:th element of storage
*/
template<typename T>
const T& MyVector<T>::operator[](unsigned i) const {
	return storage[i];
}
/*
* returns true if numberOfElements is zero. Storage is empty
*/
template<typename T>
bool MyVector<T>::empty() const {
	return numberOfElements == 0;
}
/*
* Clears storage of all elements and resets capacity to 1
*/
template<typename T>
void MyVector<T>::clear() {	
	delete[] storage;
	storage = new T[1];
	capacity = 1;
	numberOfElements = 0;

}
/*
* Returns size of storage
*/
template<typename T>
unsigned MyVector<T>::size() const {
	return numberOfElements;
}
/*
* Returns a pointer of first element in storage
*/
template<typename T>
T* MyVector<T>::begin() {
	return storage;
}
/*
* Returns a pointer of the element after the last in storage
*/
template<typename T>
T* MyVector<T>::end() {
	return storage + numberOfElements;
}

#endif	// MY_VECTOR_H

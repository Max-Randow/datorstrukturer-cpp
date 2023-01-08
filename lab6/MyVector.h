/*
 * Authors: wilmi895 maxra518
 * Usage:
 * Implements a dynamic array, vector with templated element type.
 */

#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include "MyException.h"
#include <algorithm>
#include <cmath>
#include <iostream>

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

    T* begin() const;

    T* end() const;

    void clear();

    unsigned size() const;

private:
    unsigned capacity;
    unsigned numberOfElements;
    T* storage = nullptr;
    void reserve(unsigned size);
    void copyVector(MyVector const& other);
};

/*
 * Constructor for MyVector
 */
template<typename T>
MyVector<T>::MyVector() {
    storage = new T[1];
    capacity = 1;
    numberOfElements = 0;
}

/*
 * Copies another vector to this object.
 */
template<typename T>
void MyVector<T>::copyVector(MyVector const& other) {
    capacity = other.capacity;
    numberOfElements = other.numberOfElements;
    delete [] storage;
    storage = new T[capacity];

    copy(other.begin(), other.end(), begin());
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
    copyVector(other);
}

/*
 * Copy assignment for MyVector. Reserves new capacity
 */
template<typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector& other) {
    if(this == &other){
        return *this;
    }
    copyVector(other);

    return *this;
}

/*
 * Adds new element to the back of storage, reserves new capacity
 */
template<typename T>
void MyVector<T>::push_back(const T& e) {
    if(numberOfElements >= capacity) {
        capacity *= 2;
        T* temp = new T[capacity];
        copy(begin(), end(), temp);
        delete [] storage;
        storage = temp;
    }
    storage[numberOfElements] = e;
    numberOfElements++;
}

/*
 * Removes last element from vector.
 */
template<typename T>
void MyVector<T>::pop_back() {
    if(numberOfElements > 0) {
        numberOfElements--;
    }
}

/*
 * Returns i:th element in vector.
 */
template<typename T>
T& MyVector<T>::operator[](unsigned i) {
    return storage[i];
}

/*
 * Returns i:th element in vector.
 */
template<typename T>
const T& MyVector<T>::operator[](unsigned i) const {
    return storage[i];
}

/*
 * Checks if vector is empty.
 */
template<typename T>
bool MyVector<T>::empty() const {
    return numberOfElements == 0;
}

/*
 * Clears vector of all elements and resets capacity to 1
 */
template<typename T>
void MyVector<T>::clear() {
    delete[] storage;
    storage = new T[1];
    capacity = 1;
    numberOfElements = 0;
}

/*
 * Returns size of vector.
 */
template<typename T>
unsigned MyVector<T>::size() const {
    return numberOfElements;
}

/*
 * Returns a pointer to the first element in vector.
 */
template<typename T>
T* MyVector<T>::begin() const {
    return storage;
}

/*
 * Returns a pointer to the last element in vector.
 */
template<typename T>
T* MyVector<T>::end() const {
    return storage + numberOfElements;
}

#endif	// MY_VECTOR_H

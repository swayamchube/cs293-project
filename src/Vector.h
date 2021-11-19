#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <cstdio>
#include <cstdlib>
#include <cstddef>
#include <memory>
#include <stdexcept>

/**
 * Following is an iterator class for the vector class
 * The iterator is required for writing member based for loops
 *
 * This is basically a wrapper around a pointer that points to
 * a specific location in the vector which is provided in the 
 * constructor.
 *
 * To spawn an iterator, use
 * Vector<type>::iterator it = vec.begin(); or something like that 
 */
template<class Vec>
class Iterator {
public:
	using value_type = typename Vec::value_type;
	using pointer_type = value_type*;
	using reference_type = value_type&;

public:
	/* Constructor */
	Iterator(pointer_type ptr) : m_ptr(ptr) { }

	// Using the default destructor 
	
	/* Operator Overloads */
	Iterator& operator++() {
		m_ptr++;
		return *this;
	}

	Iterator operator++(int) {
		Iterator temp = *this;
		++(*this);
		return temp;
	}

	Iterator& operator--() {
		m_ptr--;
		return *this;
	}

	Iterator operator--(int) {
		Iterator temp = *this;
		--(*this);
		return temp;
	}

	bool operator==(Iterator& rhs) {
		 return m_ptr == rhs.m_ptr;
	}

	bool operator!=(Iterator& rhs) {
		 return m_ptr != rhs.m_ptr;
	}

	reference_type operator[](unsigned long index) {
		return *(m_ptr + index);
	}

	pointer_type operator->() {
		return m_ptr;
	}

	reference_type operator*() {
		return *m_ptr;
	}

private:
	pointer_type m_ptr;
};

template<typename T>
class Vector {
public:
	using value_type = T;
	using pointer_type = T*;
	using reference_type = T&;
	using iterator = Iterator<Vector<T>>;

public:
	/* Constructors */
	Vector() {
		m_size = 0;
		m_capacity = 2;
		m_ptr = new T[m_capacity];
	}
	Vector(unsigned long size) : m_size(size), m_capacity(size) {
		m_ptr = new T[size];
	}

	/* Destructor */
	~Vector() {
		delete[] m_ptr;
	}

	/* Member Functions */
	void push_back(T val) {
		if (m_size == m_capacity) {
			realloc();
		}

		m_ptr[m_size++] = val;
	}

	bool isEmpty() const {
		return m_size == 0;
	}

	unsigned long size() const {
		return m_size;
	}

	unsigned long capacity() const {
		return m_capacity;
	}
	
	// returns an iterator at the beginning of the vector
	iterator begin() const {
		return iterator(m_ptr);
	}
	
	// returns an iterator at the end of the vector
	iterator end() const {
		return iterator(m_ptr);
	}

	/* Operator Overloads */
	T& operator[](unsigned long index) const {
		// check for out of bounds access
		if (index >= m_size) { 
			throw std::out_of_range("Error: Out of bounds access");
		}
		return *(m_ptr + index);
	}

private:
	void realloc() {
		m_capacity *= 2;
		T* new_ptr = new T[m_capacity];

		for (int i = 0; i < m_size; ++i) {
			new_ptr[i] = m_ptr[i];
		}

		T* temp = m_ptr;

		m_ptr = new_ptr;

		new_ptr = nullptr;

		delete[] temp;
	}

private:
	unsigned long m_size;
	unsigned long m_capacity;
	T* m_ptr;
};

#endif //__VECTOR_H__

#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <cstdio>
#include <cstdlib>
#include <cstddef>
#include <memory>
#include <stdexcept>

template<typename T>
class Vector {
public:
	using value_type = T;
	using pointer_type = T*;
	using reference_type = T&;
public:
	/* Constructors */
	Vector();
	Vector(unsigned long);

	/* Destructor */
	~Vector();

	/* Member Functions */
	void push_back(T);
	bool isEmpty();
	unsigned long size();

	/* Operator Overloads */
	T& operator[](unsigned long);
private:
	void realloc();
private:
	unsigned long m_size;
	unsigned long m_capacity;
	T* m_ptr;
};

#endif //__VECTOR_H__

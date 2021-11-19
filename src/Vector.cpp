#include "Vector.h"
#include <SFML/Graphics.hpp>

template<typename T>
Vector<T>::Vector() {
	m_size = 0;
	m_capacity = 2;
	m_ptr = new T[m_capacity];
}

template<typename T>
Vector<T>::Vector(unsigned long size) : m_size(size), m_capacity(size) {
	m_ptr = new T[size];
}

template<typename T>
Vector<T>::~Vector() {
	delete[] m_ptr;
}


template<typename T>
void Vector<T>::push_back(T val) {
	if (m_size == m_capacity) {
		realloc();
	}
	m_ptr[m_size++] = val;
}

template<typename T>
bool Vector<T>::isEmpty() {
	return m_size == 0;
}

template<typename T>
unsigned long Vector<T>::size() {
	return m_size;
}

template<typename T>
T& Vector<T>::operator[](unsigned long index) {
	if (index >= m_size) {
		throw std::out_of_range("Error: Out of bounds access");
	}
	return *(m_ptr + index);
}

template<typename T>
void Vector<T>::realloc() {
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

template class Vector<sf::Image>;
template class Vector<sf::Sprite>;
template class Vector<sf::Texture>;

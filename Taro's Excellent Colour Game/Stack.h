#pragma once

#include <crtdbg.h>
#include <cstdlib>

/**
 * A LIFO data structure.
 * @tparam T The type of data stored in this stack.
 */
template<typename T>
class Stack
{
public:
	/**
	 * @brief Initialises the contents array.
	 * @param growth The default capacity of the stack.
	 */
	Stack(size_t growth = 4);

	Stack(const Stack& copy);

	// Release the memory of the stack.
	~Stack();

public:
	/**
	 * @brief The passed data onto the top of the stack.
	 * @param data The data to add to the stack.
	 */
	void Push(T data);

	// Removes the top item from the stack
	void Pop();

	// Get the value of the top item of the stack.
	T Top();

	// Returns how large the stack currently is.
	size_t Count() const;

private:
	//The managed memory of the stack
	T* m_contents;

	//How much the stack will grow when it overflows
	size_t m_growth;

	// The current maximum size of the stack.
	size_t m_capacity;

	// The current amount of items in the stack.
	size_t m_count;

private:
	//Reallocates and copies the iternal buffer of memory when overflown.
	void Resize();

};

//**************************************** DEFINITIONS ************** :)))))) MEW

#pragma once
#include <cassert>

template <typename T>
Stack<T>::Stack(size_t growth)
	: m_contents{ new T[growth] }, m_growth{ growth }, m_capacity{ growth }, m_count{ 0 }
{}

template <typename T>
Stack<T>::Stack(const Stack& copy)
{
	m_capacity = copy.m_capacity;
	m_growth = copy.m_growth;
	m_count = copy.m_count;

	void* contents = malloc(sizeof(T) * m_capacity);

	if (m_count != 0)
	{
		//There is atleast one item in the original, so copy it across.
		memcpy_s(contents, sizeof(T) * copy.m_count, copy.m_contents, sizeof(T) * copy.m_count);
	}

	m_contents = static_cast<T*>(contents);
}

template <typename T>
Stack<T>::~Stack()
{
	delete[] m_contents;
	m_contents = nullptr;

	m_count = 0;
}

template <typename T>
void Stack<T>::Push(T data)
{
	if (m_count + 1 >= m_capacity)
	{
		Resize();
	}
	m_contents[m_count++] = data;
}

template <typename T>
void Stack<T>::Pop()
{
	if (m_count > 0)
	{
		m_count--;
	}
}

template <typename T>
T Stack<T>::Top()
{
	return m_count > 0 ? m_contents[m_count - 1] : T{};
}

template <typename T>
size_t Stack<T>::Count() const
{
	return m_count;
}

template <typename T>
void Stack<T>::Resize()
{
	m_capacity += m_growth;

	//Allocates a new piece of memory wth the new capacity and copy the old into the new
	void* newMem = malloc(sizeof(T) * m_capacity);
	memcpy_s(newMem, sizeof(T) * m_count, m_contents, sizeof(T) * m_count);

	//Clean up the old array and assign it to the new one
	free(m_contents);
	m_contents = static_cast<T*>(newMem);

}

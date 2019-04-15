#include <iostream>
#include <assert.h>
#include<vector>
#include<string>
#include<cstdio>
#include"exprtk.h"
#include "Project.h"

using namespace std;

template <class T>
StackInfix<T>::StackInfix()
{
	capacity = 10;
	elements = 0;
	arr = new T[capacity];

}

template <class T>
void StackInfix<T>::push(T value)
{
	if( elements == capacity )
	{
		Expand();
	}
	arr[elements] = value;
	elements++;

}

template <class T>
void StackInfix<T>::pop()
{
	assert(!isempty());
	elements--;
}

template<class T>
T StackInfix<T>::top()
{
	assert(!isempty());
	return arr[elements - 1];
}

template <class T>
bool StackInfix<T>::isempty()
{
	return (elements == 0);	

}

template <class T>
void StackInfix<T>::Expand()
{
	capacity*=2;
	T* temp = new T [capacity];
	for (int i=0 ; i<elements ; i++)
	{
		temp[i] = arr[i];
	}
	delete [] arr;
	arr= temp;
}

template <class T>
int StackInfix<T>::Length()
{
	return elements;
}

template <class T>
StackInfix<T>::~StackInfix(void)
{
	delete[] arr;
}


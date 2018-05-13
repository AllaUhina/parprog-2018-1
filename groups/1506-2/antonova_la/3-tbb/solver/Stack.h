#ifndef __STACK_H__
#define __STACK_H__

#include <iostream>

const int MaxStackSize = 100;

//������ �����

template <class T>
class TStack
{
	T *pMem; //������ ��� �������� ��������� �����
	int size; //������ �����
	int top; //����� �������� ��������
public:
	TStack(const int _size = 10);  //����������� �� ���������
	~TStack(); //����������
	T GetTop();  //�������� ������� ������� ����� ��� ��������
	bool IsEmpty(void) const; //�������� ������� �����
	bool IsFull(void) const;  //�������� ������� �����
	void Push(const T val); //�������� ������� � ����
	T Pop(); //������� ������� �� ����� c ���������
};

template <class T>
TStack<T>::TStack(const int _size)
{
	if ((_size < 1) || (_size > MaxStackSize))
		throw size;
	size = _size;
	top = -1;
	pMem = new T[size];
}

template <class T>
TStack<T>::~TStack()
{
	delete[] pMem;
}


template <class T>
bool TStack<T>::IsEmpty(void) const
{
	return (top == (-1));
}

template <class T>
bool TStack<T>::IsFull(void) const
{
	return (top == (size - 1));
}

template <class T>
T TStack<T>::GetTop()
{
	return pMem[top];
}

template <class T>
void TStack<T>::Push(const T val)
{
	if (IsFull()) throw "Error";
	else { pMem[++top] = val; }
}

template <class T>
T TStack<T>::Pop()
{
	if (IsEmpty()) throw "Error";
	else return pMem[top--];
}


#endif
#pragma once

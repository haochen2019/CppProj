#pragma  once 
#include <iostream>
using std::cout;
using std::endl;

typedef int Rank;//��
#define DEFAULT_CAPCITY 3

template <typename T> 
class Vector
{
public:
	//����
	Vector(int c = DEFAULT_CAPCITY, int s = 0,T v = 0)
	{
		_elem = new T[_capacity = c];
		for (_size = 0; _size < s; _size++)
		{
			_elem[_size] = v; 
		}
	}
	
	//������������
	void copyFrom(const T* A, Rank lo, Rank hi);

	//��д���ʽӿ�
	Vector& operator=(const Vector<T>& V);
	//����
	template<typename VST> 
	void traverse(VST&);
protected:
	Rank _size;//��ģ
	int _capacity;//����
	T* _elem;//������
};

//////////////////////////////////////////////////////////////////////////
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& V)
{
	//����Ը�ֵ������
	if (_elem)
		delete[] _elem;
	copyFrom(V._elem, 0, V._size);
	return *this;
}

//////////////////////////////////////////////////////////////////////////
template <typename T> template <typename VST>
void Vector<T>::traverse(VST& visit)
{
	for (int i = 0; i < _size; i++)//��������
	{
		visit(_elem[i]);
	}
}

//////////////////////////////////////////////////////////////////////////
template <typename T>
void Vector<T>::copyFrom(const T* A, Rank lo, Rank hi)
{
	_elem = new T[_capacity = 2 * (hi - lo)];
	_size = 0;//��ģ������ͷ��ʼ��ʼ��
	while (lo < hi)
	{
		_elem[_size++] = A[lo++];
	}
}


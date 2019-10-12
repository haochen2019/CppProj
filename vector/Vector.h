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
	
	//ֻ�����ʽӿ�
	Rank find(const T& e, Rank lo, Rank hi)const;//���������������

	//��д���ʽӿ�
	Vector& operator=(const Vector<T>& V);
	T& operator[](Rank r);
	void unsort(Rank lo, Rank hi);//��[lo,hi)��������
	Rank insert(Rank r, const T& e);//����Ԫ��
	//����
	template<typename VST> 
	void traverse(VST&);

protected:
	void copyFrom(const T* A, Rank lo, Rank hi);	//������������
	void expand();//�ռ䲻��ʱ����
	void shrink();//װ�����ӹ�Сʱѹ��
protected:
	Rank _size;//��ģ
	int _capacity;//����
	T* _elem;//������
};

template <typename T>
Rank Vector<T>::insert(Rank r, const T& e)
{
	expand();//�ж��Ƿ�overflow
	for (int i = _size; i > _size;i--)//�Ժ���ǰ�����Ԫ��˳�κ���һ����λ
	{
		elem[i] = _elem[i-1];
	}
	_elem[r] = e;
	_size++;
	return r;
}

//////////////////////////////////////////////////////////////////////////
template <typename T>
Rank Vector<T>::find(const T& e, Rank lo, Rank hi) const
{
	while (lo < hi-- && e!= _elem[hi]);
	return hi;
}

//////////////////////////////////////////////////////////////////////////
template <typename T>
void Vector<T>::unsort(Rank lo, Rank hi)
{
	T* V = _elem + lo;
	for (Rank i = hi - lo;i > 0;i--)
	{
		swap(V[i - 1], _elem[rand() % i]);
	}
}

//////////////////////////////////////////////////////////////////////////
template <typename T>
T& Vector<T>::operator[](Rank r)
{
	return _elem[r];
}

//////////////////////////////////////////////////////////////////////////
template <typename T>
void Vector<T>::expand()
{
	if (_size < _capacity)
		return;
	if (_capacity < DEFAULT_CAPCITY)
	{
		_capacity = DEFAULT_CAPCITY;
	}
	T* oldElem = _elem;
	_elem = new T[_capacity <<= 1];
	for (int i = 0; i < _size;i++)
	{
		_elem[i] = oldElem[i];
	}
	delete[] oldElem;//�ͷ�ԭ�ռ�
}

//////////////////////////////////////////////////////////////////////////
template <typename T>
void Vector<T>::shrink()
{
	if (_capacity < DEFAULT_CAPCITY<<1)
	{
		return;
	}
	if (_size << 2 > _capacity)//_size*4
	{
		return;
	}
	T* oldElem = _elem;
	_elem = new T[_capacity >>= 1];
	for (int i = 0; i < _size;i++)
	{
		_elem[i] = oldElem[i];
	}
	delete[] oldElem;
}
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


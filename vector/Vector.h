#pragma  once 
#include <iostream>
using std::cout;
using std::endl;

typedef int Rank;//秩
#define DEFAULT_CAPCITY 3

template <typename T> 
class Vector
{
public:
	//构造
	Vector(int c = DEFAULT_CAPCITY, int s = 0,T v = 0)
	{
		_elem = new T[_capacity = c];
		for (_size = 0; _size < s; _size++)
		{
			_elem[_size] = v; 
		}
	}
	
	//复制数组区间
	void copyFrom(const T* A, Rank lo, Rank hi);

	//可写访问接口
	Vector& operator=(const Vector<T>& V);
	//遍历
	template<typename VST> 
	void traverse(VST&);
protected:
	Rank _size;//规模
	int _capacity;//容量
	T* _elem;//数据区
};

//////////////////////////////////////////////////////////////////////////
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& V)
{
	//检查自赋值？？？
	if (_elem)
		delete[] _elem;
	copyFrom(V._elem, 0, V._size);
	return *this;
}

//////////////////////////////////////////////////////////////////////////
template <typename T> template <typename VST>
void Vector<T>::traverse(VST& visit)
{
	for (int i = 0; i < _size; i++)//遍历向量
	{
		visit(_elem[i]);
	}
}

//////////////////////////////////////////////////////////////////////////
template <typename T>
void Vector<T>::copyFrom(const T* A, Rank lo, Rank hi)
{
	_elem = new T[_capacity = 2 * (hi - lo)];
	_size = 0;//规模清理，从头开始初始化
	while (lo < hi)
	{
		_elem[_size++] = A[lo++];
	}
}


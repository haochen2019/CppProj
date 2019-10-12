#pragma once 

#include <new>
#include <cstddef>
#include <iostream>
#include <cstdlib>
#include <climits>

namespace JJ
{
	//分配内存并返回指针
	template<class T>
	inline T* _allocate(ptrdiff_t size, T*)
	{
		set_new_handler(0);
		T* tmp = (T*)(::operator new((size_t)(size * sizeof(T))));
		if (tmp == 0)
		{
			cerr << "out of memory" << endl;
			exit(1);
		}
		return tmp;
	}

	//释放内存
	template<class T>
	inline void _deallocate(T* buffer)
	{
		::operator delete(buffer);
	}

	template <class T1, class T2>
	inline void _construct(T1* p, const T2& value)
	{
		new(p)T1(value);//placement new在已有内存（p所指地址）上构造对象
	}

	template <class T>
	inline void _destory(T* ptr)
	{
		ptr->~T();
	}

	template <class T>
	class allocator
	{
	public:
		typedef T value_type;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef T&	reference;
		typedef const T& const_reference;
		typedef size_t  size_type;
		typedef ptrdiff_t difference_type;

		//rebind allocator of type U
		template <class U>
		struct rebind
		{
			typedef allocator<U> other;
		};

		pointer allocate(size_type n, const void* hint = 0)
		{
			return _allocate((difference_type)n, (pointer)0);
		}

		void  deallocate(pointer p, size_type n){ _deallocate(p); }//n的用处

		void construct(pointer p, const T& value)
		{
			_construct(p, value);
		}

		void destroy(pointer p){ _destory(p); }

		pointer address(reference x){ return (pointer)&x; }
		const_pointer const_address(const_reference x){ return (const_pointer)&x; }

		size_type max_size()const
		{
			return size_type(UINT_MAX / sizeof(T));
		}
	};
}

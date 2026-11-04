// This file is Copyright (c) Shadowed Works
// Please check Demi3D.h for a detailed description of the zlib license.
/*
	I would like to thank Nikolaus Gebhardt for his excellently commented irrarray.h,
	which I was able to learn from to write this file.
*/


#ifndef __DM_ARRAY_INCLUDED__
#define __DM_ARRAY_INCLUDED__

#include <memory>
#include <utility>

namespace demi
{
	template <class T>
	class array
	{
	protected:
		T* Data;
		unsigned int Used;
		unsigned int Allocated;
	public:
		array() : Data(nullptr), Used(0), Allocated(0) {}
		array(const array& other) : array()
		{
			auto data = std::make_unique<T[]>(other.Allocated);
			for (unsigned int i = 0; i < other.Used; ++i)
				data[i] = other.Data[i];
			Data = data.release();
			Used = other.Used;
			Allocated = other.Allocated;
		}

		array& operator=(array other)
		{
			std::swap(Data, other.Data);
			std::swap(Used, other.Used);
			std::swap(Allocated, other.Allocated);
			return *this;
		}

		virtual ~array() { delete[] Data; }

		virtual void push_back(const T & element)
		{
			if(Used + 1 > Allocated)
			{
				T elmt;
				elmt = element;
				reallocate(Used*2+1);
				Data[Used++] = elmt;
				return;
			}

			Data[Used++] = element;
		}

		virtual void add(const T & element)
		{
			push_back(element);
		}

		virtual void remove(unsigned int index)
		{
			if (index >= Used) return;
			for (unsigned int n = index + 1;n < Used;n++)
				Data[n - 1] = Data[n];
			Used--;
		}

		virtual void erase(unsigned int index)
		{
			remove(index);
		}

		virtual void reallocate(unsigned int size)
		{
			auto data = std::make_unique<T[]>(size);
			const unsigned int count = Used < size ? Used : size;
			for (unsigned int i = 0; i < count; ++i)
				data[i] = Data[i];
			delete[] Data;
			Data = data.release();
			Used = count;
			Allocated = size;
		}

		virtual void clear()
		{
			delete[] Data;
			Data		= 0;
			Used		= 0;
			Allocated	= 0;
		}

		virtual T* data()
		{
			return Data;
		}

		virtual unsigned int size()
		{
			return Used;
		}

		T& operator [] (unsigned int index)
		{
			return Data[index];
		}

		void operator += (const T & element)
		{
			add(element);
		}

		void operator -- ()
		{
			remove(Used-1);
		}
	};
}

#endif

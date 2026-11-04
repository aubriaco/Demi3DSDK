
#ifndef __DM_LIST_INCLUDED__
#define __DM_LIST_INCLUDED__
#include <memory>

namespace demi
{

	template <class T>
	class list
	{
	private:
		class node
		{
		public:
			T Data;
			node* Next;
			node* Previous;

			node() : Next(0), Previous(0) {}
		};
	public:
		class iterator
		{
		private:
			friend class list<T>;

			node* Current;

			iterator(node* begin) : Current(begin) {}
		public:
			iterator() : Current(0) {}

			iterator& operator++() { Current = Current->Next; return *this; }
			iterator& operator--() { Current = Current->Previous; return *this; }

			bool operator!=(const iterator& other) { return (Current != other.Current); }

			T& operator*() { return Current->Data; }
		};

	private:
		node* Root;
		node* Last;
		int Size;

	public:

		list() : Root(0), Last(0), Size(0) {}
		list(const list&) = delete;
		list& operator=(const list&) = delete;
		~list() { clear(); }

		void clear()
		{
			node* nd = Root;
			while(nd)
			{
				node* next = nd->Next;
				delete nd;
				nd = next;
			}

			Root = 0;
			Last = 0;
			Size = 0;
		}

		bool isEmpty()
		{
			return (Root == 0);
		}

		void push_back(const T& data)
		{
			auto pending = std::make_unique<node>();
			pending->Data = data;
			node* nd = pending.release();
			Size++;
			if(Root == 0)
				Root = nd;
			nd->Previous = Last;
			if(Last != 0)
				Last->Next = nd;
			Last = nd;
		}

		void push_front(const T& data)
		{
			auto pending = std::make_unique<node>();
			pending->Data = data;
			node* nd = pending.release();
			Size++;
			if(Root == 0)
			{
				Last = nd;
				Root = nd;
			}
			else
			{
				nd->Next = Root;
				Root->Previous = nd;
				Root = nd;
			}
		}

		void add(const T& data)
		{
			push_back(data);
		}

		iterator begin()
		{
			return iterator(Root);
		}

		iterator end()
		{
			return iterator(0);
		}

		iterator getLast()
		{
			return iterator(Last);
		}

		iterator remove(iterator& iter)
		{
			iterator retIter(iter);
			++retIter;

			if(iter.Current == Root)
				Root = iter.Current->Next;

			if(iter.Current == Last)
				Last = iter.Current->Previous;

			if(iter.Current->Next)
				iter.Current->Next->Previous = iter.Current->Previous;

			if(iter.Current->Previous)
				iter.Current->Previous->Next = iter.Current->Next;

			delete iter.Current;
			iter.Current = 0;
			Size--;

			return retIter;
		}

	};
}

#endif

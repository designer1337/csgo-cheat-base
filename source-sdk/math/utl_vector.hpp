#pragma once
#include <assert.h>
template <class T, class I = int> class utl_memory
{
public:
	inline bool IsIdxValid(I i) const
	{
		long x = i;
		return (x >= 0) && (x < m_nAllocationCount);
	}
	T& operator[](I i);
	const T& operator[](I i) const;
	T* Base()
	{
		return m_pMemory;
	}
	inline int NumAllocated() const
	{
		return m_nAllocationCount;
	}
	void Grow(int num)
	{
		assert(num > 0);

		auto oldAllocationCount = m_nAllocationCount;
		// Make sure we have at least numallocated + num allocations.
		// Use the grow rules specified for this memory (in m_nGrowSize)
		int nAllocationRequested = m_nAllocationCount + num;

		int nNewAllocationCount = UtlMemory_CalcNewAllocationCount(m_nAllocationCount, m_nGrowSize, nAllocationRequested, sizeof(T));

		// if m_nAllocationRequested wraps index type I, recalculate
		if ((int)(I)nNewAllocationCount < nAllocationRequested)
		{
			if ((int)(I)nNewAllocationCount == 0 && (int)(I)(nNewAllocationCount - 1) >= nAllocationRequested)
			{
				--nNewAllocationCount; // deal w/ the common case of m_nAllocationCount == MAX_USHORT + 1
			}
			else
			{
				if ((int)(I)nAllocationRequested != nAllocationRequested)
				{
					// we've been asked to grow memory to a size s.t. the index type can't address the requested amount of memory
					assert(0);
					return;
				}
				while ((int)(I)nNewAllocationCount < nAllocationRequested)
				{
					nNewAllocationCount = (nNewAllocationCount + nAllocationRequested) / 2;
				}
			}
		}

		m_nAllocationCount = nNewAllocationCount;

		if (m_pMemory)
		{
			auto ptr = new unsigned char[m_nAllocationCount * sizeof(T)];

			memcpy(ptr, m_pMemory, oldAllocationCount * sizeof(T));
			m_pMemory = (T*)ptr;
		}
		else
		{
			m_pMemory = (T*)new unsigned char[m_nAllocationCount * sizeof(T)];
		}
	}
protected:
	T* m_pMemory;
	int m_nAllocationCount;
	int m_nGrowSize;
};

template< class T, class I >
inline T& utl_memory<T, I>::operator[](I i)
{
	assert(IsIdxValid(i));
	return m_pMemory[i];
}

template< class T, class I >
inline const T& utl_memory<T, I>::operator[](I i) const
{
	assert(IsIdxValid(i));
	return m_pMemory[i];
}

template< class T, class A = utl_memory<T> >
class utl_vector
{
	typedef A CAllocator;

	typedef T* iterator;
	typedef const T* const_iterator;
public:
	T& operator[](int i);
	const T& operator[](int i) const;

	T& Element(int i)
	{
		return m_Memory[i];
	}

	T* Base()
	{
		return m_Memory.Base();
	}

	int count() const
	{
		return m_Size;
	}

	void remove_all()
	{
		for (int i = m_Size; --i >= 0; )
			Destruct(&Element(i));

		m_Size = 0;
	}

	inline bool IsValidIndex(int i) const
	{
		return (i >= 0) && (i < m_Size);
	}

	void GrowVector(int num = 1)
	{
		if (m_Size + num > m_Memory.NumAllocated())
		{
			m_Memory.Grow(m_Size + num - m_Memory.NumAllocated());
		}

		m_Size += num;
	}

	int InsertBefore(int elem)
	{
		// Can insert at the end
		assert((elem == count()) || IsValidIndex(elem));

		GrowVector();
		Construct(&Element(elem));
		return elem;
	}

	inline int AddToHead()
	{
		return InsertBefore(0);
	}

	inline int AddToTail()
	{
		return InsertBefore(m_Size);
	}

	iterator begin() { return Base(); }
	const_iterator begin() const { return Base(); }
	iterator end() { return Base() + count(); }
	const_iterator end() const { return Base() + count(); }

protected:
	CAllocator m_Memory;
	int m_Size;
	T* m_pElements;
};

template< typename T, class A >
inline T& utl_vector<T, A>::operator[](int i)
{
	assert(i < m_Size);
	return m_Memory[i];
}

template< typename T, class A >
inline const T& utl_vector<T, A>::operator[](int i) const
{
	assert(i < m_Size);
	return m_Memory[i];
}
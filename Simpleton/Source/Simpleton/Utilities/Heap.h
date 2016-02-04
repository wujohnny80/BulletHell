#ifndef _HEAP_H_
#define _HEAP_H_

#include <algorithm>
#include <limits>
#include <vector>

template <typename T>
class Heap
{
public:
	Heap();
	~Heap();

	void Insert(T);
	T Remove();
	void Clear();

	int Size() const	{ return mSize; }

private:
	void HeapUp(int child);
	void HeapDown(int parent);
	void Swap(T& lhs, T& rhs);

	int mSize;
	std::vector<T> mData;
};

#include "Heap.inl"
#endif // _HEAP_H_
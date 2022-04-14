#pragma once
#include <cassert>
#include "Defines.h"

template<class T>
class ObjectPool
{
public:

	T* getAll() {
		return objects;
	}

	int getCount() { return count; }
	int getActiveCount() { return activeCount; }

	ObjectPool(int poolSize) {
		count = 0;
		activeCount = 0;
		objects = new T[poolSize];
	}
	~ObjectPool() {
		delete[] objects;
	}

	int getIndexOf(T* object) {
		int index = (object - objects);
		assert(index >= 0 && index < count);

		return index;
	}

	T* instansiate() {
		return &objects[count++];
	}

private:

	int count;
	int activeCount;
	T* objects;

	void swap(T* First, T* Second) {
		int first = getIndexOf(First);
		int second = getIndexOf(Second);

		swap(first, second);
	}

	void swap(int first, int second) {
		T temp = objects[first];
		objects[first] = objects[second];
		objects[second] = temp;

		objects[second].onSwap(second);
		objects[first].onSwap(first);
	}

	void activate(T* object) {
		assert(&objects[activeCount-1] < object);
		if (getIndexOf(object) != activeCount)
			swap(getIndexOf(object), activeCount);

		activeCount++;
	}
	void deactivate(T* object) {
		activeCount--;
		assert(&objects[activeCount] >= object);
		if (&objects[activeCount] == object) 
			return;

		swap(getIndexOf(object), activeCount);
	}

	void destroy(T* object) {
		count--;
		assert(object <= &objects[count]);
		if (object != &objects[count]) {
			swap(getIndexOf(object), count);
		}
	}
	friend T;
};


#ifndef __Vector__
#define __Vector__

#include <iostream>

using namespace std;

template <typename T>
class Vector {
private:
	T* buffer;
	unsigned int capacity;
public:
	//Constructor.
	Vector() {
		capacity = 0;
		buffer = new T[capacity];
	}
	//Copy constructor.
	Vector(const Vector& asv) {
		int i;

		capacity = asv.size();
		buffer = new T[asv.size()];
		for (i = 0; i < capacity; i++) {
			buffer[i] = asv[i];
		}
	}
	//Destructor.
	~Vector() {
		delete[]buffer;
	}
	void push_back(T obj) {
		Vector oldSV(*this);
		int i;

		capacity++;
		delete[]buffer;
		buffer = new T[capacity];
		for (i = 0; i < oldSV.size(); i++) {
			buffer[i] = oldSV[i];
		}
		buffer[i] = obj;
	};
	T getBuffer() const {
		if (capacity == 0) {
			throw exception();
		}
		return *buffer;
	};
	T& operator[](int index) const {
		if (index >= capacity) {
			//Out of range.
			throw exception();
		}
		else {
			return buffer[index];
		}
	}
	Vector& operator=(const Vector& obj) {
		capacity = obj.size();
		delete[]buffer;
		buffer = new T[capacity];
		buffer = obj.getBuffer();
		return *this;
	}
	unsigned int size() const {
		return capacity;
	};
};

#endif

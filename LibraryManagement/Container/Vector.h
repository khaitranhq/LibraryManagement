#pragma once
template <class T> class Vector{
    private:
        T *arr;
        unsigned int capacity;
    public:
        Vector();
        Vector(unsigned int size);
        Vector(const Vector<T>& v);
        ~Vector();

        void push_back(const T& value);
        void pop_back();
        void clear();

        T& front();
        T& back();

        unsigned int size();
        T& operator[](unsigned int index);
};



/*=====================Definition of method class====================*/

template <class T> Vector<T>::Vector(){
    capacity = 0;
    arr = 0;
}

template <class T> Vector<T>::Vector(unsigned int size){
    capacity = size;
    arr = new T[size];
}

template <class T> Vector<T>::Vector(const Vector<T>& v){
    this -> capacity = v.capacity;
    delete[] arr;
    arr = v.arr;
}

template <class T> Vector<T>::~Vector(){
    delete[] arr;
}

template <class T> unsigned int Vector<T>::size(){
    return capacity;
}

template <class T> void Vector<T>::push_back(const T& value){
    T* tmp = new T[capacity + 1];
    for(int i = 0 ; i < capacity ; ++i)
        tmp[i] = arr[i];
    tmp[capacity] = value;
    delete[] arr;
    arr = tmp; ++capacity;
}

template <class T> void Vector<T>::pop_back(){
    T* tmp = new T[capacity - 1];
    for(int i = 0 ; i < capacity - 1 ; ++i)
        tmp[i] = arr[i];
    delete[] arr;
    arr = tmp; --capacity;
}

template <class T> void Vector<T>::clear(){
    while(size()) pop_back();
}

template <class T> T& Vector<T>::front(){
    return arr;
}

template <class T> T& Vector<T>::back(){
    return arr + capacity - 1;
}

template <class T> T& Vector<T>::operator[](unsigned int index){
    static int tmp = 0;
    return (index >= 0 && index < capacity) ? arr[index] : tmp;
}

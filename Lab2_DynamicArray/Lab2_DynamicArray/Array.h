#pragma once
#include <iostream>
#include <utility>
#include <string>
constexpr int kDefaultCapacity = 8;

template<typename T>
class Array final{
public:
    Array(); // Default Constructor
    Array(int capacity); // Constructor
    ~Array(); // Destructor
    int insert(const T& value);
    int insert(int index, const T& value);
    void remove(int index);
    const T& operator[](int index) const;
    T& operator[](int index);
    int size() const;
    Array(const Array& other); // Copy Constructor
    Array(Array&& other); // Move Constructor
    void swap(Array other); // Swap
    Array& operator = (const Array& other); //Copy Assignment
    Array& operator = (Array&& other); // Move Assignment

    class Iterator {
    public:
        const T& get() const;
        void set(const T& value);
        void next();
        bool hasNext() const;
        friend Array;
    private:
        int current_index_;
        bool is_reverse_;
        Array *array;
    };
    class ConstIterator {
    public:
        const T& get() const;
        void next();
        bool hasNext() const;
        friend Array;
    private:
        int current_index_;
        bool is_reverse_;
        Array *array;
    };

    Iterator iterator();
    ConstIterator cIterator() const;
    Iterator reverseIterator();
    ConstIterator cReverseIterator() const;
private:
    T* pitems_;
    int size_;
    int capacity_;
};

//Default Constructor
template<typename T>
Array<T>::Array() : capacity_(kDefaultCapacity), size_(0) {
    pitems_ = (T*)malloc(capacity_ * sizeof(T));
}

//Constructor
template<typename T>
Array<T>::Array(int capacity) : capacity_(capacity), size_(0) {
    if (capacity_ <= 0) {
        capacity_ = kDefaultCapacity;
    }
    pitems_ = (T*)malloc(capacity_ * sizeof(T));
}

//Destructor
template<typename T>
Array<T>::~Array() {
    for (int i = 0; i < size_; ++i) {
        pitems_[i].~T();
    }
    free(pitems_);
}

template<typename T>
int Array<T>::insert(const T& value) {
    return insert(size_, value);
}

template<typename T>
int Array<T>::insert(int index, const T& value) {
    if (index < 0) {
        index = 0;
    }

    if (index > size_) {
        index = size_;
    }

    if (size_ + 1 > capacity_) {
        capacity_ *= 2;
        T* temp = (T*)malloc(capacity_ * sizeof(T));
        for (int i = 0; i < size_; ++i) {
            new (temp + i) T(std::move(pitems_[i]));
            pitems_[i].~T();
        }
        std::free(pitems_);
        pitems_ = temp;
    }

    if (index != size_) {
        for (int i = size_ - 1; i >= index; --i) {
            new(pitems_ + i + 1) T(std::move(pitems_[i]));
            pitems_[i].~T();
        }
    }

    new(pitems_ + index) T(value);
    size_ += 1;
    return size_ - 1;
}

template<typename T>
void Array<T>::remove(int index) {
    if (size_ < 1 || index < 0 || index >= size_) {
        return;
    }
    for (int i = index; i < size_ - 1; ++i) {
        pitems_[i].~T();
        new(pitems_ + i) T(std::move(pitems_[i + 1]));
    }
    pitems_[size_ - 1].~T();
    size_ -= 1;
}

template<typename T>
const T& Array<T>::operator[](int index) const {
    return pitems_[index];
}

template<typename T>
T& Array<T>::operator[](int index) {
    return pitems_[index];
}

template<typename T>
int Array<T>::size() const {
    return size_;
}

//Copy Constructor
template<typename T>
Array<T>::Array(const Array<T>& other) : capacity_(other.capacity_), size_(other.size_) {
    pitems_ = (T*)malloc(capacity_ * sizeof(T));
    for (int i = 0; i < size_; ++i) {
        new(pitems_ + i) T(other.pitems_[i]);
    }
}

//Move Constuctor
template<typename T>
Array<T>::Array(Array<T>&& other) {
    pitems_ = other * pitems_;
    size_ = other * size_;
    capacity_ = other * capacity_;
    other.pitems_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

//Swap
template<typename T>
void Array<T>::swap(Array other) {
    std::swap(pitems_, other.pitems_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    return *this;
}

//Copy Assignment
template<typename T>
Array<T>& Array<T>::operator=(const Array& other) {
    if (this == &other)
        return *this;
    Array<T> temp = other;
    free(pitems_);
    capacity_ = other.capacity_;
    size_ = other.size_;
    pitems_ = (T*)malloc(capacity_ * sizeof(T));
    for (int i = 0; i < size_; ++i) {
        new (pitems_ + i) T(other.pitems_[i]);
    }
    return *this;
}

//Move Assignment
template<typename T>
Array<T>& Array<T>::operator=(Array&& other) {
    if (this == other) {
        return *this;
    }
    for (int i = 0; i < size_; ++i) {
        pitems_[i].~T();
    }
    free(pitems_);
    pitems_ = other.pitems_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    other.pitems_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
    return *this;
}

template<typename T>
typename Array<T>::Iterator Array<T>::iterator() {
    Array<T>::Iterator temp;
    temp.current_index_ = 0;
    temp.is_reverse_ = false;
    temp.array = this;
    return temp;
}

template<typename T>
typename Array<T>::ConstIterator Array<T>::cIterator() const {
    Array<T>::ConstIterator temp;
    temp.current_index_ = 0;
    temp.is_reverse_ = false;
    temp.array = this;
    return temp;
}

template<typename T>
typename Array<T>::Iterator Array<T>::reverseIterator() {
    Array<T>::Iterator temp;
    temp.current_index_ = size_ - 1;
    temp.is_reverse_ = true;
    temp.array = this;
    return temp;
}

template<typename T>
typename Array<T>::ConstIterator Array<T>::cReverseIterator() const {
    Array<T>::ConstIterator temp;
    temp.current_index_ = size_ - 1;
    temp.is_reverse_ = true;
    temp.array = this;
    return temp;
}

template<typename T>
const T& Array<T>::Iterator::get() const {
    return (*array)[current_index_];
}

template<typename T>
void Array<T>::Iterator::set(const T& value) {
    (*array)[current_index_] = value;
}

template<typename T>
void Array<T>::Iterator::next() {
    if (is_reverse_) {
        current_index_ -= 1;
    }
    else {
        current_index_ += 1;
    }
}

template<typename T>
bool Array<T>::Iterator::hasNext() const {
    if (is_reverse_) {
        if (current_index_ - 1 < 0) {
            return false;
        }
    }
    else {
        if (current_index_ + 1 > array->size_) {
            return false;
        }
    }
    return true;
}

template<typename T>
const T& Array<T>::ConstIterator::get() const {
    return (*array)[current_index_];
}

template<typename T>
void Array<T>::ConstIterator::next() {
    if (is_reverse_) {
        current_index_ -= 1;
    }
    else {
        current_index_ += 1;
    }
}

template<typename T>
bool Array<T>::ConstIterator::hasNext() const {
    if (is_reverse_) {
        if (current_index_ - 1 < 0) {
            return false;
        }
    }
    else {
        if (current_index_ + 1 > array->size_) {
            return false;
        }
    }
    return true;
}

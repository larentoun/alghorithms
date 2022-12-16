#pragma once
#include <string>
#include <algorithm>

constexpr int kInsertSortSize = 128;
constexpr int kArraySize = 800;

//v3
template<typename T, typename Compare>
void combinedSort(T* first, T* last, Compare comp) {
	if (first > last) {
		return;
	}
	T* left = first;
	T* right = last;
	while (left < right) {
		if (right - left <= kInsertSortSize) {
			insertSort(left, right, comp);
			return;
		}
		T* part = partition(left, right, comp);
		if (part - left < right - part) {
			quickSort(left, part, comp);
			left = part + 1;
		}
		else {
			quickSort(part + 1, right, comp);
			right = part;
		}
	}
}

//v3
template<typename T, typename Compare>
void quickSort(T* first, T* last, Compare comp) {
	if (first > last) {
		return;
	}
	T* left = first;
	T* right = last;
	while (left < right) {
		T* part = partition(left, right, comp);
		if (part - left < right - part) {
			quickSort(left, part, comp);
			left = part + 1;
		}
		else {
			quickSort(part + 1, right, comp);
			right = part;
		}
	}
}

//v2
template<typename T, typename Compare>
void insertSort(T* first, T* last, Compare comp) {
	if (first == last) {
		return;
	}
	T tmp;
	T* tailingIndex;
	for (T* indexToCheck = first; indexToCheck <= last; ++indexToCheck) {
		tmp = *indexToCheck;
		tailingIndex = indexToCheck;
		while (tailingIndex > first && comp(tmp, *(tailingIndex - 1))) {
			*tailingIndex = std::move(*(tailingIndex - 1));
			--tailingIndex;
		}
		*tailingIndex = tmp;
	}
}

template<typename T, typename Compare>
T getPivot(T* first, T* middle, T* last, Compare comp) {
	if (comp(*middle, *first)) {
		std::swap(*middle, *first);
	}
	if (comp(*last, *first)) {
		std::swap(*last, *first);
	}
	if (comp(*last, *middle)) {
		std::swap(*last, *middle);
	}
	return *middle;
}

template<typename T, typename Compare>
T* partition(T* first, T* last, Compare comp) {
	T* middle = first + (last - first) / 2;
	T pivot = getPivot(first, middle, last, comp);
	T* left = first;
	T* right = last;
	while (true) {
		while (comp(*left, pivot)) {
			left++;
		}
		while (comp(pivot, *right)) {
			right--;
		}
		if (left >= right)
			break;
		std::swap(*left, *right);
	}
	return right;
}

void populateIntArray(int a[], int arraySize) {
	for (int i = 0; i < arraySize; ++i) {
		a[i] = arraySize - i;
	}
}

bool checkArray(int a[], int arraySize) {
	for (int i = 0; i < arraySize - 1; ++i) {
		if (a[i] > a[i + 1]) {
			return false;
		}
	}
	return true;
}
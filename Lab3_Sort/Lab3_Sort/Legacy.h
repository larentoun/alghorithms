#pragma once

/*
template<typename T, typename Compare>
void combinedSort(T* first, T* last, Compare comp) {
	if (first > last) {
		return;
	}
	if (last - first < kInsertSortSize) {
		insertSort(first, last, comp);
		return;
	}
	quickSort(first, last, comp);
}*/

/* V1
template<typename T, typename Compare>
void combinedSort(T* first, T* last, Compare comp) {
	T* pivotLeft = partition(first, last, comp);
	T* pivotRight = pivotLeft + 1;
	while (first < pivotLeft) {
		if (pivotLeft - first < kInsertSortSize) {
			insertSort(first, pivotLeft, comp);
			break;
		}
		pivotLeft = partition(first, pivotLeft, comp);
	}
	while (pivotRight < last - 1) {
		if (last - 1 - pivotRight < kInsertSortSize) {
			insertSort(pivotRight, last, comp);
			break;
		}
		pivotRight = partition(pivotRight, last, comp);
}*/

/* V2
template<typename T, typename Compare>
void quickSort(T* first, T* last, Compare comp) {
	if (first > last) {
		return;
	}
	T* pivotLeft = partition(first, last, comp);
	T* pivotRight = pivotLeft + 1;
	if (pivotLeft - first < last - pivotRight) {
		quickSort(first, pivotLeft, comp);
		while (pivotRight < last - 1) {
			pivotRight = partition(pivotRight, last, comp);
		}
	}
	else {
		quickSort(pivotRight, last, comp);
		while (first < pivotLeft) {
			pivotLeft = partition(first, pivotLeft, comp);
		}
	}
}*/

/* V1
template<typename T, typename Compare>
void quickSort(T* first, T* last, Compare comp) {
	T* pivotLeft = partition(first, last, comp);
	T* pivotRight = pivotLeft + 1;
	while (pivotRight < last - 1) {
		pivotRight = partition(pivotRight, last, comp);
	}
	while (first < pivotLeft) {
		pivotLeft = partition(first, pivotLeft, comp);
	}
}*/
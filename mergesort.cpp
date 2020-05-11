/*
Mergesort:

Worst case: nlogn 	-> Read description
Best case: nlogn	-> 
average case: nlogn	-> 
stable:				-> Yes

Description:
 Classic divide and conquer algorithm. Divides the vector on two, and recursively sorts each half.
 Then merge both halfs on the vector.

**** It takes o(n) memory space, which if is allocated in the merge function makes slower. ****

**** Here I have an implementation with half a vector alocated and pass as pool for the merge, resulting in much better constant ****

*/

#ifndef MERGESORT
#define MERGESORT

#include <cstdlib>
#include <cstring>

// mergesort
template <typename T, typename Func>
void merge(T *v, int pivot, int size, Func eval) {
	int v_l=0, v_r=pivot, sp=0;
	T *sorted = (T *)malloc(size*sizeof(T));

	for (sp=0; sp<size; sp++) {
		if(v_l==pivot || (eval(v[v_r], v[v_l]) && v_r!=size))
			sorted[sp] = v[v_r++];
		else
			sorted[sp] = v[v_l++];
	}

	memcpy(v, sorted, size*sizeof(T));
	free(sorted);
}

template <typename T, typename Func>
void mergesort(T *v, int size, Func eval) {
	// caso base
	if (size == 1) return;

	int pivot = size/2;
	mergesort(&v[0], pivot, eval);
	mergesort(&v[pivot], size-pivot, eval);

	merge(&v[0], pivot, size, eval);
}

// Default order set on ascending
template <typename T>
void mergesort(T *v, int size) {
	mergesort(v, size, [] (T a, T b) { return a<b; });
}

/////////////////////////////////////////////////////////////
// mergesort in place
template <typename T, typename Func>
void mergeInPlace(T *v, int pivot, int size, Func eval, T *pool) {
	int v_l=0, v_r=pivot, s=0;
	memcpy(pool, v, pivot*sizeof(T));

	while (v_l<pivot) {
		if (eval(pool[v_l], v[v_r]) || v_r==size)
			v[s++] = pool[v_l++];
		else
			v[s++] = v[v_r++];
	}
}

template <typename T, typename Func>
void mergesortInPlaceUtil(T *v, int size, Func eval, T *pool) {
	if (size <= 1) return;

	int pivot = size/2;
	mergesortInPlaceUtil(&v[0], pivot, eval, pool);
	mergesortInPlaceUtil(&v[pivot], size-pivot, eval, pool);

	mergeInPlace(&v[0], pivot, size, eval, pool);
}

template <typename T, typename Func>
void mergesortInPlace(T *v, int size, Func eval) {
	T *pool = (T*)malloc(size/2*sizeof(T));
	mergesortInPlaceUtil(v, size, eval, pool);
	free(pool);
}

// Default order set on ascending
template <typename T>
void mergesortInPlace(T *v, int size) {
	mergesortInPlace(v, size, [] (T a, T b) { return a<b; });
}


#ifndef VECTOR_TEST

// Testing
#include <iostream>
#include <ctime>

#include "vector_utility.cpp"

using namespace std;

int main() {
	int size=20;
	int *v = (int*)malloc(size*sizeof(int));
	int *v2 = (int*)malloc(size*sizeof(int));

	initRandomV(v, size, 30, 0);
	memcpy(v2, v, size*sizeof(int));
	printV(v, size);

	mergesort(v, size, [] (int a, int b) {return a>b;});
	printV(v, size);
	mergesort(v, size);
	printV(v, size);

	cout << "\ninplace:\n";
	memcpy(v,v2,size*sizeof(int));
	mergesortInPlace(v, size, [] (int a, int b) {return a>b;});
	printV(v,size);

	memcpy(v,v2,size*sizeof(int));
	mergesortInPlace(v, size);
	printV(v,size);
	return 0;
}

#endif

#endif

/*
Quicksort:

Worst case: n^2 	-> When pivot lands on edge elements, and the division of work doesn’t divide much
Best case: nlogn	-> Pivot on the middle
average case: nlogn	-> On random data it tends to work really well
stable:				-> No

Description:
 It selects a pivot, at position 0 or random (on this code both are implemented), then it
iterates through the vector swapping elements, until it gets a boundary where all the less or equal 
elements than the pivot are on the left side of the pivot, and the greater elements are left on 
the right side.
 Then a swap puts the pivot on the correct sorting place, and recursively calls itself on the left 
 and right side of the pivot. Until the vector is sorted.

**** It makes the sorting in place. ****
*/

#ifndef QUICKSORT
#define QUICKSORT

#define SWAP(a,b,swap_tmp) ({swap_tmp=a; a=b; b=swap_tmp;})

#include <cstdlib>
#include <ctime>

// STATIC PIVOT SELECTION AT 0
template <typename T, typename Func>
void quicksort(T *v, int size, Func eval) {
	__quicksort_tail_recursion:
	// Base case
	if (size <= 1) return;

	int pivot = 0, front;
	T swap_tmp;
	
	// We set front to a proper place, without swapping unnecessary
	for (front=1; front<size; front++)
		if (eval(v[pivot], v[front]))
			break;

	// We iterate through the vector, keeping front left-most element of the right side (greather than the pivot)
	for (int i=front+1; i<size; i++) {
		if (eval(v[i], v[pivot])) {
			SWAP(v[i], v[front], swap_tmp);
			front++;
		}
	}

	// We swap pivot to the corresponding index on the sorted array
	SWAP(v[pivot], v[front-1], swap_tmp);

	// Recursively call on left and right sides
	// quicksort(&v[0], front-1, eval);
	// quicksort(&v[front], size-front, eval);

	// tail recursion call optimization to avoid stack overflow
	if (size-front <= 1) {
		size = front-1;
		goto __quicksort_tail_recursion;
	}
	else if (front-1>1)
		quicksort(&v[0], front-1, eval);

	// tail recursion call optimization
	v = &v[front];
	size -= front;
	goto __quicksort_tail_recursion;
}

// Default order set on ascending
template <typename T>
void quicksort(T *v, int size) {
	quicksort(v, size, [](T a, T b){ return a<b;});
}

// RANDOM PIVOT SELECTION
template <typename T, typename Func>
void _quicksortRandomPivot(T *v, int size, Func eval) {
	__quicksortRandomPivot_Tail_recursion_call:
	// Base case
	if (size <= 1) return;

	// We select a random pivot between the size bound.
	int pivot = rand()%size, front;
	T swap_tmp;
	
	// We swap the pivot to position 0
	SWAP(v[0], v[pivot], swap_tmp);
	pivot = 0;

	// We set front to a proper place, without swapping unnecessary
	for (front=1; front<size; front++)
		if (eval(v[pivot], v[front]))
			break;

	// We iterate through the vector, keeping front left-most element of the right side (greather than the pivot)
	for (int i=front+1; i<size; i++) {
		if (eval(v[i], v[pivot])) {
			SWAP(v[i], v[front], swap_tmp);
			front++;
		}
	}

	// We swap pivot to the corresponding index on the sorted array
	SWAP(v[pivot], v[front-1], swap_tmp);

	// Recursively call on left and right sides
	_quicksortRandomPivot(&v[0], front-1, eval);
	// _quicksortRandomPivot(&v[front], size-front, eval);

	// tail recursion call
	v += front;
	size -= front;
	goto __quicksortRandomPivot_Tail_recursion_call;
}

// Drive function for seting the seed needed in rand function
template <typename T, typename Func>
void quicksortRandomPivot(T *v, int size, Func eval) {
	srand(time(0));
	_quicksortRandomPivot(v,size,eval);
}

// Default order set on ascending
template <typename T>
void quicksortRandomPivot(T *v, int size) {
	quicksortRandomPivot(v, size, [](T a, T b){ return a<b;});
}


#ifndef VECTOR_TEST
// Testing
#include <iostream>

#include "vector_utility.cpp"

using namespace std;

int main() {
	int size=100;
	int v[size];

	initRandomV(v, size, size, 0);
	printV(v, size);

	quicksort(v, size, [] (int a, int b) {return a>b;});
	printV(v, size);
	quicksort(v, size);
	printV(v, size);
	return 0;
}

#endif

#endif

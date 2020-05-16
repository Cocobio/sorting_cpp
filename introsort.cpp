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
#ifndef INTROSORT
#define INTROSORT

#define SWAP(a,b,swap_tmp) ({swap_tmp=a; a=b; b=swap_tmp;})

#include <cstdlib>
#include <ctime>
#include <cmath>

#ifndef VECTOR_TEST
#define VECTOR_TEST
#include "quicksort.cpp"
#include "heapsort.cpp"
#include "insertionsort.cpp"
#else
#include "quicksort.cpp"
#include "heapsort.cpp"
#include "insertionsort.cpp"
#endif

// RANDOM PIVOT SELECTION
template <typename T, typename Func>
void _introsort(T *v, int size, Func eval, int depth) {
	__introsort_Tail_Recursion_Call:
	// Base case
	if (size <= 15) {
		insertionsort(v,size,eval);
		return;
	}

	if (depth == 0) {
		heapsort(v,size,eval);
		return;
	}

	depth -= 1;

	// Random selection and reuse of partition with static selection
	T swap_tmp;
	SWAP(v[0], v[rand()%size], swap_tmp);
	
	int pivot = partition(v, size, eval);

	// tail recursion call optimization to avoid stack overflow
	if (size-pivot <= 2) {
		size = pivot;
		goto __introsort_Tail_Recursion_Call;
	}
	else if (pivot>1)
		_introsort(v, pivot, eval, depth);

	// tail recursion call optimization
	v = &v[pivot+1];
	size -= pivot+1;
	goto __introsort_Tail_Recursion_Call;
}

// Drive function for seting the seed needed in rand function
template <typename T, typename Func>
void introsort(T *v, int size, Func eval) {
	srand(time(0));
	int depth = 2*log(size);
	_introsort(v,size,eval, depth);
}

// Default order set on ascending
template <typename T>
void introsort(T *v, int size) {
	introsort(v, size, [](T a, T b){ return a<b;});
}


#ifndef VECTOR_TEST
// Testing
#include <iostream>

#include "vector_utility.cpp"

using namespace std;

int main() {
	int size=200000;
	int v[size];

	initRandomV(v, size, size, 0);
	// printV(v, size);

	introsort(v, size, [] (int a, int b) {return a>b;});
	cout << checkSorting(v,size, [](int a, int b) {return a>b;}) << endl;
	// printV(v, size);
	introsort(v, size);
	// printV(v, size);

	cout << checkSorting(v, size) << endl;
	return 0;
}

#endif

#endif

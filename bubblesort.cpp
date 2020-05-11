/*
Bubblesort:

Worst case: n^2 	-> It runs n^2 comparisons, if the array is sorted before n^2 iterations it will stop
Best case: n		-> When the vector is already sorted the n_swaps variable will stop the algorithm
average case: n^2	-> 
stable:				-> Yes

Description:
 It runs n^2 times on the vector, checking whether the element i and i+1 fulfils the evaluator,
if otherwise, it swaps them.

**** Similar to selectionsort and insertionsort, but with worst constant factor ****
*/

#ifndef BUBBLESORT
#define BUBBLESORT

#define SWAP(a,b, swap_tmp) ({swap_tmp=a; a=b; b=swap_tmp;})

template <typename T, typename Func>
void bubblesort(T *v, int size, Func eval) {
	int n_swaps;
	T swap_tmp;

	// it iterates n times
	for (int i=0; i<size; i++) {
		n_swaps = 0;

		// for each i iteration, it iterates another n times
		for (int j=0; j<size-1; j++)
			if (eval(v[j+1], v[j])) {
				SWAP(v[j], v[j+1], swap_tmp);
				n_swaps++;
			}

		// When the vector is sorted, then no swap would have been made, this stops the algorithm
		if (n_swaps==0) break;
	}
}

// Default order set on ascending
template <typename T>
void bubblesort(T *v, int size) {
	bubblesort(v, size, [] (T a, T b) {return a<b;});
}


#ifndef VECTOR_TEST
// Testing
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "vector_utility.cpp"

using namespace std;

int main() {
	srand(time(0));
	int size=50;
	int v[size];

	initRandomV(v, size, (int)size, (int)0.0);
	printV(v, size);

	bubblesort(v, size, [] (int a, int b){ return a>b; });
	printV(v, size);
	bubblesort(v, size);
	printV(v, size);
	return 0;
}

#endif

#endif

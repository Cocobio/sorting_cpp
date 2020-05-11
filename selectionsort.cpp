/*
Selectionsort:

Worst case: n^2 	-> It will iterate the same way independent of the input data, but it will swap more if v is sorted inverted
Best case: n^2		-> 
average case: n^2	-> 
stable:				-> No

Description:
 It starts from the left, increasing the sorted part of the vector by 1 on each loop of i.
 It iterates through and finds the min (or max, depending on evaluator) element and swaps it to
the end of the sorted parted. Then it increments the sorted part size by 1.

*/

#ifndef SELECTIONSORT
#define SELECTIONSORT

#define SWAP(a,b,swap_tmp) ({swap_tmp=a; a=b; b=swap_tmp;})

template <typename T, typename Func>
void selectionsort(T *v, int size, Func eval) {
	int index;
	T swap_tmp;

	// Each iteration sets a sorted value on i
	for (int i=0; i<size; i++) {
		index=i;

		// This loop finds the element that satisfies the evaluator for all the unsorted elements
		for (int j=i+1; j<size; j++)
			if (eval(v[j], v[index]))
				index=j;

		// We swap the lower (or greather) element to the sorted part of the vector
		SWAP(v[i], v[index], swap_tmp);
	}
}

// Default order set on ascending
template <typename T>
void selectionsort(T *v, int size) {
	selectionsort(v, size, [] (T a, T b) { return a<b; });
}


#ifndef VECTOR_TEST
// Testing
#include <iostream>
#include <ctime>
#include "vector_utility.cpp"

#include "vector_utility.cpp"

using namespace std;

int main() {
	int size=50;
	int *v = (int*) malloc(size*sizeof(int));

	initRandomV(v, size, size, 0);
	printV(v, size);

	selectionsort(v, size, [] (int a, int b) {return a>b;});
	printV(v, size);
	selectionsort(v, size);
	printV(v, size);
	return 0;
}

#endif

#endif

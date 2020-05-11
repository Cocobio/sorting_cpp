/*
Insertionsort:

Worst case: n^2 	-> If the vector is sorted inverted, it will take n(n+1)/2 iterations, yielding n^2 complexity
Best case: n		-> If vector already sorted, then it takes n comparisons
average case: n^2	-> 
stable:				-> Yes

Description:
 Similar to selectionsort, it starts by assuming the left sided already sorted, then it takes a new
element from the right side (the most left one) and inserts it to the corresponding index on the left
side, doing h swaps (h = distance from index to boundary for left and right sides)

*/

#ifndef INSERTIONSORT
#define INSERTIONSORT

template <typename T, typename Func>
void insertionsort(T *v, int size, Func eval) {
	T tmp;

	// Each iteration sets an element on a sorted vector located on the left side of v
	for (int s=1, j; s<size; s++) {
		// By saving the element on a tmp var the insertion is made faster
		tmp = v[s];

		// We will move all the elements to the right, until we reach the begining or we find a element that doesn't satisfy the evaluator 
		for (j=s; j>0 && eval(tmp, v[j-1]); j--)
			v[j] = v[j-1];

		// The element is set on the sorted index		
		v[j] = tmp;
	}
}

// Default order set on ascending
template <typename T>
void insertionsort(T *v, int size) {
	insertionsort(v, size, [] (T a, T b) { return a<b; });
}

#ifndef VECTOR_TEST

// Testing
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "vector_utility.cpp"

using namespace std;

int main() {
	int size=50;
	int *v = (int*)malloc(size*sizeof(int));

	initRandomV(v, size, size, 0);
	printV(v, size);

	insertionsort(v, size, [] (int a, int b) {return a>b;});
	printV(v, size);
	insertionsort(v, size);
	printV(v, size);
	return 0;
}

#endif

#endif

/*
Heapsort:

Worst case: nlogn 	-> Read description
Best case: nlogn	-> 
average case: nlogn	-> 
stable:				-> No

Description:
 First, it represents the vector as a not full balance binary tree. Using element 0 as root, and
2*ith and 2*i+1th elements as the child. Then it creates a max (or min, depending on evaluator) heap
(which is o(n), not trivially explained). And Runs n time extracting the max (or min) value, which
is done in constant time. Then the heap is heapify, which is o(logn).

**** It uses constant memory space and pays an extra o(n) for create the heap ****

*/

#ifndef HEAPSORT
#define HEAPSORT

#define SWAP(a,b,swap_tmp) ({swap_tmp=a; a=b; b=swap_tmp;})

// Maintenance property of heap, assuming that childs of node are max (or min) heaps
template <typename T, typename Func>
void heapify(T *heap, int i, int size, Func eval) {
	// We identify the node and the children
	int root = i;
	int lc = 2*i+1;
	int rc = 2*i+2;


	// We select the node that preserves the max (or min) property of the heap
	if (lc<size && eval(heap[root], heap[lc])) root = lc;
	if (rc<size && eval(heap[root], heap[rc])) root = rc;

	// If we have to make a swap, we recursively call heapify to maintain the property on swapped child
	if (root != i) {
		T swap_tmp;
		SWAP(heap[root], heap[i], swap_tmp);
		heapify(heap, root, size, eval);
	}
}

template <typename T, typename Func>
void heapsort(T *v, int size, Func eval) {
	// Creates max (or min) heap
	for (int i=size/2-1; i>=0; i--)
		heapify(v, i, size, eval);

	T swap_tmp;
	
	// Iteratively extract max or min, and heapify on root the heap, with size-1
	while (--size>0) {
		SWAP(v[0], v[size], swap_tmp);
		heapify(v, 0, size, eval);;
	}
}

// Default order set on ascending
template <typename T>
void heapsort(T *v, int size) {
	heapsort(v, size, [] (T a, T b) { return a<b; });
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

	heapsort(v, size, [] (int a, int b) {return a>b;});
	printV(v, size);
	heapsort(v, size);
	printV(v, size);
	return 0;
}

#endif

#endif

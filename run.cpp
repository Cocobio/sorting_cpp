#define VECTOR_TEST

#include <iostream>
#include <string>
#include <vector>
#include "vector_utility.cpp"

#include "quicksort.cpp"
#include "mergesort.cpp"
#include "heapsort.cpp"
#include "bubblesort.cpp"
#include "selectionsort.cpp"
#include "insertionsort.cpp"

// testing
#include "introsort.cpp"

using namespace std;

typedef int data_type;

int main() {
	//// List of algorithms
	vector<void (*)(data_type*,int)> sortingFuncs;
	vector<string> f_names;

	sortingFuncs.push_back(quicksort);
	f_names.push_back("quicksort");

	sortingFuncs.push_back(quicksortRandomPivot);
	f_names.push_back("quicksortRandomPivot");
	
	f_names.push_back("mergesort");
	sortingFuncs.push_back(mergesort);
	
	f_names.push_back("mergesortInPlace");
	sortingFuncs.push_back(mergesortInPlace);

	f_names.push_back("heapsort");
	sortingFuncs.push_back(heapsort);

	sortingFuncs.push_back(bubblesort);
	f_names.push_back("bubblesort");

	sortingFuncs.push_back(selectionsort);
	f_names.push_back("selectionsort");

	sortingFuncs.push_back(insertionsort);
	f_names.push_back("insertionsort");

	sortingFuncs.push_back(introsort);
	f_names.push_back("introsort");

	// input and output data files
	string input, output;

	cout << "This programs will assume integer arrays." << endl;

	cout << "Input file: ";
	cin >> input;
	cout << "Output file: ";
	cin >> output;

	int option;

	cout << "Algorithm list:" << endl;
	for (int i=0; i<f_names.size(); i++) {
		cout << i << ":\t" << f_names[i] << endl;
	}

	cout << "Select Algorithm: ";
	cin >> option;

	if (option<0 || option>=f_names.size()) {
		cout << "Option out of bound." << endl;
		return -1;
	}

	int size;
	data_type *v;
	v = readVectorFromFile<data_type>(&size, input);
	double t = measureTimeOf(sortingFuncs[option], v, size);
	cout << f_names[option] << " in " << t << "sec for " << size << " elements." << endl;
	writeFileWithVector(v, size, output, ""); 

	return 0;
}
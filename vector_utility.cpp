#ifndef VECTOR_UTILITY
#define VECTOR_UTILITY

#include <string>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <ctime>

using namespace std;

// Binary file writer from a vector
template <typename T>
void writeFileWithVector(T* v, int size, string name, string folder) {
	//we output the data into a binary file
	ofstream output;

	// we open a binary file (if it exists it overwrites it)
	// we write 4 bytes with a int saving the size of the vector
	// and then we write the vector
	output.open(folder+name, ios::binary | ios::out | ios::trunc);
	output.write((char*)&size, sizeof(int));
	output.write((char*)v, size*sizeof(T));
		
	// we close the file
	output.close();
}

// Binary file reader from a vector
template <typename T>
T* readVectorFromFile(int *size, string file) {
	ifstream input;
	T *v;

	input.open(file, ios::binary | ios::in);
	input.read((char*)size, sizeof(int));
		
	v = (T*) malloc((*size)*sizeof(T));

	input.read((char*)v, (*size)*sizeof(T));
	input.close();

	return v;
}

// Utility function for testing
template <typename T, typename Func>
int checkSorting(T *v, int size, Func eval) {
	for (int i=0; i<size-1; i++)
		if (eval(v[i+1], v[i]))			
			return -1;
	return 0;
}

template <typename T>
int checkSorting(T *v, int size) {
	for (int i=0; i<size-1; i++)
		if (v[i] > v[i+1])			
			return -1;
	return 0;
}

template <typename T>
void shuffle(T *v, int size) {
	T tmp;
	int rand_i;
	
	for (int i=0; i<size; i++) {
		tmp = v[i];
		rand_i = rand()%(size-i)+i;
		
		v[i] = v[rand_i];
		v[rand_i] = tmp;
	}
}

// Random vector initializer
template <typename T>
void initRandomV(T *v, int size, T range, T offset) {
	for (int i=0; i<size; i++)
		v[i] = ((float) rand())/RAND_MAX*range + offset;
}

template <typename T>
void initSortedV(T *v, int size, T range, T offset) {
	float step = (float)range/size;
	for (int i=0; i<size; i++)
		v[i] = step*i+offset;
}

template <typename T>
void initRandomVWithUniqueValues(T *v, int size, T range, T offset) {
	float step = (float)range/size;

	for (int i=0; i<size; i++)
		v[i] = step*i+offset;

	shuffle(v, size);
}

// Utility function for printing a vector
template <typename T>
void printV(T *v, int size) {
	cout << "v = { ";
	for (int i=0; i<size; i++)
		cout << v[i] << " ";
	cout << "}\n";
}

// Sort a bin file to a bin file
// Function with evaluator
template <typename T, typename Func>
void sortBinFileToBinFile(string input_file, string output_file, void (*s)(T*,int,Func), Func eval) {
	int size;
	T *v;
	v = readVectorFromFile<T>(&size, input_file);
	s(v, size, eval);
	writeFileWithVector(v, size, output_file, ""); 
}

// Function with default evaluator
template <typename T>
void sortBinFileToBinFile(string input_file, string output_file, void (*s)(T*,int)) {
	// sortBinFileToBinFile<T>(input_file, output_file, s, [](T a, T b) { return a<b; });
	int size;
	T *v;
	v = readVectorFromFile<T>(&size, input_file);
	s(v, size);
	writeFileWithVector(v, size, output_file, ""); 
}

// ----------------------------------------------
// time measure functions
template <typename T>
double measureTimeOf(void s (T*,int), T *v, int size) {
	clock_t t; 
	t = clock(); 
	s(v, size);
	t = clock() - t; 

	return ((double)t)/CLOCKS_PER_SEC; // in seconds 
}

// this one is for sorting that uses pointers to the begin and end of what has to be sorted 
template <typename T>
double measureTimeOf(void s (T*,T*), T *b, T *e) {
	clock_t t; 
	t = clock(); 
	s(b, e);
	t = clock() - t; 

	return ((double)t)/CLOCKS_PER_SEC; // in seconds 
}

// This one is for sorting using a evaluator
template <typename T, typename Func>
double measureTimeOf(void s (T*,int,Func), T *v, int size, Func eval) {
	clock_t t; 
	t = clock(); 
	s(v, size, eval);
	t = clock() - t; 
	double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
	return time_taken;
}

#endif

#define VECTOR_TEST

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
// #include <chrono>


#include "quicksort.cpp"
#include "mergesort.cpp"
#include "bubblesort.cpp"
#include "heapsort.cpp"
#include "insertionsort.cpp"
#include "selectionsort.cpp"
#include <algorithm>

#include "vector_utility.cpp"

#include <sstream>
#include <iomanip>

using namespace std;

// This part only works for windows, I didn't searched for linux and mac variations
#ifdef WIN32

#include <Windows.h>
// Inspecting folder for a list of all files
vector<string> getFileListWithinFolder(std::string folder) {
    vector<string> names;
    string search_path = folder + "/*.*";
    WIN32_FIND_DATA fd; 
    HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd); 
    if(hFind != INVALID_HANDLE_VALUE) { 
        do { 
            // read all (real) files in current folder
            // , delete '!' read other 2 default folder . and ..
            if(! (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) ) {
                names.push_back(folder+"/"+fd.cFileName);
            }
        }while(::FindNextFile(hFind, &fd)); 
        ::FindClose(hFind); 
    }
    return names;
}

#endif

// Function for creating data with a size and size_step
void create_data_set() {
	int n = 10000000;
	int step = 10000;
	string name;
	string folder;
	void *v;

	int a=23;
	int size_v[] = {100,500,1000,2000,3000,4000,5000,10000,20000,30000,40000,50000,100000,200000,300000,400000,500000,1000000,2000000,3000000,4000000,5000000,10000000};

	name = "intV_";
	folder = "Datasets/vectorInt random With Unique Values/";
	// for (int size=step; size<=n; size+=step) {
	// 	std::stringstream ss;
	// 	ss << std::setw(8) << std::setfill('0') << size;

	// 	v = malloc(size*sizeof(int)); 
	// 	initRandomV((int*)v, size, size, 0);
	// 	writeFileWithVector<int>((int*)v, size, name+ss.str()+".bin", folder);
	// 	free(v);
	// }
	for (int i=0; i<23; i++) {
		std::stringstream ss;
		ss << std::setw(8) << std::setfill('0') << size_v[i];

		v = malloc(size_v[i]*sizeof(int)); 
		// initRandomV((int*)v, size_v[i], size_v[i], 0);
		// initSortedV((int*)v, size_v[i], size_v[i], 0);
		initRandomVWithUniqueValues((int*)v, size_v[i], size_v[i], 0);
		writeFileWithVector<int>((int*)v, size_v[i], name+ss.str()+".bin", folder);
		free(v);
	}

	// name = "floatV_";
	// folder = "Datasets/vectorFloat/";
	// for (int size=step; size<=n; size+=step) {
	// 	v = malloc(size*sizeof(float));
	// 	initRandomV((float*)v, size, (float)1000.0, (float)0.0);
	// 	if (size==step) printV((float*)v,size);
	// 	writeFileWithVector<float>((float*)v, size, name+to_string(size)+".bin", folder);
	// 	free(v);
	// }

	// name = "doubleV_";
	// folder = "Datasets/vectorDouble/";
	// for (int size=step; size<=n; size+=step) {
	// 	v = malloc(size*sizeof(double));
	// 	initRandomV((double*)v, size, (double)1000.0, (double)0.0);
	// 	writeFileWithVector<double>((double*)v, size, name+to_string(size)+".bin", folder);	
	// 	free(v);
	// }
}

// Function for runing all the implemented sorts with all the differents data created inside folder
template <typename T>
void runTVectorTests(string folder) {
	// We define the vector variables
	T *v, *v_tmp;
	int size;
	double t;
	
	// list of sorting functions
	vector<void (*)(T*,int)> sortingFuncs;
	vector<string> f_names;

	//// uncomment for sorting integer vectors created by create_data_set
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

	sortingFuncs.push_back(insertionsort);
	f_names.push_back("insertionsort");

	sortingFuncs.push_back(selectionsort);
	f_names.push_back("selectionsort");
	//

	// we search the file list for the datasets and iterate over them
	vector<string> files = getFileListWithinFolder(folder);
	cout.precision(6);

	for (vector<string>::iterator i = files.begin(); i<files.end(); i++) {
		cout << "Reading file: " << *i << endl;
		
		// We read the file as vector and return it
		v = readVectorFromFile<T>(&size, *i);
		v_tmp = (T*) malloc(size*sizeof(T));

		// cout << "checkSorting input: " << checkSorting(v,size) << endl;

		for (int j=0; j<f_names.size(); j++) {
			// we copie v into the temporal vector, so we can run all the sortings with the same vector
			memcpy(v_tmp, v, size*sizeof(T));

			// we measure the time
			t = measureTimeOf(sortingFuncs[j], v_tmp, size);
			cout << f_names[j] << " in " << t << "sec for " << size << " elements." << endl;

			if (checkSorting(v_tmp,size)) cout << "Error en " << f_names[j] << " sorting\n";
		}

		memcpy(v_tmp, v, size*sizeof(T));

		// we measure the time of std::sort
		double t = measureTimeOf(std::sort, v_tmp, v_tmp+size);
		cout << "std::sort in " << t << "sec " << endl;
		
		// we free de memory that the vector and temporal vector were using
		free(v);
		free(v_tmp);
	}
}

template <typename T>
void runTVectorTestsWriteDataTo(void (*s)(T*,int), string folder, string output_file) {
	// We define the vector variables
	T *v, *v_tmp;
	int size;
	double t;
	int n = 10;
	float t_avr;	

	// we search the file list for the datasets and iterate over them
	vector<string> files = getFileListWithinFolder(folder);
	cout.precision(6);

	ofstream output;

		
	// we close the file

	for (vector<string>::iterator i = files.begin(); i<files.end()-9; i++) {
	output.open(output_file, ios::out | ios::app);
		t_avr = 0;
		cout << "Reading file: " << *i << endl;
		
		// We read the file as vector and return it
		v = readVectorFromFile<T>(&size, *i);
		v_tmp = (T*) malloc(size*sizeof(T));

		// cout << "checkSorting input: " << checkSorting(v,size) << endl;

		for (int j=0; j<n; j++) {
			// we copie v into the temporal vector, so we can run all the sortings with the same vector
			memcpy(v_tmp, v, size*sizeof(T));

			// we measure the time
			t = measureTimeOf(s, v_tmp, size);
			// cout << f_names[j] << " in " << t << "sec for " << size << " elements." << endl;
			if (checkSorting(v_tmp,size)) cout << "Error in sorting\n";
			t_avr += t/n;

		}

		memcpy(v_tmp, v, size*sizeof(T));
		output << t_avr << ";";
		output.close();

		// we free de memory that the vector and temporal vector were using
		free(v);
		free(v_tmp);
	}

	output.close();
}

template <typename T>
void runTVectorTestsWriteDataTo(void (*s)(T*,T*), string folder, string output_file) {
	// We define the vector variables
	T *v, *v_tmp;
	int size;
	double t;
	int n = 10;
	float t_avr;	

	// we search the file list for the datasets and iterate over them
	vector<string> files = getFileListWithinFolder(folder);
	cout.precision(6);

	ofstream output;

	output.open(output_file, ios::out | ios::trunc);
		
	// we close the file

	for (vector<string>::iterator i = files.begin(); i<files.end(); i++) {
		t_avr = 0;
		cout << "Reading file: " << *i << endl;
		
		// We read the file as vector and return it
		v = readVectorFromFile<T>(&size, *i);
		v_tmp = (T*) malloc(size*sizeof(T));

		// cout << "checkSorting input: " << checkSorting(v,size) << endl;

		for (int j=0; j<n; j++) {
			// we copie v into the temporal vector, so we can run all the sortings with the same vector
			memcpy(v_tmp, v, size*sizeof(T));

			// we measure the time
			t = measureTimeOf(s, v_tmp, v_tmp+size);
			// cout << f_names[j] << " in " << t << "sec for " << size << " elements." << endl;
			if (checkSorting(v_tmp,size)) cout << "Error in sorting\n";
			t_avr += t/n;

		}

		memcpy(v_tmp, v, size*sizeof(T));
		output << t_avr << ";";

		// we free de memory that the vector and temporal vector were using
		free(v);
		free(v_tmp);
	}

	output.close();
}


int main() {
	srand(time(0));											// I dont know were to put this one, but its needed for the quicksortRandomPivot and create data sets
	// create_data_set();										// uncomment for creating data


	// runTVectorTests<int>("Datasets/vectorInt");			// uncomment for sorting integer vectors created by create_data_set
	// runTVectorTests<float>("Datasets/vectorFloat/");		// uncomment for sorting floating points vectors created by create_data_set
	// runTVectorTests<double>("Datasets/vectorDouble/");		// uncomment for sorting floating points with double precision vectors created by create_data_set


	// // This section is for sorting specific files with a specific sorting, and write the result into a file
	// typedef float data_type;										// Must match vector type for the input file

	// string input_file = "Datasets/vectorFloat/floatV_100.bin";
	// string output_file = "Datasets/vectorFloat/Sorted/floatV_100.bin";
	// auto eval = [] (data_type a, data_type b) { return a<b; };		// for ascending order
	// // auto eval = [] (data_type a, data_type b) { return a>b; };		// for descending order

	// sortBinFileToBinFile<data_type>(input_file, output_file, quicksort, eval);

	// int size;
	// data_type * v = readVectorFromFile<data_type>(&size, output_file);

	// if (!checkSorting(v, size, eval)) cout << "Correct sorted order" << endl;
	// else cout << "Incorrect sorted order" << endl;

	/*
	SORTINGS:
	quicksort
	quicksortRandomPivot
	mergesort
	mergesortInPlace
	heapsort
	bubblesort
	insertionsort
	selectionsort
	std::sort
	*/

	vector<void (*)(int*,int)> sortingFuncs;
	vector<string> f_names;

	// uncomment for sorting integer vectors created by create_data_set
	sortingFuncs.push_back(quicksort);
	f_names.push_back("quicksort");

	// sortingFuncs.push_back(quicksortRandomPivot);
	// f_names.push_back("quicksortRandomPivot");
	
	// f_names.push_back("mergesort");
	// sortingFuncs.push_back(mergesort);
	
	// f_names.push_back("mergesortInPlace");
	// sortingFuncs.push_back(mergesortInPlace);

	// f_names.push_back("heapsort");
	// sortingFuncs.push_back(heapsort);

	// sortingFuncs.push_back(bubblesort);
	// f_names.push_back("bubblesort");

	// sortingFuncs.push_back(insertionsort);
	// f_names.push_back("insertionsort");

	// sortingFuncs.push_back(selectionsort);
	// f_names.push_back("selectionsort");

	for (int i=0; i<sortingFuncs.size(); i++) {
		// runTVectorTestsWriteDataTo<int>(sortingFuncs[i], "Datasets/vectorInt", "Datasets/vectorInt/Sorted/"+f_names[i]+".txt");
		// runTVectorTestsWriteDataTo<int>(sortingFuncs[i], "Datasets/vectorInt random With Unique Values", "Datasets/vectorInt random With Unique Values/Sorted/"+f_names[i]+".txt");
		runTVectorTestsWriteDataTo<int>(sortingFuncs[i], "Datasets/vectorInt sorted", "Datasets/vectorInt sorted/Sorted/"+f_names[i]+".txt");
	}

	// runTVectorTestsWriteDataTo<int>(std::sort, "Datasets/vectorInt", "Datasets/vectorInt/Sorted/std_sort.txt");
	// runTVectorTestsWriteDataTo<int>(std::sort, "Datasets/vectorInt random With Unique Values", "Datasets/vectorInt random With Unique Values/Sorted/std_sort.txt");
	// runTVectorTestsWriteDataTo<int>(std::sort, "Datasets/vectorInt sorted", "Datasets/vectorInt sorted/Sorted/std_sort.txt");


	// // Single test
	// int *v;
	// int size;
	// v = readVectorFromFile<int>(&size, "Datasets/vectorInt/intV_10000000.bin");
	// double t = measureTimeOf(quicksort, v, size);
	// cout << "quicksort in " << t << "sec for " << size << " elements." << endl;

	return 0;
}


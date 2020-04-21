// Homework 4
// Testing Sorting Algorithms
// YOUR NAME

#include "Sort.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <vector>
using namespace std;

// Test function that shows how you can time a piece of code.
// Just times a simple loop.

void TestTiming() {
  cout << "Test Timing" << endl;
  const auto begin = chrono::high_resolution_clock::now();
  // Time this piece of code.
  int sum = 0;
  for (int i = 1; i < 10000; ++i) sum ++;
  // End of piece of code to time.
  const auto end = chrono::high_resolution_clock::now();
  cout << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << "ns" << endl;
  cout << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << "ms" << endl;

}

// Generates and returns random vector of size @size_of_vector.
vector<int> GenerateRandomVector(size_t size_of_vector) {
  vector<int> random_nums_vector;
  for (int i=0; i<size_of_vector-1; i++) {
     random_nums_vector.push_back(rand());
  }

  return random_nums_vector;

}//end GenerateRandomVector


// Generate and returns sorted vecotr of size @size_of_vector
// If smaller_to_larger is true, returns vector sorted from small to large
// Otherwise returns vector sorted from large to small
vector<int> GenerateSortedVector(size_t size_of_vector, bool smaller_to_larger) {
   vector<int> sorted_vector;

   if (smaller_to_larger) {
      for (int i=0; i<size_of_vector-1; i++) {
         sorted_vector.push_back(i);
      }
   }

   else {
      for (int i=size_of_vector-1; i>=0; i--) {
         sorted_vector.push_back(i);
      }
   }
   return sorted_vector;
}//end GenerateSortedVector

// Verifies that a vector is sorted given a comparator
template <typename Comparable, typename Comparator>
bool VerifyOrder(const vector<Comparable> &input, Comparator less_than) {

   for (size_t i=0; i<input.size()-1; i++)   // go over each element of the vector
   {
      if(!less_than(input[i],input[i+1])) //if this fails, return false
         return false;
   }

   return true; //if the whole loop went through, the vector is ordered correctly
}

// Computes duration given a start time and a stop time in nano seconds
long long ComputeDuration(chrono::high_resolution_clock::time_point start_time, chrono::high_resolution_clock::time_point end_time) {

   const auto begin = start_time;
   const auto end = end_time;

   long long duration_computed = chrono::duration_cast<chrono::nanoseconds>(end - begin).count();

   return duration_computed;
}

// Wrapper function to test different sorting algorithms
void sortTestingWrapper(int argc, char **argv) {
  const string input_type = string(argv[1]);
  const int input_size = stoi(string(argv[2]));
  const string comparison_type = string(argv[3]);

  if (input_type != "random" && input_type != "sorted_small_to_large" && input_type != "sorted_large_to_small") {
    cout << "Invalid input type" << endl;
    //return 0;
  }
  if (input_size <= 0) {
    cout << "Invalid size" << endl;
    //return 0;
  }
  if (comparison_type != "less" && comparison_type != "greater") {
    cout << "Invalid comparison type" << endl;
    //return 0;
  }

  // This block of code to be removed for your final submission.
  //TestTiming();

  cout << "Running sorting algorithms: " << input_type << " " << input_size << " numbers " << comparison_type << endl;
  vector<int> input_vector;
  if (input_type == "random") {
    // Generate random vector

  } else {
    // Generate sorted vector.

  }

  // Call quicksort / heapsort / mergesort using appropriate input.
  // ...
  // if comparison type is "less" then call
  // MergeSort(input_vector, less<int>{})
  // otherwise call
  // MergeSort(input_vector, greater<int>{})
  // ...

  // Call quicksort with median of three as pivot / middle as pivot / first as pivot using appropriate input.
  // ...
  // if comparison type is "less" then call
  // QuickSort(input_vector, less<int>{})
  // otherwise call
  // QuickSort(input_vector, greater<int>{})
  // ...

}

int main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Usage: " << argv[0] << "<input_type> <input_size> <comparison_type>" << endl;
    return 0;
  }

  sortTestingWrapper(argc, argv);

  return 0;
}

// Homework 4
// Testing Sorting Algorithms
// Tal Bachar

#include "Sort.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <vector>
using namespace std;


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
      for (int i=0; i<size_of_vector; i++) {
         sorted_vector.push_back(i);
      }
   }

   else {
      for (int i=size_of_vector; i>=0; i--) {
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
auto ComputeDuration(chrono::high_resolution_clock::time_point start_time,
                           chrono::high_resolution_clock::time_point end_time) {

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


  cout << "Running sorting algorithms: " << input_type << " " << input_size << " numbers " << comparison_type << endl;
  if (input_type == "random") {
       vector<int> input_vector = GenerateRandomVector(input_size);
       vector<int> input_vector1 = input_vector;
       vector<int> input_vector2 = input_vector;

       if (comparison_type == "less") {
         //HEAP
         const auto begin = chrono::high_resolution_clock::now();
         HeapSort(input_vector, less<int>{});
         const auto end = chrono::high_resolution_clock::now();
         cout << "Heapsort" << "\n\n" <<  "Runtime: " << ComputeDuration(begin, end) << " ns" << endl;
         cout << "Verified: " << VerifyOrder(input_vector, less<int>{}) << "\n\n";
         //MERGE
         const auto begin1 = chrono::high_resolution_clock::now();
         MergeSort(input_vector1, less<int>{});
         const auto end1 = chrono::high_resolution_clock::now();
         cout << "MergeSort" << "\n\n" <<  "Runtime: " << ComputeDuration(begin1, end1) << " ns" << endl;
         cout << "Verified: " << VerifyOrder(input_vector1, less<int>{}) << "\n\n";
         //QUICK
         const auto begin2 = chrono::high_resolution_clock::now();
         QuickSort(input_vector2, less<int>{});
         const auto end2 = chrono::high_resolution_clock::now();
         cout << "QuickSort" << "\n\n" <<  "Runtime: " << ComputeDuration(begin2, end2) << " ns" << endl;
         cout << "Verified: " << VerifyOrder(input_vector2, less<int>{}) << "\n\n";

      }
      if (comparison_type == "greater") {
         //HEAP
         const auto begin = chrono::high_resolution_clock::now();
         HeapSort(input_vector, greater<int>{});
         const auto end = chrono::high_resolution_clock::now();
         cout << "Heapsort" << "\n\n" <<  "Runtime: " << ComputeDuration(begin, end) << " ns" << endl;
         cout << "Verified: " << VerifyOrder(input_vector, greater<int>{}) << "\n\n";
         //MERGE
         const auto begin1 = chrono::high_resolution_clock::now();
         MergeSort(input_vector1, greater<int>{});
         const auto end1 = chrono::high_resolution_clock::now();
         cout << "MergeSort" << "\n\n" <<  "Runtime: " << ComputeDuration(begin1, end1) << " ns" << endl;
         cout << "Verified: " << VerifyOrder(input_vector1, greater<int>{}) << "\n\n";
         //QUICK
         const auto begin2 = chrono::high_resolution_clock::now();
         QuickSort(input_vector2, greater<int>{});
         const auto end2 = chrono::high_resolution_clock::now();
         cout << "QuickSort" << "\n\n" <<  "Runtime: " << ComputeDuration(begin2, end2) << " ns" << endl;
         cout << "Verified: " << VerifyOrder(input_vector2, greater<int>{}) << "\n\n"; //ISSUE! not verified

      }
   }//end random

 else if (input_type == "sorted_small_to_large") {
   vector<int> input_vector = GenerateSortedVector(input_size, true);
   vector<int> input_vector1 = input_vector;
   vector<int> input_vector2 = input_vector;

   if (comparison_type == "less") {
     //HEAP
     const auto begin = chrono::high_resolution_clock::now();
     HeapSort(input_vector, less<int>{});
     const auto end = chrono::high_resolution_clock::now();
     cout << "Heapsort" << "\n\n" <<  "Runtime: " << ComputeDuration(begin, end) << " ns" << endl;
     cout << "Verified: " << VerifyOrder(input_vector, less<int>{}) << "\n\n";
     //MERGE
     const auto begin1 = chrono::high_resolution_clock::now();
     MergeSort(input_vector1, less<int>{});
     const auto end1 = chrono::high_resolution_clock::now();
     cout << "MergeSort" << "\n\n" <<  "Runtime: " << ComputeDuration(begin1, end1) << " ns" << endl;
     cout << "Verified: " << VerifyOrder(input_vector1, less<int>{}) << "\n\n";
     //QUICK
     const auto begin2 = chrono::high_resolution_clock::now();
     QuickSort(input_vector2, less<int>{});
     const auto end2 = chrono::high_resolution_clock::now();
     cout << "QuickSort" << "\n\n" <<  "Runtime: " << ComputeDuration(begin2, end2) << " ns" << endl;
     cout << "Verified: " << VerifyOrder(input_vector2, less<int>{}) << "\n\n";

  }//sorted_small_to_large - LESS
  if (comparison_type == "greater") {
     //HEAP
     const auto begin = chrono::high_resolution_clock::now();
     HeapSort(input_vector, greater<int>{});
     const auto end = chrono::high_resolution_clock::now();
     cout << "Heapsort" << "\n\n" <<  "Runtime: " << ComputeDuration(begin, end) << " ns" << endl;
     cout << "Verified: " << VerifyOrder(input_vector, greater<int>{}) << "\n\n";
     //MERGE
     const auto begin1 = chrono::high_resolution_clock::now();
     MergeSort(input_vector1, greater<int>{});
     const auto end1 = chrono::high_resolution_clock::now();
     cout << "MergeSort" << "\n\n" <<  "Runtime: " << ComputeDuration(begin1, end1) << " ns" << endl;
     cout << "Verified: " << VerifyOrder(input_vector1, greater<int>{}) << "\n\n";
     //QUICK
     const auto begin2 = chrono::high_resolution_clock::now();
     QuickSort(input_vector2, greater<int>{});
     const auto end2 = chrono::high_resolution_clock::now();
     cout << "QuickSort" << "\n\n" <<  "Runtime: " << ComputeDuration(begin2, end2) << " ns" << endl;
     cout << "Verified: " << VerifyOrder(input_vector2, greater<int>{}) << "\n\n";  //ISSUE - Doesn't verify
  }//sorted_small_to_large - GREATER

 }//sorted_small_to_large

 else if (input_type == "sorted_large_to_small") {
     vector<int> input_vector = GenerateSortedVector(input_size, false);
     vector<int> input_vector1 = input_vector;
     vector<int> input_vector2 = input_vector;

     if (comparison_type == "less") {
       //HEAP
       const auto begin = chrono::high_resolution_clock::now();
       HeapSort(input_vector, less<int>{});
       const auto end = chrono::high_resolution_clock::now();
       cout << "Heapsort" << "\n\n" <<  "Runtime: " << ComputeDuration(begin, end) << " ns" << endl;
       cout << "Verified: " << VerifyOrder(input_vector, less<int>{}) << "\n\n";
       //MERGE
       const auto begin1 = chrono::high_resolution_clock::now();
       MergeSort(input_vector1, less<int>{});
       const auto end1 = chrono::high_resolution_clock::now();
       cout << "MergeSort" << "\n\n" <<  "Runtime: " << ComputeDuration(begin1, end1) << " ns" << endl;
       cout << "Verified: " << VerifyOrder(input_vector1, less<int>{}) << "\n\n";
       //QUICK
       const auto begin2 = chrono::high_resolution_clock::now();
       QuickSort(input_vector2, less<int>{});
       const auto end2 = chrono::high_resolution_clock::now();
       cout << "QuickSort" << "\n\n" <<  "Runtime: " << ComputeDuration(begin2, end2) << " ns" << endl;
       cout << "Verified: " << VerifyOrder(input_vector2, less<int>{}) << "\n\n";
    }//sorted_large_to_small - LESS

    if (comparison_type == "greater") {
       //HEAP
       const auto begin = chrono::high_resolution_clock::now();
       HeapSort(input_vector, greater<int>{});
       const auto end = chrono::high_resolution_clock::now();
       cout << "Heapsort" << "\n\n" <<  "Runtime: " << ComputeDuration(begin, end) << " ns" << endl;
       cout << "Verified: " << VerifyOrder(input_vector, greater<int>{}) << endl;
       //MERGE
       const auto begin1 = chrono::high_resolution_clock::now();
       MergeSort(input_vector1, greater<int>{});
       const auto end1 = chrono::high_resolution_clock::now();
       cout << "MergeSort" << "\n\n" <<  "Runtime: " << ComputeDuration(begin1, end1) << " ns" << endl;
       cout << "Verified: " << VerifyOrder(input_vector1, greater<int>{}) << "\n\n";
       //QUICK
       const auto begin2 = chrono::high_resolution_clock::now();
       QuickSort(input_vector2, greater<int>{});
       const auto end2 = chrono::high_resolution_clock::now();
       cout << "QuickSort" << "\n\n" <<  "Runtime: " << ComputeDuration(begin2, end2) << " ns" << endl;
       cout << "Verified: " << VerifyOrder(input_vector2, greater<int>{}) << "\n\n";   //ISSUE - doesn't verify
    }//sorted_large_to_small - GREATER

  } //sorted_large_to_small



}//end sortTestingWrapper



int main(int argc, char **argv) {
  if (argc != 4) {
    cout << "Usage: " << argv[0] << "<input_type> <input_size> <comparison_type>" << endl;
    return 0;
  }

  sortTestingWrapper(argc, argv);

  return 0;
}

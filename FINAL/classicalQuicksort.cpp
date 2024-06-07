#include <iostream>
#include <fstream>
#include <chrono>
#include <memory>
#include <limits>

using namespace std;
using namespace chrono;

// Function to swap two elements
void swap(int* a, int* b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

// Partition function for quicksort
int partition(int arr[], int low, int high) {
  int pivot = arr[high]; // pivot element
  int i = (low - 1); // index of smaller element

  for (int j = low; j <= high - 1; j++) {
    // If current element is smaller than the pivot
    if (arr[j] < pivot) {
      i++; // increment index of smaller element
      swap(&arr[i], &arr[j]);
    }
  }
  swap(&arr[i + 1], &arr[high]);
  return (i + 1);
}

// Recursive quicksort implementation
void quickSort(int arr[], int low, int high) {
  if (low < high) {
    // pi is partitioning index, arr[p] is now at right place
    int pi = partition(arr, low, high);

    // Recursively sort elements before and after partition
    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
  }
}

// Main function
int main() {
  const int n = 101; // Reduced number of elements to sort (1 million)
  const string filename = "/home/kvass/Optimized_Quick_Sort/FINAL/DATASETS/oneHundred.txt"; // Name of the input file

  // Allocate memory for the array using unique_ptr for safety
  unique_ptr<int[]> arr(new int[n]);

  // Read data from the input file
  ifstream inputFile(filename);
  if (!inputFile.is_open()) {
    cerr << "Error opening file: " << filename << endl;
    return 1;
  }
  for (int i = 0; i < n; i++) {
    inputFile >> arr[i];
  }
  inputFile.close();

  // Start timer
  auto start = high_resolution_clock::now();

  // Call the quicksort function
  quickSort(arr.get(), 0, n - 1);

  // Stop timer
  auto end = high_resolution_clock::now();

  // Calculate elapsed time
  auto elapsed = duration_cast<nanoseconds>(end - start);

  // Print execution time
  cout << "Execution time for sorting " << n << " integers from file: " 
       << elapsed.count() << " nanoseconds\n";

  return 0;
}

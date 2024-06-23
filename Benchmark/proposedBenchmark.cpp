#include <iostream>
#include <vector>
#include <fstream>
#include <numeric>
#include <chrono>
#include <iomanip>
#include <random>

using namespace std;
using namespace std::chrono;

/**
 * Sorts a subarray of integers in the range [low, high] using a manual
 * sorting algorithm.
 *
 * @param arr The array to be sorted.
 * @param low The starting index of the subarray.
 * @param high The ending index of the subarray.
 */
void manualSort(vector<int>& arr, int low, int high) {
    // Calculate the number of elements in the subarray.
    int N = high - low + 1;
    
    // If the subarray has 1 or fewer elements, return early.
    if (N <= 1) {
        return;
    }
    // If the subarray has 2 elements, sort them if necessary.
    else if (N == 2) {
        if (arr[low] > arr[high]) {
            swap(arr[low], arr[high]);
        }
    }
    // If the subarray has 3 elements, sort them if necessary.
    else if (N == 3) {
        // Sort the first two elements if necessary.
        if (arr[low] > arr[high - 1]) {
            swap(arr[low], arr[high - 1]);
        }
        // Sort the first and last elements if necessary.
        if (arr[low] > arr[high]) {
            swap(arr[low], arr[high]);
        }
        // Sort the last two elements if necessary.
        if (arr[high - 1] > arr[high]) {
            swap(arr[high - 1], arr[high]);
        }
    }
}

/**
 * Calculates the pivot element for a given subarray.
 *
 * @param arr The array to be sorted.
 * @param low The starting index of the subarray.
 * @param high The ending index of the subarray.
 *
 * @return The calculated pivot element.
 */
int calculatePivot(const vector<int>& arr, int low, int high) {
    // Calculate the midpoint of the subarray.
    int mid = low + (high - low) / 2;

    // Calculate the maximum and minimum values on the left of the midpoint.
    int leftMax = max(arr[low], arr[mid - 1]);
    int leftMin = min(arr[low], arr[mid - 1]);

    // Calculate the maximum and minimum values on the right of the midpoint.
    int rightMax = max(arr[mid], arr[high]);
    int rightMin = min(arr[mid], arr[high]);

    // Calculate the mean of the left and right subarrays.
    int leftMean = (leftMax + leftMin) / 2;
    int rightMean = (rightMax + rightMin) / 2;
    
    // Calculate and return the pivot element.
    return (leftMean + rightMean) / 2;
}

/**
 * Partitions a vector of integers around a pivot element.
 *
 * @param arr The vector to partition
 * @param low The start index of the range to partition
 * @param high The end index of the range to partition
 * @param pivot The pivot element to partition around
 *
 * @return The index of the pivot element after partitioning
 */
int partition(vector<int>& arr, int low, int high, int pivot) {
    // Initialize the indices of the left and right elements
    int i = low - 1;
    int j = high + 1;
    
    // Partition the vector around the pivot element
    while (true) {
        
        // Move the left index up until the element is greater than or equal to
        // the pivot
        while (arr[++i] < pivot);
        
        // Move the right index down until the element is less than or equal to
        // the pivot
        while (arr[--j] > pivot);
        
        // If the indices have crossed over each other, break the loop
        if (i >= j) {
            break;
        }
        
        // Swap the elements at the current indices
        swap(arr[i], arr[j]);
    }
    
    // Return the index of the pivot element after partitioning
    return j;
}

/**
 * Performs insertion sort on a subrange of a vector of integers.
 *
 * @param arr The vector to sort
 * @param low The start index of the subrange to sort
 * @param high The end index of the subrange to sort
 */
void insertionSort(vector<int>& arr, int low, int high) {
    // Iterate through the subrange starting from the second element
    for (int i = low + 1; i <= high; i++) {
        // Set the current element as the key to insert
        int key = arr[i];
        // Initialize the index of the previous element
        int j = i - 1;
        
        // Traverse backward and move elements greater than the key
        while (j >= low && arr[j] > key) {
            // Shift the element to the right
            arr[j + 1] = arr[j];
            j--;
        }
        
        // Place the key at its correct position
        arr[j + 1] = key;
    }
}

/**
 * Performs quicksort on a subrange of a vector of integers.
 *
 * @param arr The vector to sort
 * @param low The start index of the subrange to sort
 * @param high The end index of the subrange to sort
 */
void quickSort(vector<int>& arr, int low, int high) {
    // Get the size of the subrange
    int N = high - low + 1;
    
    // If the subrange size is less than or equal to 3, use manualSort
    if (N <= 3) {
        manualSort(arr, low, high);
    } 
    // If the subrange size is less than or equal to 10, use insertionSort
    else if (N <= 10) {
        insertionSort(arr, low, high);
    } 
    // Otherwise, use the quicksort algorithm
    else {
        // Calculate the pivot element index
        int pivot = calculatePivot(arr, low, high);
        
        // Partition the subrange around the pivot element
        int q = partition(arr, low, high, pivot);
        
        // Recursively sort the subranges before and after the pivot element
        quickSort(arr, low, q);
        quickSort(arr, q + 1, high);
    }
}

/**
 * Generates a vector of size integers with a uniform distribution.
 * The distribution is centered at size / 2 and has a range of size.
 *
 * @param size The size of the vector to generate
 * @return A vector of size integers with a uniform distribution
 */
vector<int> generateUniformData(size_t size) {
    // Create a vector to store the generated data
    vector<int> data(size);
    
    // Create a random device and a mersenne twister generator
    random_device rd;
    mt19937 gen(rd());
    
    // Create a uniform integer distribution with a range of 0 to size - 1
    uniform_int_distribution<> dis(0, size - 1);
    
    // Generate random integers and store them in the data vector
    for (size_t i = 0; i < size; ++i) {
        data[i] = dis(gen);
    }
    
    // Return the generated data vector
    return data;
}

/**
 * Generates a vector of size integers with a bimodal distribution.
 * The distribution consists of two normal distributions centered
 * at size/3 and 2*size/3, respectively. The range of the distribution
 * is from 0 to size-1.
 *
 * @param size The size of the vector to generate
 * @return A vector of size integers with a bimodal distribution
 */
vector<int> generateBimodalData(size_t size) {
    // Create a vector to store the generated data
    vector<int> data(size);
    
    // Create a random device and a mersenne twister generator
    random_device rd;
    mt19937 gen(rd());
    
    // Create two normal distributions with ranges from 0 to size-1
    normal_distribution<> dis1(size / 3, size / 20);
    normal_distribution<> dis2(2 * size / 3, size / 20);
    
    // Generate random integers and store them in the data vector
    for (size_t i = 0; i < size; ++i) {
        // Alternate between the two normal distributions
        if (i % 2 == 0) {
            data[i] = round(dis1(gen));
        } else {
            data[i] = round(dis2(gen));
        }
        // Ensure the values are within the range of the data vector
        if (data[i] < 0) {
            data[i] = 0;
        } else if (data[i] >= static_cast<int>(size)) {
            data[i] = size - 1;
        }
    }
    
    // Return the generated data vector
    return data;
}

/**
 * Generates a vector of size integers with an exponential distribution.
 * The distribution has a lambda parameter of 1/(size/10).
 * The range of the distribution is from 0 to size-1.
 *
 * @param size The size of the vector to generate
 * @return A vector of size integers with an exponential distribution
 */
vector<int> generateExponentialData(size_t size) {
    // Create a vector to store the generated data
    vector<int> data(size);
    
    // Create a random device and a mersenne twister generator
    random_device rd;
    mt19937 gen(rd());
    
    // Create an exponential distribution with lambda parameter of 1/(size/10)
    exponential_distribution<> dis(1.0 / (size / 10));
    
    // Generate random integers and store them in the data vector
    for (size_t i = 0; i < size; ++i) {
        // Generate a random integer using the exponential distribution
        data[i] = round(dis(gen));
        // Ensure the values are within the range of the data vector
        if (data[i] < 0) {
            data[i] = 0;
        } else if (data[i] >= static_cast<int>(size)) {
            data[i] = size - 1;
        }
    }
    
    // Return the generated data vector
    return data;
}

/**
 * Generates a vector of size integers with a normal distribution.
 * The distribution is centered at size / 2 and has a standard deviation of size / 10.
 * The generated values are truncated to the range of the data vector.
 *
 * @param size The size of the vector to generate
 * @return A vector of size integers with a normal distribution
 */
vector<int> generateNormalData(size_t size) {
    // Create a vector to store the generated data
    vector<int> data(size);
    
    // Create a random device and a mersenne twister generator
    random_device rd;
    mt19937 gen(rd());
    
    // Create a normal distribution with a mean of size / 2 and a standard deviation of size / 10
    normal_distribution<> dis(size / 2, size / 10);
    
    // Generate random integers and store them in the data vector
    for (size_t i = 0; i < size; ++i) {
        // Generate a random integer using the normal distribution
        data[i] = static_cast<int>(dis(gen));
        // Ensure the values are within the range of the data vector
        if (data[i] < 0) {
            data[i] = 0; // truncate values less than 0
        } else if (data[i] >= static_cast<int>(size)) {
            data[i] = size - 1; // truncate values greater than or equal to size
        }
    }
    
    // Return the generated data vector
    return data;
}

/**
 * Generates a vector of size integers with the values reversed.
 *
 * @param size The size of the vector to generate
 * @return A vector of size integers with reversed values
 */
vector<int> generateReversedData(size_t size) {
    // Create a vector to store the generated data
    vector<int> data(size);
    
    // Populate the vector with reversed values
    for (size_t i = 0; i < size; ++i) {
        // Calculate the index of the value to be placed at position i
        size_t reversedIndex = size - i - 1;
        // Set the value at position i to the reversed value
        data[i] = reversedIndex;
    }
    
    // Return the generated data vector
    return data;
}

/**
 * Runs the sorting tests for different datasets and sizes.
 * 
 * @param file The output file to write the results to
 */
void runTests(ofstream& file) {
    // Define the sizes to test
    vector<size_t> sizes = {10, 100, 1000, 10000, 100000};
    const int iterations = 10; // Number of times to run each test
    vector<string> datasetNames = {"Uniform", "Normal", "Exponential", "Bimodal", "Reversed"};

    // Run tests for each size
    for (size_t size : sizes) {
        file << "Data Size: " << size << endl;
        cout << "Data Size: " << size << endl;

        vector<long long> totalDurations(datasetNames.size(), 0); // Total durations for each dataset

        // Run tests for each iteration
        for (int i = 0; i < iterations; ++i) {
            // Generate datasets
            vector<vector<int>> datasets = {
                generateUniformData(size),
                generateBimodalData(size),
                generateExponentialData(size),
                generateNormalData(size),
                generateReversedData(size)
            };

            // Run quickSort for each dataset and accumulate the durations
            for (size_t j = 0; j < datasets.size(); ++j) {
                vector<int> data = datasets[j];

                auto startSorting = high_resolution_clock::now();
                quickSort(data, 0, data.size() - 1);
                auto stopSorting = high_resolution_clock::now();
                auto durationSorting = duration_cast<nanoseconds>(stopSorting - startSorting);

                totalDurations[j] += durationSorting.count();

                cout << datasetNames[j] << " Iteration " << i + 1 << ": " << durationSorting.count() << " nanoseconds" << endl;
                file << datasetNames[j] << " Iteration " << i + 1 << ": " << durationSorting.count() << " nanoseconds" << endl;
            }
        }

        // Calculate and print the average durations for each dataset
        cout << "Average runtimes:" << endl;
        file << "Average runtimes:" << endl;

        for (size_t j = 0; j < datasetNames.size(); ++j) {
            double averageDuration = static_cast<double>(totalDurations[j]) / iterations;
            cout << datasetNames[j] << ": " << fixed << setprecision(2) << averageDuration << " nanoseconds" << endl;
            file << datasetNames[j] << ": " << fixed << setprecision(2) << averageDuration << " nanoseconds" << endl;
        }

        cout << "---------------------------------" << endl;
        file << "---------------------------------" << endl;
    }
}

/**
 * @brief Main function that runs the tests and writes the results to a file.
 * 
 * @return int The exit status of the program.
 */
int main() {
    // Open the output file for writing
    ofstream file("quick_sort_test_results.txt");

    // Check if the file was successfully opened
    if (file.is_open()) {
        // Run the tests and write the results to the file
        runTests(file);

        // Close the file
        file.close();
    } else {
        // Print an error message if the file could not be opened
        cerr << "Unable to open file for writing." << endl;
    }

    return 0;
}

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
 * Sorts a small array (less than or equal to 3 elements) in-place using a
 * simple sorting algorithm
 *
 * @param arr The vector to sort
 * @param low The start index of the range to sort
 * @param high The end index of the range to sort
 */
void manualSort(vector<int>& arr, int low, int high) {
    // If the vector has only one or no elements, there's nothing to do
    int N = high - low + 1;
    if (N <= 1) {
        return;
    } else if (N == 2) {
        // If the vector has only two elements, we can swap them if they're in
        // the wrong order
        if (arr[low] > arr[high]) {
            swap(arr[low], arr[high]);
        }
    } else if (N == 3) {
        // If the vector has only three elements, we can swap them to put them
        // in order
        if (arr[low] > arr[high - 1]) {
            swap(arr[low], arr[high - 1]);
        }
        if (arr[low] > arr[high]) {
            swap(arr[low], arr[high]);
        }
        if (arr[high - 1] > arr[high]) {
            swap(arr[high - 1], arr[high]);
        }
    }
}

/**
 * Calculates the pivot element for a given range of elements in a vector.
 * The pivot is chosen as the mean of the maximum and minimum elements on
 * either side of the middle element.
 *
 * @param arr The vector to calculate the pivot for
 * @param low The start index of the range to consider
 * @param high The end index of the range to consider
 *
 * @return The calculated pivot element
 */
int calculatePivot(const vector<int>& arr, int low, int high) {
    
    // Calculate the index of the middle element
    int mid = low + (high - low) / 2;
    
    // Calculate the maximum and minimum elements on either side of the middle
    // element
    int leftMax = max(arr[low], arr[mid - 1]);
    int leftMin = min(arr[low], arr[mid - 1]);
    int rightMax = max(arr[mid], arr[high]);
    int rightMin = min(arr[mid], arr[high]);
    
    // Calculate the mean of the maximum and minimum elements on either side of
    // the middle element
    int leftMean = (leftMax + leftMin) / 2;
    int rightMean = (rightMax + rightMin) / 2;
    
    // Calculate the pivot element as the mean of the means of the two sides
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
 * Performs a quicksort on a vector of integers.
 *
 * @param arr The vector to sort
 * @param low The start index of the range to sort
 * @param high The end index of the range to sort
 */
void quickSort(vector<int>& arr, int low, int high) {
    // Get the size of the range to sort
    int N = high - low + 1;
    
    // If the size is less than or equal to 3, use manual sorting
    if (N <= 3) {
        manualSort(arr, low, high);
    } else {
        // Calculate the pivot element
        int pivot = calculatePivot(arr, low, high);
        
        // Partition the vector around the pivot element
        int q = partition(arr, low, high, pivot);
        
        // Recursively quicksort the left and right halves
        quickSort(arr, low, q);
        quickSort(arr, q + 1, high);
    }
}

/**
 * Generates a vector of size integers with values uniformly distributed between 0 and size - 1.
 *
 * @param size The size of the vector to generate
 * @return A vector of size integers with values uniformly distributed between 0 and size - 1
 */
vector<int> generateUniformData(size_t size) {
    // Create a vector of size integers
    vector<int> data(size);
    
    // Create a random number generator
    random_device rd;
    mt19937 gen(rd());
    
    // Create a uniform distribution with values between 0 and size - 1
    uniform_int_distribution<> dis(0, size - 1);
    
    // Fill the vector with values from the uniform distribution
    for (size_t i = 0; i < size; ++i) {
        data[i] = dis(gen);
    }
    
    // Return the generated vector
    return data;
}

/**
 * Generates a vector of size integers with bimodal distribution.
 * The distribution consists of two normal distributions centered at size/3 and
 * 2*size/3 respectively. The standard deviation is size/20.
 *
 * @param size The size of the vector to generate
 * @return A vector of size integers with bimodal distribution
 */
vector<int> generateBimodalData(size_t size) {
    vector<int> data(size);
    random_device rd;
    mt19937 gen(rd());

    // Create two normal distributions centered at size/3 and 2*size/3
    normal_distribution<> dis1(size / 3, size / 20);
    normal_distribution<> dis2(2 * size / 3, size / 20);

    for (size_t i = 0; i < size; ++i) {
        // Alternate between the two distributions
        if (i % 2 == 0) {
            data[i] = round(dis1(gen));
        } else {
            data[i] = round(dis2(gen));
        }

        // Ensure the data is within the range of the vector
        if (data[i] < 0) {
            data[i] = 0;
        } else if (data[i] >= static_cast<int>(size)) {
            data[i] = size - 1;
        }
    }

    return data;
}

/**
 * Generates a vector of size integers with an exponential distribution.
 * The distribution is centered at size / 10 and has a rate parameter of 1.0 / (size / 10).
 *
 * @param size The size of the vector to generate
 * @return A vector of size integers with an exponential distribution
 */
vector<int> generateExponentialData(size_t size) {
    vector<int> data(size);
    random_device rd;
    mt19937 gen(rd());

    // Create an exponential distribution with a rate parameter of 1.0 / (size / 10)
    exponential_distribution<> dis(1.0 / (size / 10));

    for (size_t i = 0; i < size; ++i) {
        // Generate a random number from the exponential distribution
        data[i] = round(dis(gen));

        // Ensure the data is within the range of the vector
        if (data[i] < 0) {
            data[i] = 0;
        } else if (data[i] >= static_cast<int>(size)) {
            data[i] = size - 1;
        }
    }

    return data;
}

/**
 * Generates a vector of size integers with a normal distribution.
 * The distribution is centered at size / 2 and has a standard deviation of size / 10.
 *
 * @param size The size of the vector to generate
 * @return A vector of size integers with a normal distribution
 */
vector<int> generateNormalData(size_t size) {
    vector<int> data(size);
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<> dis(size / 2, size / 10); // normal distribution centered at size / 2 with standard deviation of size / 10

    for (size_t i = 0; i < size; ++i) {
        data[i] = static_cast<int>(dis(gen));
        // Ensure the data is within the range of the vector
        if (data[i] < 0) {
            data[i] = 0;
        } else if (data[i] >= static_cast<int>(size)) {
            data[i] = size - 1;
        }
    }

    return data;
}

/**
 * Generates a vector of size integers with the values reversed.
 *
 * @param size The size of the vector to generate
 * @return A vector of size integers with reversed values
 */
vector<int> generateReversedData(size_t size) {
    // Create a vector of the specified size
    vector<int> data(size);

    // Fill the vector with values reversed
    for (size_t i = 0; i < size; ++i) {
        data[i] = size - i - 1;
    }

    // Return the generated vector
    return data;
}

/**
 * Runs tests for different datasets and saves the results to a file.
 *
 * @param file The file to write the results to
 */
void runTests(ofstream& file) {
    // Define the sizes of the datasets to test
    vector<size_t> sizes = {10, 100, 1000, 10000, 100000};
    // Define the number of iterations to run for each dataset
    const int iterations = 10;
    // Define the names of the datasets
    vector<string> datasetNames = {"Uniform", "Normal", "Exponential", "Bimodal", "Reversed"};

    // Loop through each dataset size
    for (size_t size : sizes) {
        // Write the size to the file and to the console
        file << "Data Size: " << size << endl;
        cout << "Data Size: " << size << endl;

        // Initialize a vector to store the total durations for each dataset
        vector<long long> totalDurations(datasetNames.size(), 0);

        // Loop through each iteration for the dataset
        for (int i = 0; i < iterations; ++i) {
            // Generate the datasets for the current size
            vector<vector<int>> datasets = {
                generateUniformData(size),
                generateBimodalData(size),
                generateExponentialData(size),
                generateNormalData(size),
                generateReversedData(size)
            };

            // Loop through each dataset and calculate the duration of the quick sort
            for (size_t j = 0; j < datasets.size(); ++j) {
                vector<int> data = datasets[j];

                auto startSorting = high_resolution_clock::now();
                quickSort(data, 0, data.size() - 1);
                auto stopSorting = high_resolution_clock::now();
                auto durationSorting = duration_cast<nanoseconds>(stopSorting - startSorting);

                // Add the duration to the total duration for the dataset
                totalDurations[j] += durationSorting.count();

                // Write the duration to the console and file
                cout << datasetNames[j] << " Iteration " << i + 1 << ": " << durationSorting.count() << " nanoseconds" << endl;
                file << datasetNames[j] << " Iteration " << i + 1 << ": " << durationSorting.count() << " nanoseconds" << endl;
            }
        }

        // Calculate the average duration for each dataset
        cout << "Average runtimes:" << endl;
        file << "Average runtimes:" << endl;

        for (size_t j = 0; j < datasetNames.size(); ++j) {
            double averageDuration = static_cast<double>(totalDurations[j]) / iterations;
            // Write the average duration to the console and file
            cout << datasetNames[j] << ": " << fixed << setprecision(2) << averageDuration << " nanoseconds" << endl;
            file << datasetNames[j] << ": " << fixed << setprecision(2) << averageDuration << " nanoseconds" << endl;
        }

        // Write a separator line to the console and file
        cout << "---------------------------------" << endl;
        file << "---------------------------------" << endl;
    }
}

/**
 * The main function that runs the tests and writes the results to a file.
 *
 * @return 0 upon successful completion
 *
 * @throws None
 */
int main() {
    // Open the output file to write the test results
    ofstream file("quick_sort_test_results.txt");

    // Check if the file was successfully opened
    if (file.is_open()) {
        // Run the tests and write the results to the file
        runTests(file);

        // Close the file after writing
        file.close();
    } else {
        // Print an error message if the file could not be opened
        cerr << "Unable to open file for writing." << endl;
    }

    return 0;
}


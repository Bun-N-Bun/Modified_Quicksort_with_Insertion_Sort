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
 * Classical quicksort implementation.
 *
 * @param arr The vector of integers to be sorted.
 * @param low The starting index of the subarray to be sorted.
 * @param high The ending index of the subarray to be sorted.
 */
void quickSort(vector<int>& arr, int low, int high) {
    // Base case: if the subarray has less than 2 elements, return early.
    if (low < high) {
        // Choose the last element as the pivot.
        int pivot = arr[high];
        int i = low - 1;

        // Partition the array into two subarrays.
        for (int j = low; j < high; j++) {
            // If the current element is less than the pivot, swap it with the
            // element at index i and increment i.
            if (arr[j] < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }

        // Swap the pivot element with the element at index i + 1.
        swap(arr[i + 1], arr[high]);

        // Return the index of the pivot element.
        int pi = i + 1;

        // Recursively sort the subarrays to the left and right of the pivot.
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

/**
 * Generate a vector of integers with a uniform distribution.
 *
 * @param size The size of the vector to generate.
 * @return A vector of integers with a uniform distribution.
 */
vector<int> generateUniformData(size_t size) {
    // Create a vector to store the generated data.
    vector<int> data(size);
    
    // Create a random device and a mersenne twister generator.
    random_device rd;
    mt19937 gen(rd());
    
    // Create a uniform distribution with a range of 0 to size-1.
    uniform_int_distribution<> dis(0, size - 1);
    
    // Generate random integers and store them in the data vector.
    for (size_t i = 0; i < size; ++i) {
        // Generate a random integer using the uniform distribution.
        data[i] = dis(gen);
    }
    
    // Return the generated data vector.
    return data;
}

/**
 * Generate a vector of integers with a bimodal distribution.
 *
 * This function generates a vector of integers with a bimodal distribution.
 * The first half of the vector has a normal distribution with a mean of size/3
 * and a standard deviation of size/20. The second half of the vector has a
 * normal distribution with a mean of 2*size/3 and a standard deviation of
 * size/20. The function ensures that all generated values are within the
 * range [0, size-1].
 *
 * @param size The size of the vector to generate.
 * @return A vector of integers with a bimodal distribution.
 */
vector<int> generateBimodalData(size_t size) {
    // Create a vector to store the generated data.
    vector<int> data(size);

    // Create a random device and a mersenne twister generator.
    random_device rd;
    mt19937 gen(rd());

    // Create two normal distributions with different means and standard deviations.
    normal_distribution<> dis1(size / 3, size / 20);
    normal_distribution<> dis2(2 * size / 3, size / 20);

    // Generate random integers and store them in the data vector.
    for (size_t i = 0; i < size; ++i) {
        // Generate a random integer using the appropriate normal distribution.
        if (i % 2 == 0) {
            data[i] = round(dis1(gen));
        } else {
            data[i] = round(dis2(gen));
        }

        // Ensure that all generated values are within the range [0, size-1].
        if (data[i] < 0) {
            data[i] = 0;
        } else if (data[i] >= static_cast<int>(size)) {
            data[i] = size - 1;
        }
    }

    // Return the generated data vector.
    return data;
}

/**
 * Generates a vector of integers with an exponential distribution.
 *
 * The function generates a vector of integers with an exponential
 * distribution. The distribution is defined by the exponential_distribution
 * class from the C++ standard library. The generated values are rounded to
 * the nearest integer. The function ensures that all generated values are
 * within the range [0, size-1].
 *
 * @param size The size of the vector to generate.
 * @return A vector of integers with an exponential distribution.
 */
vector<int> generateExponentialData(size_t size) {
    // Create a vector to store the generated data.
    vector<int> data(size);

    // Create a random device and a mersenne twister generator.
    random_device rd;
    mt19937 gen(rd());

    // Create an exponential distribution with a lambda parameter of 1 / (size / 10).
    exponential_distribution<> dis(1.0 / (size / 10));

    // Generate random integers and store them in the data vector.
    for (size_t i = 0; i < size; ++i) {
        // Generate a random integer using the exponential distribution.
        data[i] = round(dis(gen));

        // Ensure that all generated values are within the range [0, size-1].
        if (data[i] < 0) {
            data[i] = 0;
        } else if (data[i] >= static_cast<int>(size)) {
            data[i] = size - 1;
        }
    }

    // Return the generated data vector.
    return data;
}

/**
 * Generates a vector of integers with a normal distribution.
 *
 * The function generates a vector of integers with a normal distribution.
 * The distribution is defined by the normal_distribution class from the
 * C++ standard library. The generated values are rounded to the nearest
 * integer. The function ensures that all generated values are within the
 * range [0, size-1].
 *
 * @param size The size of the vector to generate.
 * @return A vector of integers with a normal distribution.
 */
vector<int> generateNormalData(size_t size) {
    // Create a vector to store the generated data.
    vector<int> data(size);

    // Create a random device and a mersenne twister generator.
    random_device rd;
    mt19937 gen(rd());

    // Create a normal distribution with a mean of size / 2 and a standard
    // deviation of size / 10.
    normal_distribution<> dis(size / 2, size / 10);

    // Generate random integers and store them in the data vector.
    for (size_t i = 0; i < size; ++i) {
        // Generate a random integer using the normal distribution.
        data[i] = static_cast<int>(dis(gen));

        // Ensure that all generated values are within the range [0, size-1].
        if (data[i] < 0) {
            data[i] = 0;
        } else if (data[i] >= static_cast<int>(size)) {
            data[i] = size - 1;
        }
    }

    // Return the generated data vector.
    return data;
}

/**
 * Generates a vector of integers where each element is the reversed index.
 *
 * This function generates a vector of integers where each element is the
 * reversed index. For example, if the size of the vector is 10, the
 * generated vector will be {9, 8, 7, 6, 5, 4, 3, 2, 1, 0}. This function is
 * useful for testing algorithms that need to sort in reverse order.
 *
 * @param size The size of the vector to generate.
 * @return A vector of integers where each element is the reversed index.
 */
vector<int> generateReversedData(size_t size) {
    // Create a vector to store the generated data.
    vector<int> data(size);

    // Generate the reversed indices and store them in the data vector.
    for (size_t i = 0; i < size; ++i) {
        // Calculate the reversed index by subtracting the current index from
        // the size of the vector minus one.
        data[i] = size - i - 1;
    }

    // Return the generated data vector.
    return data;
}

/**
 * Runs the sorting tests for different datasets and sizes.
 * 
 * This function runs the sorting tests for different datasets and sizes.
 * It generates datasets of different types (uniform, normal, exponential,
 * bimodal, reversed) for each size and runs the quickSort algorithm on each
 * dataset multiple times. It calculates the average duration of the quickSort
 * algorithm for each dataset and writes the results to a file.
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
 * @brief Main function that runs the sorting tests and writes the results to a file.
 * 
 * This function opens the output file "quick_sort_test_results.txt" for writing. If the file
 * is successfully opened, it calls the runTests function to run the sorting tests and write
 * the results to the file. The function then closes the file. If the file cannot be opened,
 * an error message is printed to the console.
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

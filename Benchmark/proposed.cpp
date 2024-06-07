#include <iostream>
#include <vector>
#include <fstream>
#include <numeric>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

void manualSort(vector<int>& arr, int low, int high) {
    int N = high - low + 1;
    if (N <= 1) {
        return;
    } else if (N == 2) {
        if (arr[low] > arr[high]) {
            swap(arr[low], arr[high]);
        }
    } else if (N == 3) {
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

int partition(vector<int>& arr, int low, int high, int pivot) {
    int i = low - 1;
    int j = high + 1;
    while (true) {
        while (arr[++i] < pivot);
        while (arr[--j] > pivot);
        if (i >= j) {
            break;
        }
        swap(arr[i], arr[j]);
    }
    return j;
}

void insertionSort(vector<int>& arr, int low, int high) {
    for (int i = low + 1; i <= high; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= low && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int calculatePivot(vector<int>& arr, int low, int high) {
    int mid = (low + high) / 2;
    vector<int> leftSubarray(arr.begin() + low, arr.begin() + mid + 1);
    vector<int> rightSubarray(arr.begin() + mid + 1, arr.begin() + high + 1);

    double leftMean = accumulate(leftSubarray.begin(), leftSubarray.end(), 0.0) / leftSubarray.size();
    double rightMean = accumulate(rightSubarray.begin(), rightSubarray.end(), 0.0) / rightSubarray.size();

    int pivot = static_cast<int>((leftMean + rightMean) / 2);

    return pivot;
}

void quickSort(vector<int>& arr, int low, int high) {
    int N = high - low + 1;
    if (N <= 3) {
        manualSort(arr, low, high);
    } else if (N <= 100) {
        insertionSort(arr, low, high);
    } else {
        int pivot = calculatePivot(arr, low, high);
        int q = partition(arr, low, high, pivot);
        quickSort(arr, low, q);
        quickSort(arr, q + 1, high);
    }
}

vector<int> readDataFromFile(const string& filename) {
    vector<int> data;
    ifstream inputFile(filename);
    int num;
    while (inputFile >> num) {
        data.push_back(num);
    }
    inputFile.close();
    return data;
}

void writeDataToFile(const vector<int>& data, const string& filename) {
    ofstream outputFile(filename);
    for (int num : data) {
        outputFile << num << "\n";
    }
    outputFile.close();
}

int main() {
    // Read data from file
    string filename = "/home/kvass/Optimized_Quick_Sort/FINAL/DATASETS/oneMillion.txt";
    vector<int> data = readDataFromFile(filename);

    // Sort the data
    auto startSorting = high_resolution_clock::now();
    quickSort(data, 0, data.size() - 1);
    auto stopSorting = high_resolution_clock::now();
    auto durationSorting = duration_cast<nanoseconds>(stopSorting - startSorting);
    cout << "Sorting time: " << scientific << durationSorting.count() << " nanoseconds" << endl;

    return 0;
}
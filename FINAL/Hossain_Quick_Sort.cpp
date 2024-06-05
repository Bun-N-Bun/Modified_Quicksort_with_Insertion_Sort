//Optimized Quick Sort
//Md. Sabir Hossain proposed algorithm with Insertion Sort

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <numeric>

using namespace std;

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
    int j = high;
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
    } else {
        int pivot = calculatePivot(arr, low, high);
        int q = partition(arr, low, high, pivot);
        quickSort(arr, low, q);
        quickSort(arr, q + 1, high);
    }
}

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 1000);

    vector<int> data(100);
    generate(data.begin(), data.end(), [&]() { return dis(gen); });

    quickSort(data, 0, data.size() - 1);

    cout << "Sorted array: ";
    for (int num : data) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}


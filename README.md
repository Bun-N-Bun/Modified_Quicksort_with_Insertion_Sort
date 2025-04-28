# Runtime Optimization of Modified Quicksort Using Insertion Sort

## Overview
This project implements an optimized version of the Quicksort algorithm by integrating Insertion Sort as a subroutine for sorting small subarrays. The optimization is based on the work of Md. Sabir Hossain, who proposed a new pivot selection method and a "Manual Sort" function to reduce the worst-case complexity of Quicksort to O(n log n). This implementation further enhances runtime performance by using Insertion Sort for small datasets, resulting in improved efficiency.

The project includes three versions of the proposed Quicksort algorithm, each with a different threshold for switching to Insertion Sort:

- Proposed 10 Quicksort: Threshold of 10.
- Proposed 50 Quicksort: Threshold of 50.
- Proposed 100 Quicksort: Threshold of 100.

These versions are tested against Hossain’s Quicksort and the Classical Quicksort on various data distributions (Uniform, Normal, Exponential, Bimodal, and Reversed) and dataset sizes (10, 100, 1000, 10000, and 100000).

[Read the full paper here](Runtime_Optimization_of_Modified_Quicksort_Using_Insertion_Sort.pdf)

---
### Results
The Proposed 10 Quicksort (threshold = 10) demonstrated the best performance, ranking 1st in 16 out of 25 datasets and achieving a 27.9% improvement over Hossain’s Quicksort. Increasing the threshold for Insertion Sort decreased performance, with the Proposed 50 Quicksort running 22.31% faster and the Proposed 100 Quicksort running only 0.62% faster than Hossain’s Quicksort.

---
## Key Features
- Optimized Quicksort: Combines Quicksort with Insertion Sort for improved performance on small subarrays.
- Pivot Selection: Uses a custom pivot selection method based on the mean of left and right subarrays.
- Manual Sort: Implements a manual sorting function for very small datasets (≤ 3 elements).
- Threshold-Based Insertion Sort: Switches to Insertion Sort for subarrays smaller than a specified threshold (10, 50, or 100).

---
## Objectives
1. To optimize the runtime performance of Quicksort by integrating Insertion Sort for small subarrays.
2. To compare the performance of the proposed algorithm with Hossain’s Quicksort and the Classical Quicksort.
3. To evaluate the impact of different thresholds for Insertion Sort on overall sorting performance.

---
## Implementation Details
The project is implemented in Python and consists of the following functions:
    - quick_sort(arr, low, high): The main Quicksort function with Insertion Sort integration.
    - manual_sort(arr, low, high): Sorts subarrays with ≤ 3 elements.
    - insertion_sort(arr, low, high): Sorts subarrays using Insertion Sort.
    - partition(arr, low, high, pivot): Partitions the array around the pivot.
    - calculate_pivot(arr, low, high): Calculates the pivot using the mean of left and right subarrays.

---
## How to Use
1. Clone the Repository:
   ```
   git clone https://github.com/your-repo/optimized-quicksort.git
   cd optimized-quicksort
   ```
2. Run the Code:
     - Ensure you have Python installed.
     - Run the Python script:
        ```
        python optimized_quicksort.py
        ```
3. Sample Usage:
- The script generates a random dataset and sorts it using the optimized Quicksort algorithm.
- Modify the dataset size or distribution as needed for testing.

---
## Contributors
- Krystal Heart Bacalso
- Javier Raut
- Junar Landicho

## Acknowledgments
This project was developed as part of the research conducted at the Department of Computer Science, University of Science and Technology of Southern Philippines. Special thanks to Md. Sabir Hossain for his foundational work on optimizing Quicksort.

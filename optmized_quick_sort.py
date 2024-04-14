#Optimized Quick Sort
#Md. Sabir Hossain proposed algorithm with Insertion Sort
import random
def quick_sort(arr, low, high):
    N = high - low + 1
    if N <= 3:
        manual_sort(arr, low, high) 
    elif N <= 10:
        insertion_sort(arr, low, high)  # Use Insertion Sort for small sublists
    else:
        pivot = calculate_pivot(arr, low, high)  # Replace with your pivot selection function
        q = partition(arr, low, high, pivot)
        quick_sort(arr, low, q)
        quick_sort(arr, q + 1, high)

def manual_sort(arr, low, high):
    N = high - low + 1
    if N <= 1:
        return
    elif N == 2:
        if arr[low] > arr[high]:
            arr[low], arr[high] = arr[high], arr[low]
    elif N == 3:
        if arr[low] > arr[high-1]:
            arr[low], arr[high-1] = arr[high-1], arr[low]
    
    if arr[low] > arr[high]:
        arr[low], arr[high] = arr[high], arr[low]
    if arr[high-1] > arr[low]:
        arr[high-1], arr[high] = arr[high], arr[high-1]
        
    return arr
        
def partition(arr, low, high, pivot):
    i = low - 1
    j = high
    while True:
        while arr[i] < pivot:
            i += 1
        while arr[j] > pivot:
            j -= 1
        if i >= j:
            break
        arr[i], arr[j] = arr[j], arr[i]  # Swap elements

    return j

def insertion_sort(arr, low, high):
    for i in range(low + 1, high + 1):
        key = arr[i]
        j = i - 1
        while j >= low and arr[j] > key:
            arr[j + 1] = arr[j]
            j -= 1
        arr[j + 1] = key

def calculate_pivot(arr, low, high):
    mid = (low + high) // 2
    left_subarray = arr[low:mid+1]
    right_subarray = arr[mid+1:high+1]
    
    left_mean = sum(left_subarray) / len(left_subarray)
    right_mean = sum(right_subarray) / len(right_subarray)
    
    pivot = (left_mean + right_mean) // 2
    return pivot

# Sample usage
data = random.sample(range(1000), 1000)
quick_sort(data, 0, len(data) - 1)
print("Sorted array:", data)

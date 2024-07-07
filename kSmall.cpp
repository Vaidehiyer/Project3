/**
 * @file kSmall.cpp
 * @author Hakim Abdisalam
 * StartID: oc3378es
 * @brief KSmall Algorithm implementation and test file
 * @version 0.1
 * @date 2024-07-07
 * Instructor: Jerome Covington
 * Due date: 07/08/2024
 * 
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <iostream>
#include <cstdlib>
using namespace std;

/**
 * @brief PArtitions arr[first..last]
 *
 * @param arr  Array to partition
 * @param first First element
 * @param last LAst element
 * @return int
 */
int partition(int *arr, int first, int last)
{
    // Choose pivot
    int pivot = arr[first];

    // Determine the regions S1 and S2
    int leftMark = first + 1;
    int rightMark = last;

    bool done = false;
    while (!done)
    {
        // Locate first entry on left that is > pivot
        while (leftMark <= rightMark && arr[leftMark] <= pivot)
        {
            leftMark++;
        }

        // Locate first entry on right that is < pivot
        while (rightMark >= leftMark && arr[rightMark] >= pivot)
        {
            rightMark--;
        }
        if (leftMark > rightMark)
        {
            done = true;
        }
        else
        {
            swap(arr[leftMark], arr[rightMark]);
        }
    }

    // Place pivot in proper position between S1 and S2
    swap(arr[first], arr[rightMark]);
    return rightMark;
}

/**
 * @brief Returns the kth smallest value in arr[first..last].
 *
 * @param k  : kth value to return
 * @param arr : Array to search
 * @param first : First element in array
 * @param last : LAst element in array
 * @return int : kth smallest value
 */
int kSmall(int k, int *arr, int first, int last)
{
    if (first <= last)
    {
        // Choose a pivot value p from anArray[first..last]
        // Partition the values of anArray[first..last] about p
        int pivotIndex = partition(arr, first, last);

        // If S1 contains k or more values, S1 contains the k
        // smallest values of the array segment anArray[first..last]
        if (k < pivotIndex - first + 1)
        {
            return kSmall(k, arr, first, pivotIndex - 1);
        }

        // Base case: the kth smallest value must be the pivot p
        else if (k == pivotIndex - first + 1)
        {
            return arr[pivotIndex];
        }

        // If S1 contains fewer than k – 1 values, the kth smallest
        // value in arr must be in S2
        else
        {
            return kSmall(k - (pivotIndex - first + 1), arr, pivotIndex + 1, last);
        }
    }
    return -1; // This line should never be reached.
}

int main()
{
    // Dynamic array allocation
    int size;
    cout << "Enter the size of the array: ";
    cin >> size;

    // Getting user inputs
    int *arr = new int[size];
    cout << "Enter " << size << " elements: ";
    for (int i = 0; i < size; i++)
    {
        cin >> arr[i];
    }

    // Get k
    int k;
    cout << "Enter the value of k: ";
    cin >> k;

    // display result
    if (k > 0 && k <= size)
    {
        int result = kSmall(k, arr, 0, size - 1);
        cout << "The " << k << "th smallest element is " << result << endl;
    }
    else
    {
        cout << "Invalid value of k" << endl;
    }

    // Test all three cases:
    // Case 1: kth smallest in S1
    cout << "Testing kth smallest in S1" << endl;
    int testArr1[] = {7, 4, 3, 6, 1};
    int testSize1 = sizeof(testArr1) / sizeof(testArr1[0]);
    cout << "Array: ";
    for (int i = 0; i < testSize1; i++)
    {
        cout << testArr1[i] << " ";
    }
    cout << endl;
    cout << "3rd smallest: " << kSmall(3, testArr1, 0, testSize1 - 1) << endl;

    // Case 2: kth smallest is the pivot
    cout << "Testing kth smallest is the pivot" << endl;
    int testArr2[] = {6, 3, 1, 10, 8, 4};
    int testSize2 = sizeof(testArr2) / sizeof(testArr2[0]);
    cout << "Array: ";
    for (int i = 0; i < testSize2; i++)
    {
        cout << testArr2[i] << " ";
    }
    cout << endl;
    cout << "4th smallest: " << kSmall(4, testArr2, 0, testSize2 - 1) << endl;

    // Case 3: kth smallest in S2
    cout << "Testing kth smallest in S2" << endl;
    int testArr3[] = {1, 3, 5, 2, 19, 13, 4};
    int testSize3 = sizeof(testArr3) / sizeof(testArr3[0]);
    cout << "Array: ";
    for (int i = 0; i < testSize3; i++)
    {
        cout << testArr3[i] << " ";
    }
    cout << endl;
    cout << "6th smallest: " << kSmall(6, testArr3, 0, testSize3 - 1) << endl;

    // Clean up dynamically allocated memory
    delete[] arr;

    return 0;
}

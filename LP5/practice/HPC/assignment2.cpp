#include <iostream>
#include <omp.h>
#include <chrono>

using namespace std;
void print_array(int *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}
void sequential_bubble_sort(int *arr, int n)
{

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
void parallel_bubble_sort(int *arr, int n)
{
#pragma omp parallel for shared(arr, n)
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void merge(int *arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[n1], R[n2];
    for (int i = 0; i < n1; i++)
    {
        L[i] = arr[left + i];
    }
    for (int i = 0; i < n2; i++)
    {
        R[i] = arr[mid + 1 + i];
    }
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void sequential_merge_sort(int *arr, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        sequential_merge_sort(arr, left, mid);
        sequential_merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void parallel_merge_sort(int *arr, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
#pragma omp parallel sections
        {
#pragma omp section
            {
                parallel_merge_sort(arr, left, mid);
            }
#pragma omp section
            {
                parallel_merge_sort(arr, mid + 1, right);
            }
        }
        merge(arr, left, mid, right);
    }
}
void test_bubble_sort_performance(int n)
{
    int *arr = new int[n];
    int *arr_copy = new int[n];

    // Initialize the array with random values
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 1000;
        arr_copy[i] = arr[i];
    }

    // Measure the execution time of sequential bubble sort
    auto start_time = chrono::high_resolution_clock::now();
    sequential_bubble_sort(arr, n);
    auto end_time = chrono::high_resolution_clock::now();
    auto sequential_sort_time = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();

    // Measure the execution time of parallel bubble sort
    start_time = chrono::high_resolution_clock::now();
    parallel_bubble_sort(arr_copy, n);
    end_time = chrono::high_resolution_clock::now();
    auto parallel_sort_time = chrono::duration_cast<chrono::microseconds>(end_time - start_time).count();

    // Print the execution times of the sequential and parallel bubble sort
    cout << "Sequential bubble sort time: " << sequential_sort_time << " microseconds" << endl;
    print_array(arr, n);

    cout << "\nParallel bubble sort time: " << parallel_sort_time << " microseconds" << endl;
    print_array(arr, n);

    // Free the memory allocated for the arrays
    delete[] arr;
    delete[] arr_copy;
}

void test_merge_sort_performance(int n)
{
    int *arr = new int[n];
    int *arr_copy = new int[n];

    // Initialize array with random values
    srand(time(NULL));
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 1000;
        arr_copy[i] = arr[i];
    }

    auto start = chrono::high_resolution_clock::now();
    sequential_merge_sort(arr, 0, n - 1);
    auto end = chrono::high_resolution_clock::now();
    std::cout << "Sequential merge sort took " << chrono::duration_cast<chrono::microseconds>(end - start).count() << "microseconds\n";
    print_array(arr, n);

    start = chrono::high_resolution_clock::now();
    parallel_merge_sort(arr_copy, 0, n - 1);
    end = chrono::high_resolution_clock::now();
    std::cout << "\nParallel merge sort took " << chrono::duration_cast<chrono::microseconds>(end - start).count() << "microseconds\n";
    print_array(arr_copy, n);

    delete[] arr;
    delete[] arr_copy;
}
int main()
{
    int n = 5;
    test_bubble_sort_performance(n);
    cout << "\n------------------\n";
    test_merge_sort_performance(n);
    return 0;
}
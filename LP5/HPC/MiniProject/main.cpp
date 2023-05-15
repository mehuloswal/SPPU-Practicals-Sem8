#include <iostream>
#include <vector>
#include <mpi.h>

// Helper function to swap two elements
void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

// Partition function for Quicksort
int partition(std::vector<int> &arr, int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Quicksort function
void quicksort(std::vector<int> &arr, int low, int high)
{
    if (low < high)
    {
        int pivotIndex = partition(arr, low, high);
        quicksort(arr, low, pivotIndex - 1);
        quicksort(arr, pivotIndex + 1, high);
    }
}

int main(int argc, char *argv[])
{
    MPI_Init(&argc, &argv);

    int worldSize, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &worldSize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::vector<int> arr;
    int n;
    if (rank == 0)
    {
        int elements[] = {9, 3, 1, 7, 5, 6, 2, 8, 4};
        int numElements = sizeof(elements) / sizeof(elements[0]);
        arr.resize(numElements);
        for (int i = 0; i < numElements; i++)
        {
            arr[i] = elements[i];
        }
        n = arr.size();
    }

    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    arr.resize(n);

    MPI_Bcast(arr.data(), n, MPI_INT, 0, MPI_COMM_WORLD);

    quicksort(arr, 0, n - 1);

    // Gather sorted subarrays to the root process
    std::vector<int> sortedArr(n);
    MPI_Gather(arr.data(), n, MPI_INT, sortedArr.data(), n, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        std::cout << "Sorted Array: ";
        for (int i = 0; i < n; i++)
        {
            std::cout << sortedArr[i] << " ";
        }
        std::cout << std::endl;
    }

    MPI_Finalize();
    return 0;
}

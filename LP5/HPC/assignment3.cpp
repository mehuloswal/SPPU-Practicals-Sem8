#include <iostream>
#include <cmath>
#include <chrono>
#include <limits>
#include <omp.h>

using namespace std;

const int ARRAY_SIZE = 100000000;

int main()
{
    double *array = new double[ARRAY_SIZE];
    double min = numeric_limits<double>::max();
    double max = numeric_limits<double>::min();
    double sum = 0.0;
    double avg = 0.0;

    // Initialize array with random values
    for (int i = 0; i < ARRAY_SIZE; ++i)
    {
        array[i] = rand();
    }

    // Sequential version
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < ARRAY_SIZE; ++i)
    {
        if (array[i] < min)
        {
            min = array[i];
        }
        if (array[i] > max)
        {
            max = array[i];
        }
        sum += array[i];
    }
    avg = sum / ARRAY_SIZE;
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_seconds = end - start;

    cout << "Sequential version:" << endl;
    cout << "Min: " << min << endl;
    cout << "Max: " << max << endl;
    cout << "Sum: " << sum << endl;
    cout << "Average: " << avg << endl;
    cout << "Elapsed time: " << elapsed_seconds.count() << "s" << endl;

    // Parallel version using OpenMP
    min = numeric_limits<double>::max();
    max = numeric_limits<double>::min();
    sum = 0.0;
    avg = 0.0;

    start = chrono::high_resolution_clock::now();
#pragma omp parallel for reduction(min : min) reduction(max : max) reduction(+ : sum)
    for (int i = 0; i < ARRAY_SIZE; ++i)
    {
        if (array[i] < min)
        {
            min = array[i];
        }
        if (array[i] > max)
        {
            max = array[i];
        }
        sum += array[i];
    }
    avg = sum / ARRAY_SIZE;
    end = chrono::high_resolution_clock::now();
    elapsed_seconds = end - start;

    cout << "Parallel version:" << endl;
    cout << "Min: " << min << endl;
    cout << "Max: " << max << endl;
    cout << "Sum: " << sum << endl;
    cout << "Average: " << avg << endl;
    cout << "Elapsed time: " << elapsed_seconds.count() << "s" << endl;

    delete[] array;
    return 0;
}

// reduction(min : min): This reduction clause specifies that a reduction operation should be applied to the variable min during the parallel execution. The reduction operation in this case is min, which means the minimum value across all threads will be computed and stored in the variable min. Each thread will have its own private copy of min, and the final result will be obtained by combining the minimum values from all threads.

// reduction(max : max): This reduction clause specifies that a reduction operation should be applied to the variable max during the parallel execution. The reduction operation in this case is max, which means the maximum value across all threads will be computed and stored in the variable max. Similar to the previous clause, each thread will have its own private copy of max, and the final result will be obtained by combining the maximum values from all threads.

// reduction(+ : sum): This reduction clause specifies that a reduction operation should be applied to the variable sum during the parallel execution. The reduction operation in this case is +, which means the sum of values across all threads will be computed and stored in the variable sum. Again, each thread will have its own private copy of sum, and the final result will be obtained by summing the values from all threads.
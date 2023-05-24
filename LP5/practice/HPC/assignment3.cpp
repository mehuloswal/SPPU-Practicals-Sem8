#include <iostream>
#include <omp.h>
#include <chrono>
#include <limits>
#include <cmath>

using namespace std;

const int ARRAY_SIZE = 100000;

void sequential(double arr[], double min, double max, double avg, double sum)
{
    auto start = chrono::high_resolution_clock::now();
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        if (arr[i] < min)
        {
            min = arr[i];
        }
        if (arr[i] > max)
        {
            max = arr[i];
        }
        sum += arr[i];
    }
    avg = sum / ARRAY_SIZE;
    auto end = chrono::high_resolution_clock::now();
    double elapsed_time = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Sequential version:" << endl;
    cout << "Min: " << min << endl;
    cout << "Max: " << max << endl;
    cout << "Sum: " << sum << endl;
    cout << "Average: " << avg << endl;
    cout << "Elapsed time: " << elapsed_time << endl;
}
void parallel(double arr[], double min, double max, double avg, double sum)
{

    auto start = chrono::high_resolution_clock::now();
#pragma omp parallel for reduction(min : min) reduction(max : max) reduction(+ : sum)
    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        if (arr[i] < min)
        {
            min = arr[i];
        }
        if (arr[i] > max)
        {
            max = arr[i];
        }
        sum += arr[i];
    }
    avg = sum / ARRAY_SIZE;
    auto end = chrono::high_resolution_clock::now();
    double elapsed_time = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Parallel version:" << endl;
    cout << "Min: " << min << endl;
    cout << "Max: " << max << endl;
    cout << "Sum: " << sum << endl;
    cout << "Average: " << avg << endl;
    cout << "Elapsed time: " << elapsed_time << endl;
}

int main()
{
    double *array = new double[ARRAY_SIZE];
    double max = numeric_limits<double>::min();
    double min = numeric_limits<double>::max();
    double sum = 0.0;
    double avg = 0.0;

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        array[i] = rand() % 100;
    }
    sequential(array, min, max, avg, sum);
    parallel(array, min, max, avg, sum);

    return 0;
}
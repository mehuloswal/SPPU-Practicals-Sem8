#include <iostream>
#include <math.h>
#include <functional>
// #include <stdlib.h> /* srand, rand */
// #include <time.h>   /* time */

__global__ void vecAdd(double *a, double *b, double *c, int n)
{
    int id = blockIdx.x * blockDim.x + threadIdx.x;
    if (id < n)
        c[id] = a[id] + b[id];
}

int main()
{
    int n = 10;

    double *h_a;
    double *h_b;
    double *h_c;

    double *d_a;
    double *d_b;
    double *d_c;

    size_t bytes = n * sizeof(double);

    h_a = (double *)malloc(bytes);
    h_b = (double *)malloc(bytes);
    h_c = (double *)malloc(bytes);

    cudaMalloc(&d_a, bytes);
    cudaMalloc(&d_b, bytes);
    cudaMalloc(&d_c, bytes);

    for (int i = 0; i < n; i++)
    {
        h_a[i] = i;
        h_b[i] = 2 * i;
    }

    cudaMemcpy(d_a, h_a, bytes, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, bytes, cudaMemcpyHostToDevice);

    int blocksize, gridsize;

    blocksize = 1024;
    gridsize = (int)ceil((float)n / blocksize);

    vecAdd<<gridsize,blocksize>>(d_a,d_b,d_c,n);

    cudaMemcpy(h_c,d_c,bytes,cudaMemcpyDeviceToHost);
    

}
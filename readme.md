# Semester 8

SPPU Computer Engineering 2019 Pattern Final Year-Sem 2/Sem 8 Assignments. If this repo helped you, do star it! :)

## HPC Practicals

### For running openmp programs hit commands:-

C++ : `g++ filename.cpp -fopenmp` and `./a.out`

C : `gcc filename.cpp -fopenmp` and `./a.out`

### To run CUDA programs on Collab, follow these steps:

1. [Go to Google Collab](https://colab.research.google.com)
2. Create a new Notebook(.ipynb file).
3. Click on Runtime and then change runtime type to GPU.
4. Now run `!pip install git+https://github.com/andreinechaev/nvcc4jupyter.git` in a cell.
5. On a new cell run `%load_ext nvcc_plugin`
6. Test the following code

```
%%cu
#include <iostream>
int main(){
  std::cout << "Hello World\n";
  return 0;
}
```

7. Remember to add `%%cu` before writing the C++ code for every CUDA program. CUDA is now set.

[Click here for detailed steps](https://www.geeksforgeeks.org/how-to-run-cuda-c-c-on-jupyter-notebook-in-google-colaboratory/)

### For running CUDA programms using nvcc:-

First install nvcc on your nvidia supported machine using

```bash
$> sudo apt install nvidia-cuda-toolkit
```

Then use these commands to compile and execute the programs

```bash
$> nvcc filename.cu -o output_file
$> ./output_file
```

### For running mpi programs hit commands:-

`mpic++ parallel_quicksort.cpp -o parallel_quicksort`
`mpiexec -n 4 ./parallel_quicksort`

Contributed by :
[Mehul Oswal](https://github.com/mehuloswal), [Burhanuddin Merchant](https://github.com/burhanuddinmerchant), [Rohin Bhat](https://github.com/RohinBhat)

#include <chrono>
#include "taco.h"
#include "utils.hpp"

using namespace std;
using namespace taco;

template <class TYPE>
void spspmm(int* a_rows, int* a_columns, TYPE* a_values, int a_nnz, int a_row_counts
, int a_column_counts, int* b_rows, int* b_columns, TYPE* b_values, int b_nnz, int b_row_counts, int b_column_counts,
std::string &result)
{
    double time_converting_scale = 1000000000.;

    // init A
    Tensor<int> A({a_row_counts, a_column_counts}, Format({Dense,Sparse}));
    for (int i = 0; i < a_nnz;i++){
        A.insert({a_rows[i],a_columns[i]},a_values[i]);
    }

    // init B
    Tensor<int> B({b_row_counts, b_column_counts}, Format({Dense,Sparse}));
    for (int i = 0; i < b_nnz;i++){
        B.insert({b_rows[i],b_columns[i]},b_values[i]);
    }


    // Define res
    Tensor<int> res({a_row_counts, b_column_counts}, Format({Dense,Sparse}));

    IndexVar i, j, k;
    res(i,j) = A(i,k) * B(k,j);
    res.compile();
    // timing the computation time for SparseSparseMatrixMultiplication
    double computation_time = 0;
    auto start = std::chrono::high_resolution_clock::now();
    // assemble and computation
    res.assemble();
    res.compute();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    computation_time = (double)duration.count();

    result = "Computation time: " + std::to_string(computation_time) + " nanoseconds";
}

int main(int argc, char **argv)
{
    // double computation_time = spspmm<int, float>(5, 5, 5);
    // cout << "Computation time: " << computation_time << " (s)" << endl;
    driver("../artifacts/matrices/",spspmm<int>);
    return 0;
}
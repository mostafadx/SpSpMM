

#include <iostream>
#include <string>
#include <algorithm>
#include <chrono>
#include "linalg.hpp"
#include "utils.hpp"

using namespace std;

template <class KEY, class TYPE>
void spspmm(int* a_rows, int* a_columns, TYPE* a_values, int a_nnz, int a_row_counts
, int a_column_counts, int* b_rows, int* b_columns, TYPE* b_values, int b_nnz, int b_row_counts, int b_column_counts,
std::string &result)
{
    
    cout << a_nnz << endl;
    cout << b_nnz << endl;
    cout << a_row_counts << endl;
    cout << b_column_counts << endl;


    double time_converting_scale = 1000000000.;


    SPDB::HashMap A(a_row_counts, std::max(1,(a_nnz/a_row_counts)));
    SPDB::HashMap B(b_row_counts, std::max(1,(b_nnz/b_row_counts)));

    // initializing A
    for (size_t c = 0; c < a_nnz; ++c)
    {
        struct SPDB::key k;
        k.i = a_rows[c];
        k.j = a_columns[c];
        A.put(k,a_values[c]);
    }

    // initializing B
    for (size_t c = 0; c < b_nnz; ++c)
    {
        struct SPDB::key k;
        k.i = b_rows[c];
        k.j = b_columns[c];
        B.put(k,b_values[c]);
    }

    // initializing res
    SPDB::HashMap res(a_row_counts, std::max(1,(a_nnz/b_row_counts)));
    
    // timing the computation time for SparseSparseMatrixMultiplication
    double computation_time = 0;
    auto start = std::chrono::high_resolution_clock::now();
    opSpSpMM(a_row_counts, A, B, res);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    computation_time = (double)duration.count();

    result = "Computation time: " + std::to_string(computation_time) + " nanoseconds";

}

int main(int argc, char **argv)
{
    driver("../artifacts/matrices/",spspmm<int, int>);
    return 0;
}

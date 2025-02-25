

#include <iostream>
#include <string>

#include <chrono>
#include "linalg.hpp"
#include "utils.hpp"

using namespace std;

template <class KEY, class TYPE>
void spspmm(int* a_rows, int* a_columns, TYPE* a_values, int a_nnz, int a_row_counts
, int a_column_counts, int* b_rows, int* b_columns, TYPE* b_values, int b_nnz, int b_row_counts, int b_column_counts,
std::string &result)
{
    
    // cout << a_nnz << endl;
    // cout << b_nnz << endl;
    // cout << a_row_counts << endl;
    // cout << b_column_counts << endl;


    double time_converting_scale = 1000000000.;

    //  allocation array of flat_map to store the sparse matrix of (I,K) dimension
    arr_type<boostFlatMap<KEY, TYPE>> A = (boostFlatMap<KEY, TYPE> *)(::operator new(sizeof(boostFlatMap<KEY, TYPE>) * a_row_counts));
    // std::vector<boostFlatMap<int, int>> A(a_row_counts);
    arr_type<boostFlatMap<KEY, TYPE>> B = (boostFlatMap<KEY, TYPE> *)(::operator new(sizeof(boostFlatMap<KEY, TYPE>) * b_row_counts));

    // initializing A
    for (size_t i = 0; i < a_row_counts; ++i)
    {
        new (&A[i]) boostFlatMap<KEY, TYPE>();
        boostFlatMap<KEY, TYPE> temp;

        for (size_t j = 0; j < a_nnz; ++j)
        {
            if (a_rows[j] == i)
            {
                temp[a_columns[j]] = a_values[j];
            }
        }
        A[i] = temp;
    }

    // initializing B
    for (size_t i = 0; i < b_row_counts; ++i)
    {
        new (&B[i]) boostFlatMap<KEY, TYPE>();
        boostFlatMap<KEY, TYPE> temp;

        for (size_t j = 0; j < b_nnz; ++j)
        {
            if (b_rows[j] == i)
                temp.insert({b_columns[j], b_values[j]});
        }
        B[i] = temp;
    }

    arr_type<boostFlatMap<KEY, TYPE>> res = (boostFlatMap<KEY, TYPE> *)(::operator new(sizeof(boostFlatMap<KEY, TYPE>) * a_row_counts));
    
    // timing the computation time for SparseSparseMatrixMultiplication
    double computation_time = 0;
    auto start = std::chrono::high_resolution_clock::now();
    SpSpMM(a_row_counts, A, B, res);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
    computation_time = (double)duration.count();
    
    

    // print A,C and res
    // cerr << "------- Matrix A: \n";
    // printSpMat(A, a_row_counts);
    // cerr << "------- Matrix B: \n";
    // printSpMat(B, b_row_counts);
    // cerr << "------- Matrix res: \n";
    // printSpMat(res, a_row_counts);

    // memory cleaning
    for (size_t i = 0; i < a_row_counts; ++i)
    {
        A[i].~flat_map<KEY, TYPE>(); // Call the destructor
    }
    for (size_t i = 0; i < b_row_counts; ++i)
    {
        B[i].~flat_map<KEY, TYPE>(); // Call the destructor
    }
    for (size_t i = 0; i < a_row_counts; ++i)
    {
        res[i].~flat_map<KEY, TYPE>(); // Call the destructor
    }
    ::operator delete(A);
    ::operator delete(B);
    ::operator delete(res);

    result = "Computation time: " + std::to_string(computation_time) + " nanoseconds";
    // return computation_time / time_converting_scale;
}

int main(int argc, char **argv)
{
    driver("../artifacts/matrices/",spspmm<int, int>);
    return 0;
}

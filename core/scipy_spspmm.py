import numpy as np
from scipy.sparse import csr_matrix
import cProfile
import pstats
from pstats import SortKey
import io
import time
import sys
from pathlib import Path

target_dir = Path(__file__).resolve().parent.parent.joinpath('shared/runtime')
sys.path.append(str(target_dir))
import utils

ENABLE_PROFILE = False

def spspmm(a_rows, a_columns, a_values, a_nnz, a_row_counts,
                        a_column_counts, b_rows, b_columns, b_values,
                        b_nnz, b_row_counts, b_column_counts):
    
    # init A
    A = csr_matrix((a_values, (a_rows, a_columns)), shape=(a_row_counts, a_column_counts))

    # init B
    B = csr_matrix((b_values, (b_rows, b_columns)), shape=(b_row_counts, b_column_counts))
    
    # measure computation
    start = time.time()
    
    if ENABLE_PROFILE:
        prof = cProfile.Profile()
        prof.enable()
    
    C = A @ B
    
    if ENABLE_PROFILE:
        prof.disable()
        s = io.StringIO()
        sortby = SortKey.CUMULATIVE
        ps = pstats.Stats(prof, stream=s).sort_stats(sortby)
        ps.print_stats()
        print(s.getvalue())       
    
    end = time.time()


    non_zero_count_a = A.count_nonzero()
    print("info: Number of non-zero elements A:", non_zero_count_a)

    non_zero_count_b = B.count_nonzero()
    print("info: Number of non-zero elements B:", non_zero_count_b)

    non_zero_count_c = C.count_nonzero()
    print("info: Number of non-zero elements C:", non_zero_count_c)

    return "Computation time: " + str((end-start)*(10**9)) + ' nanoseconds'

utils.driver('../artifacts/matrices/',spspmm)
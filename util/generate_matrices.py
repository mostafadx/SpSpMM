import random
import numpy as np


matrix_diminsions = [
                     ((250000,250000),(250000,250000)), ((250000,250000),(250000,250000)), ((250000,250000),(250000,250000)),
                     ((200000,200000),(200000,200000)), ((200000,200000),(200000,200000)), ((200000,200000),(200000,200000)),
                     ((150000,150000),(150000,150000)), ((150000,150000),(150000,150000)), ((150000,150000),(150000,150000)),
                     ((75000,75000),(75000,75000)), ((75000,75000),(75000,75000)), ((75000,75000),(75000,75000)),
                     ((40000,40000),(40000,40000)), ((40000,40000),(40000,40000)), ((40000,40000),(40000,40000)),
                     ((20000,20000),(20000,20000)), ((20000,20000),(20000,20000)), ((20000,20000),(20000,20000)),
                     ((10000,10000),(10000,10000)), ((10000,10000),(10000,10000)), ((10000,10000),(10000,10000))]

sparcity_factors = [(0.00001,0.00001),(0.000001,0.000001),(0.0000001,0.0000001),
                    (0.00001,0.00001),(0.000001,0.000001),(0.0000001,0.0000001),
                    (0.00001,0.00001),(0.000001,0.000001),(0.0000001,0.0000001),
                    (0.00001,0.00001),(0.000001,0.000001),(0.0000001,0.0000001),
                    (0.00001,0.00001),(0.000001,0.000001),(0.0000001,0.0000001),
                    (0.00001,0.00001),(0.000001,0.000001),(0.0000001,0.0000001),
                    (0.00001,0.00001),(0.000001,0.000001),(0.0000001,0.0000001)]

def create_sparse_matrix(dims,sparcity_factor):
    rows_count, cols_count = dims
    total_elements = rows_count * cols_count
    non_zero_elements = int(total_elements * sparcity_factor)
    # Initialize empty lists for rows, columns
    rows, columns = [], []
    seen_pairs = set()
    
    # Generate unique row-column pairs
    while len(seen_pairs) < non_zero_elements:
        r = np.random.randint(0, rows_count)
        c = np.random.randint(0, cols_count)
        if (r, c) not in seen_pairs:
            seen_pairs.add((r, c))
            rows.append(r)
            columns.append(c)

    values = np.random.randint(1, 100, size=len(seen_pairs))
    
    return rows,columns,values

for i in range(len(matrix_diminsions)):
    dims1,dims2 = matrix_diminsions[i]
    spf1,spf2 = sparcity_factors[i]
    
    A = create_sparse_matrix(dims1,spf1)
    B = create_sparse_matrix(dims2,spf2)
    
    file_name = str(matrix_diminsions[i]) + ' ' + str(sparcity_factors[i]) + '.txt'
    with open('../artifacts/matrices/'+file_name,'w+') as file:
        file.write('a_rows:[' +  ' '.join(str(num) for num in A[0]) +']\n')
        file.write('a_columns:['+' '.join(str(num) for num in A[1])+']\n')
        file.write("a_values:["+' '.join(str(num) for num in A[2])+']\n')
        file.write('b_rows:['+' '.join(str(num) for num in B[0])+']\n')
        file.write('b_columns:['+' '.join(str(num) for num in B[1])+']\n')
        file.write("b_values:["+' '.join(str(num) for num in B[2])+']\n')
    print("Created ", file_name)
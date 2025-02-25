import os
import re
from pathlib import Path



def parse_filename(filename):
    print(f"Processing Filename: {filename}")
    # Extracting matrix dimensions and sparsity factor using regular expressions
    match = re.match(r"\(\((\d+), (\d+)\), \((\d+), (\d+)\)\) \(([\de.-]+), ([\de.-]+)\)", filename)
    if match:
        a_row_counts, a_column_counts, b_row_counts, b_column_counts, a_sparsity_factor, b_sparsity_factor = match.groups()
        # Convert integers and floats
        a_row_counts = int(a_row_counts)
        a_column_counts = int(a_column_counts)
        b_row_counts = int(b_row_counts)
        b_column_counts = int(b_column_counts)
        a_sparsity_factor = float(a_sparsity_factor)
        b_sparsity_factor = float(b_sparsity_factor)
        
        print(f"A Row Counts: {a_row_counts}, A Column Counts: {a_column_counts}")
        print(f"B Row Counts: {b_row_counts}, B Column Counts: {b_column_counts}")
        print(f"A Sparsity Factor: {a_sparsity_factor}, B Sparsity Factor: {b_sparsity_factor}")
        return a_row_counts, a_column_counts, b_row_counts, b_column_counts, a_sparsity_factor, b_sparsity_factor
    else:
        print("Filename format is incorrect.")
        raise ValueError("Filename format is incorrect.")

def extract_matrix_data(file_path):
    # Initialize lists to hold matrix data
    a_rows, a_columns, a_values = [], [], []
    b_rows, b_columns, b_values = [], [], []

    with open(file_path, 'r') as file:
        for line in file:
            
            if line.startswith("a_rows:["):
                a_rows = [int(x) for x in line[len('a_rows:['):-2].split(' ')]
            elif line.startswith("a_columns:["):
                a_columns = [int(x) for x in line[len('a_columns:['):-2].split(' ')]
            elif line.startswith("a_values:["):
                a_values = [int(x) for x in line[len('a_values:['):-2].split(' ')]
            elif line.startswith("b_rows:["):
                b_rows = [int(x) for x in line[len('b_rows:['):-2].split(' ')]
            elif line.startswith("b_columns:["):
                b_columns = [int(x) for x in line[len('b_columns:['):-2].split(' ')]
            elif line.startswith("b_values:["):
                b_values = [int(x) for x in line[len('b_values:['):-2].split(' ')]

    return a_rows, a_columns, a_values, b_rows, b_columns, b_values

def driver(path_to_directory, process_matrix_data):
    for entry in Path(path_to_directory).iterdir():
        if entry.is_file():
            filename = entry.name
            try:
                a_row_counts, a_column_counts, b_row_counts, b_column_counts, a_sparsity_factor, b_sparsity_factor = parse_filename(filename)
                print(f"A Row Counts: {a_row_counts}")
                print(f"A Column Counts: {a_column_counts}")
                print(f"B Row Counts: {b_row_counts}")
                print(f"B Column Counts: {b_column_counts}")
                print(f"A Sparsity Factor: {a_sparsity_factor}")
                print(f"B Sparsity Factor: {b_sparsity_factor}")

                a_rows, a_columns, a_values, b_rows, b_columns, b_values = extract_matrix_data(entry)
                a_nnz, b_nnz = len(a_values), len(b_values)

                # Placeholder for result handling
                result = process_matrix_data(a_rows, a_columns, a_values, a_nnz, a_row_counts, 
                                    a_column_counts, b_rows, b_columns, b_values, 
                                    b_nnz, b_row_counts, b_column_counts)
                with open('../artifacts/results/results.txt','a') as file:
                    file.write("Result: " + result + '\n')
                    file.write(f"A Sparsity Factor: {a_sparsity_factor}"+ '\n')
                    file.write(f"B Sparsity Factor: {b_sparsity_factor}"+ '\n')
                    file.write(f"A Rows: {a_row_counts}"+ '\n')
                    file.write(f"A Columns: {a_column_counts}"+ '\n')
                    file.write(f"B Rows: {b_row_counts}"+ '\n')
                    file.write(f"B Columns: {b_column_counts}"+ '\n')
                    file.write('--------------------------------------' + '\n')
                print(result)
                print(f"Processed: {filename}")
                
            except ValueError as e:
                print(f"Error processing file {filename}: {e}")
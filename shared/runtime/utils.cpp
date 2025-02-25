#include "utils.hpp"

void parse_filename(const std::string& filename, int& a_row_counts, int& a_column_counts, 
                    int& b_row_counts, int& b_column_counts, float& a_sparsity_factor, float &b_sparsity_factor) {
    
    std::cout << "Processing Filename: " << filename << std::endl;
    std::stringstream ss(filename);
    char ignore; // Used to ignore characters that are not needed
    // Example filename: ((12, 12), (12, 12)) (1, 1)
    // Extracting matrix dimensions and sparsity factor
    ss >> ignore; // Ignore '('
    ss >> ignore; // Ignore '('
    ss >> a_row_counts;
    ss >> ignore; // Ignore ','
    ss >> a_column_counts;
    ss >> ignore; // Ignore ')'
    ss >> ignore; // Ignore ','
    ss >> ignore; // Ignore '('
    ss >> b_row_counts;
    ss >> ignore; // Ignore ','
    ss >> b_column_counts;
    // Move past the rest until the sparsity factor
    while (ss >> ignore && ignore != ')'); // Move until the end of matrix dimensions section
    ss >> ignore; // Ignore ')'
    ss >> ignore; // Ignore '('
    ss >> a_sparsity_factor; // Finally, extract the sparsity factor
    ss >> ignore; // Ignore ','
    ss >> b_sparsity_factor;
    
}
static bool starts_with(const std::string& line, const std::string& prefix) {
    // Check if line starts with prefix
    return line.find(prefix) == 0;
}

static void extract_matrix_data(const std::string& file_path, 
                         std::vector<int>& a_rows, std::vector<int>& a_columns, std::vector<int>& a_values, 
                         std::vector<int>& b_rows, std::vector<int>& b_columns, std::vector<int>& b_values) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << file_path << std::endl;
        return;
    }

    std::string line;
    std::vector<int>* current_vector = nullptr;

    while (getline(file, line)) {
        if (starts_with(line, "a_rows:[")) {
            current_vector = &a_rows;
        } else if (starts_with(line, "a_columns:[")) {
            current_vector = &a_columns;
        } else if (starts_with(line, "a_values:[")) {
            current_vector = &a_values;
        } else if (starts_with(line, "b_rows:[")) {
            current_vector = &b_rows;
        } else if (starts_with(line, "b_columns:[")) {
            current_vector = &b_columns;
        } else if (starts_with(line, "b_values:[")) {
            current_vector = &b_values;
        } else {
            continue; // Skip any lines that don't match expected starting patterns.
        }

        // Extracting numbers from the current line
        std::string numbers = line.substr(line.find('[') + 1);
        numbers.pop_back(); // Remove the last character, which should be ']'
        std::istringstream stream(numbers);
        int number;
        while (stream >> number) {
            current_vector->push_back(number);
            if (stream.peek() == ',') stream.ignore();
        }
    }

    file.close();
}


void driver(const std::string& path_to_directory, ProcessMatrixDataFunc process_matrix_data) {
    try {
        for (const auto& entry : fs::directory_iterator(path_to_directory)) {
            if (entry.is_regular_file()) {
                int a_row_counts;
                int a_column_counts;
                int b_row_counts;
                int b_column_counts;
                float a_sparsity_factor;
                float b_sparsity_factor;
                std::string filename = entry.path().filename().string();
                std::string matrix_dimensions, sparcity_factor;
                std::string result;
                parse_filename(filename,a_row_counts,a_column_counts,b_row_counts,b_column_counts,a_sparsity_factor,b_sparsity_factor);
                
                // std::cout << "A Row Counts: " << a_row_counts << std::endl;
                // std::cout << "A Column Counts: " << a_column_counts << std::endl;
                // std::cout << "B Row Counts: " << b_row_counts << std::endl;
                // std::cout << "B Column Counts: " << b_column_counts << std::endl;
                // std::cout << "A Sparsity Factor: " << a_sparsity_factor << std::endl; 
                // std::cout << "B Sparsity Factor: " << b_sparsity_factor << std::endl; 

                // Assuming a mechanism to extract A and B matrices' data from the filename or content
                std::vector<int> a_rows, a_columns, a_values, b_rows, b_columns, b_values;

                // Example call to a fictional function to fill a_rows, a_columns, a_values, etc.
                extract_matrix_data(entry.path(), a_rows, a_columns, a_values, b_rows, b_columns, b_values);
                // Further processing required here to distinguish between A and B matrices
                
                // Call the provided function with these parameters
                // Assuming a_nnz, b_nnz, a_row_counts, etc. are determined correctly
                int a_nnz = a_values.size(); // Number of non-zero elements in matrix A
                int b_nnz = b_values.size(); // Number of non-zero elements in matrix B

                process_matrix_data(a_rows.data(), a_columns.data(), a_values.data(), a_nnz, a_row_counts, 
                a_column_counts, b_rows.data(), b_columns.data(), b_values.data(), 
                b_nnz, b_row_counts, b_column_counts, result);

                std::cout << result << std::endl;
               // Prepare the output string with sparsity factors and row counts
                std::ostringstream oss;
                oss << "Result: " << result << "\n";
                oss << "A Sparsity Factor: " << a_sparsity_factor << "\n";
                oss << "B Sparsity Factor: " << b_sparsity_factor << "\n";
                oss << "A Rows: " << a_row_counts << "\n";
                oss << "A Columns: " << a_column_counts << "\n";
                oss << "B Rows: " << b_row_counts << "\n";
                oss << "B Columns: " << b_column_counts << "\n";
                oss << "--------------------------------------" << "\n";
                std::string output = oss.str();

                // Append the output string to results.txt
                std::ofstream ofs("../artifacts/results/results.txt", std::ios::app); // Open results.txt in append mode
                if (!ofs) {
                    std::cerr << "Failed to open results.txt for appending." << std::endl;
                } else {
                    ofs << output; // Append the formatted string
                    ofs.close(); // Close the file
                }              
                // Output the parsed values for confirmation
                std::cout << "Processed: " << filename << std::endl;
            }
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "General error: " << e.what() << std::endl;
    }
}
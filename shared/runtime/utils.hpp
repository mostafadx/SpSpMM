#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
namespace fs = std::filesystem;
typedef void (*ProcessMatrixDataFunc)(int*, int*, int*, int, int, int, int*, int*, int*, int, int, int,std::string&);

void driver(const std::string& path_to_directory, ProcessMatrixDataFunc process_matrix_data);
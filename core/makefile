# these optimization flags are passed to the compiler 
OPTS=-O3 -ffast-math -ftree-vectorize -mtune=native -std=c++17 

    
# Other compilation flags for baseline
LIB=-I../shared/runtime -I../shared/runtime/3rdparty/    
# TACO's compilation flags
TACOLIB=-I../shared -I../shared/runtime/3rdparty/taco/include -L../shared/runtime/3rdparty/taco/build/lib  

# To make sure that all computaions execute on a single core 
export OMP_NUM_THREADS=1
export MKL_NUM_THREADS=1
export OPENBLAS_NUM_THREADS=1
export VECLIB_MAXIMUM_THREADS=1
export NUMEXPR_NUM_THREADS=1


exe_path="./execution_files/"
matrices_path="../artifacts/matrices/"
plots_path="../artifacts/plots/"
results_path="../artifacts/results/"

clean:
	rm -f $(exe_path)*.exe
	rm -f $(matrices_path)*.txt
	rm -f $(plots_path)*.pdf
	rm -f $(results_path)*.txt

generate_matrices:
	python ../util/generate_matrices.py

generate_plots:
	python ../util/generate_plots.py

micro:
	clang++ $(OPTS) $(LIB) ./baseline_spspmm.cpp ../shared/runtime/utils.cpp -o $(exe_path)baseline_spspmm.exe
	clang++ -pthread $(OPTS) $(LIB) ./parallelized_baseline_spspmm.cpp ../shared/runtime/utils.cpp -o $(exe_path)parallelized_baseline_spspmm.exe
	clang++ $(OPTS) $(LIB) ./optimized_baseline_spspmm.cpp ../shared/runtime/utils.cpp -o $(exe_path)optimized_baseline_spspmm.exe
	clang++ $(OPTS) $(TACOLIB) $(LIB)  ./taco_spspmm.cpp ../shared/runtime/utils.cpp -o $(exe_path)taco_spspmm.exe -ltaco

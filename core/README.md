## Guide
### Run baseline
1. open terminal in this directory
2. execute ```./run.sh```

### Implementation
-   TACO
    - clone it to ```../shared/runtime/3rdparty/``` then build it as instructed at their GitHub page.
    - Add your implementation to ```taco_spspmm.cpp``` file
- SciPy
    - Add you implementation to ```scipy_spspmm.py```
- Benchmarking
    - For benchmarking, you are timing two sparse matrices multiplication, for different dimensions and sparsity. Therefore, you need to generate random matrices as inputs and time the computation-time.
- Optimization
    - You can change the code in ```baseline_spspmm.cpp``` for any possible optimization as well as changing function ```SpSpMM``` in ```../shared/runtime/linalg.hpp```. The only constrain is that the structure used for a matrix that is ```(dense,sparse)``` should be ```array``` of a ```map(dictionary)```.  
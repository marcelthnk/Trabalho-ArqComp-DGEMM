The compilation in Windows is: gcc -Wall -Wextra -O<i> -o dgemm_<j>k_O<i> .\windowsDGEMM.c
Where "i" is the number of the optimization (O0, O1, O2, O3) and "j" is the size of the matrix (1024, 2048, 4096, 8192)
The angle brackets "<>" must be removed.

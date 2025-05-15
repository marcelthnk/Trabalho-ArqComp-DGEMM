The compilation in Linux is: gcc -Wall -Wextra -Oi -o dgemm_jk_Oi linuxDGEMM.c
Where "i" in "-Oi" and "_Oi" is the number of the optimization (O0, O1, O2, O3) and "j" in "_jk" is the size of the matrix (1024, 2048, 4096, 8192)
Example: gcc -Wall -Wextra -O0 -o dgemm_1k_O0 linuxDGEMM.c
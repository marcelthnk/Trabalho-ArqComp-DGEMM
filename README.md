Chapter 2:
The compilation in Linux is: gcc -Oi -o dgemm_jk_Oi linuxDGEMM.c
Where "i" in "-Oi" and "_Oi" is the number of the optimization (O0, O1, O2, O3) and "j" in "_jk" is the size of the matrix (1024, 2048, 4096, 8192)
Example: gcc -Wall -Wextra -O3 -o dgemm_1k_O3 linuxDGEMM.c

Chapter 3:
The compilation in Linux is: gcc -O3 -mavx -o dgemm_jk_Oi linuxDGEMM.c
Where "i" in "-Oi" and "_Oi" is the number of the optimization (O0, O1, O2, O3) and "j" in "_jk" is the size of the matrix (1024, 2048, 4096, 8192)
Example: gcc -Wall -Wextra -O3 -mavx -o dgemm_1k_O3 linuxDGEMM.c

Chapter 4:
The compilation in Linux is: gcc -O3 -mavx2 -mfma -o dgemm_jk_Oi linuxDGEMM.c
Where "i" in "-Oi" and "_Oi" is the number of the optimization (O0, O1, O2, O3) and "j" in "_jk" is the size of the matrix (1024, 2048, 4096, 8192)
Example: gcc -Wall -Wextra -O3 -mavx2 -mfma -o dgemm_1k_O3 linuxDGEMM.c

Chapter 5:
The compilation in Linux is: gcc -O3 -mavx2 -mfma -o dgemm_jk_Oi linuxDGEMM.c
Where "i" in "-Oi" and "_Oi" is the number of the optimization (O0, O1, O2, O3) and "j" in "_jk" is the size of the matrix (1024, 2048, 4096, 8192)
Example: gcc -Wall -Wextra -O3 -mavx2 -mfma -o dgemm_1k_O3 linuxDGEMM.c


# Python script for running the executables

import subprocess 
# Library for executing an external program

for opt_num in range(4):
    # Getting the program path, if it is in the same directory then just put the name and the extension(.exe if in Windows)
    program_path = f"./dgemm_8k_O{opt_num}"

    print(f"Running dgemm_8k_O{opt_num}")
    
    # Creating a txt to store the time it took
    with open("times.txt", "a") as txt:
        # Running it 10 times 
        for i in range(10):

            # Printing to see which step of the loop it is 
            print(f"Running try: {i+1}")

            # Running the .exe, capturing the output(the output from the printf function), transforming the output into text, because the output would be in bytes
            result = subprocess.run(program_path, capture_output=True, text=True)

            # Writing the results to a txt, it is written "{(size of the matrix) (optimization flag) (time)\n}"
            txt.write(result.stdout)








"""
============================================================================
Group No     : A1
Team No      : 02
Team Members : Rishika Sur (002311001025)
             : Vidhi Mantry (002311001043)
             : Prama Ray (002311001033)

Date: 14th August, 2025

Assignment  : 3 - Parallel Matrix Multiplication in Python

Description :
    This program performs matrix multiplication between two large square
    matrices using parallel processing. The matrix elements are initialized 
    with random unsigned integers modulo a given value (mod).
    
    The matrix multiplication is divided into multiple chunks, which are 
    processed in parallel using Python's multiprocessing pool.

    The program also measures the time taken for the matrix multiplication 
    and prints the result if requested via command-line argument.
    
    The program uses multiprocessing to optimize the computation time 
    when dealing with large matrices.
    
    - Command-line arguments are handled.
    - Warning-free compilation.
    - Proper indentation and formatting.

Input  : 
    - dim (integer): Dimension of the square matrices (e.g., 3000)
    - numThreads (integer): Number of parallel threads (e.g., 4)
    - mod (integer): Modulo value for initializing matrices (e.g., 1000)
    - printSwitch (integer): Switch to control printing matrices (1: print, 0: don't print)

Output : 
    - Matrix A, Matrix B, and Result Matrix C (if printSwitch == 1)
    - Time taken for matrix multiplication

Before Execution run:
    pip install numpy 

Execution :
    python A1_02_3.py <dim> <numThreads> <mod> <printSwitch>
  

Timing Measurements for Matrix Multiplication (Dimension x Dimension, Mod Value)
  - Dimension: 3000
  - Mod Value: 1000
  - Number of Processes (1):  68.5151 seconds
  - Number of Processes (2):  34.8077 seconds
  - Number of Processes (4):  19.5800 seconds
  - Number of Processes (8):  14.7509 seconds     
    
Sample Input 1:  python3 A1_02_3.py 3000 1 1000 1

Sample Output 1:
    Matrix multiplication completed in 68.5151 seconds with 1 threads.
Matrix A:
[[375 820 289 ... 911 773 565]
 [645 965 863 ... 427 282  67]
 [438 405 176 ...  99 230 679]
 ...
 [235 908 554 ... 846 410 786]
 [ 88 370 119 ... 974 328 237]
 [348 402 100 ... 692 307 978]]
Matrix B:
[[772 845 501 ...  96 519  98]
 [134 474 569 ... 782 898 778]
 [ 57 882 612 ... 621 900 743]
 ...
 [802 416 282 ... 830 667 458]
 [330 533 946 ...   7 760 679]
 [323 350 710 ...  12 656 294]]
Result Matrix C:
[[775377476 756917141 768712588 ... 739095242 744195181 768762794]
 [787535992 783689502 775915121 ... 756845957 763547867 784160734]
 [758046656 748790884 760190275 ... 728319385 743098057 756768453]
 ...
 [753699816 740551497 756631050 ... 722547738 736763317 755885275]
 [762877570 752531759 760207448 ... 721373989 742452719 752396741]
 [780792132 768273327 778803567 ... 751784861 758276357 772179120]]

CPU Utilisation for Input 1:
Command: cpustat 
Output:
  %CPU   %USR   %SYS     PID S  CPU    Time Task
100.00 100.00   0.00   13183 R   11   1.04m python3
  1.00   0.00   1.00     572 S    9  41.12s [irq/162-rtw88_p]

  %CPU   %USR   %SYS     PID S  CPU    Time Task
100.00 100.00   0.00   13183 R   11   1.05m python3
  4.00   4.00   0.00    4807 S    4   2.23m /usr/share/code/code

  %CPU   %USR   %SYS     PID S  CPU    Time Task
100.00 100.00   0.00   13183 R   11   1.06m python3
  5.00   4.00   1.00    4807 S    4   2.23m /usr/share/code/code

Sample Input 2:  python3 A1_02_3.py 3000 2 1000 0

Sample Output 2: 
 Matrix multiplication completed in 34.8077 seconds with 2 threads.

CPU Utilisation for Input 2:
Command: cpustat 
Output:
  %CPU   %USR   %SYS     PID S  CPU    Time Task
100.00 100.00   0.00   14137 R   10  31.47s python3
100.00 100.00   0.00   14136 R    4  31.57s python3
  4.00   4.00   0.00    4807 S    9   2.56m /usr/share/code/code

  %CPU   %USR   %SYS     PID S  CPU    Time Task
100.00 100.00   0.00   14137 R   10  32.47s python3
100.00 100.00   0.00   14136 R    4  32.57s python3
  2.00   2.00   0.00    4807 S    9   2.56m /usr/share/code/code

  %CPU   %USR   %SYS     PID S  CPU    Time Task
100.00 100.00   0.00   14137 R   10  33.47s python3
100.00 100.00   0.00   14136 R    4  33.57s python3
  2.00   1.00   1.00    4807 S    9   2.56m /usr/share/code/code
  
Sample Input 3:  python3 A1_02_3.py 3000 4 1000 0

Sample Output 3: 
 Matrix multiplication completed in 19.5800 seconds with 4 threads.

CPU Utilisation for Input 3:
Command: cpustat 
Output:  
  %CPU   %USR   %SYS     PID S  CPU    Time Task
100.00 100.00   0.00   14656 R    3  16.74s python3
100.00 100.00   0.00   14654 R    4  16.94s python3
100.00 100.00   0.00   14655 R    6  16.85s python3
100.00 100.00   0.00   14653 R    9  17.01s python3
 18.00  17.00   1.00    4807 S   10   3.17m /usr/share/code/code 

  %CPU   %USR   %SYS     PID S  CPU    Time Task
100.00 100.00   0.00   14656 R    3  17.74s python3
100.00 100.00   0.00   14654 R    4  17.94s python3
100.00 100.00   0.00   14655 R    6  17.85s python3
100.00 100.00   0.00   14653 R    9  18.01s python3
 13.00  13.00   0.00    4807 S   10   3.17m /usr/share/code/code

Sample Input 4:  python3 A1_02_3.py 3000 8 1000 0

Sample Output 4: 
 Matrix multiplication completed in 14.7509 seconds with 8 threads.

CPU Utilisation for Input 4:
Command: cpustat 
Output:    

    %CPU   %USR   %SYS     PID S  CPU    Time Task
100.00 100.00   0.00   16188 R    3   3.62s python3
100.00 100.00   0.00   16185 R    0   3.88s python3
100.00 100.00   0.00   16192 R   10   3.13s python3
100.00 100.00   0.00   16187 R    9   3.70s python3
100.00 100.00   0.00   16191 R    6   3.27s python3
100.00 100.00   0.00   16190 R    5   3.41s python3
100.00 100.00   0.00   16189 R    7   3.52s python3
100.00 100.00   0.00   16186 R   11   3.80s python3
  7.00   7.00   0.00    4807 S   10   3.49m /usr/share/code/code
============================================================================
"""

import sys
import numpy as np
import multiprocessing as mp
import time

def initMatrix(dim, mod):
   
    #Initializes a square matrix of dimension `dim` with random unsigned integers modulo `mod`.
    
    return np.random.randint(0, mod, size=(dim, dim), dtype=np.uint32)


def workerMultiply(args):
    
    #Worker function to multiply a chunk of matrix A with matrix B.
    #Each worker processes a specific range of rows.
    A, B, rowsRange = args
    startRow, endRow = rowsRange
    subResult = np.dot(A[startRow:endRow], B)
    return (startRow, subResult)


def main():
   
    if len(sys.argv) != 5:
        print("Usage: python A1_02_3.py <dim> <numThreads> <mod> <printSwitch>")
        sys.exit(1)

    # Command-line arguments
    dim = int(sys.argv[1])
    numThreads = int(sys.argv[2])
    mod = int(sys.argv[3])
    printSwitch = int(sys.argv[4])

    # Initialize matrices A and B
    matrixA = initMatrix(dim, mod)
    matrixB = initMatrix(dim, mod)

    # Calculate row ranges for each process
    chunkSize = dim // numThreads
    rowsRanges = []
    for i in range(numThreads):
        startRow = i * chunkSize
        endRow = (i + 1) * chunkSize if i != numThreads - 1 else dim
        rowsRanges.append((startRow, endRow))

    # Start timing for matrix multiplication
    startTime = time.perf_counter()

    # Perform parallel computation using multiprocessing Pool
    with mp.Pool(processes=numThreads) as pool:
        results = pool.map(workerMultiply, [(matrixA, matrixB, rr) for rr in rowsRanges])

    # Combine the partial results into the final result matrix
    resultMatrix = np.zeros((dim, dim), dtype=np.uint32)
    for startRow, subMat in results:
        rows = subMat.shape[0]
        resultMatrix[startRow:startRow+rows, :] = subMat

    # End timing and calculate elapsed time
    endTime = time.perf_counter()
    elapsedTime = endTime - startTime

    # Print the time taken for multiplication
    print(f"Matrix multiplication completed in {elapsedTime:.4f} seconds with {numThreads} threads.")

    # Optionally print matrices A, B, and C
    if printSwitch == 1:
        print("Matrix A:")
        print(matrixA)
        print("Matrix B:")
        print(matrixB)
        print("Result Matrix C:")
        print(resultMatrix)


if __name__ == "__main__":
    main()

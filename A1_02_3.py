
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

Execution :
    python A1_02_3.py <dim> <numThreads> <mod> <printSwitch>

Example :  python A1_02_3.py 3000 4 1000 1

Sample Output:
    Matrix multiplication completed in 0.1234 seconds with 4 threads.
    Matrix A:
    [[…]]
    Matrix B:
    [[…]]
    Result Matrix C:
    [[…]]
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

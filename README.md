# Maze Problem

*Authors: Zhihao Shu, Junzhou Liu, Dongzhe Fan, Yang He*

This project focuses on solving the maze problem using various implementations of the Depth-First Search (DFS) algorithm. The content below provides instructions on decompression, generation of new maze matrices, compilation and execution of the code, and performance analysis.

## Getting Started

1. Decompress the provided ZIP file.
2. Copy and paste the extracted files onto your CIMS server.

## Folders and Files

- Pre-generated maze matrices: `maze10`, `maze100`, `maze500`, `maze800`, `maze1000`, `maze1500`, `maze2000`, and `maze3000`.
- Maze generator script: `maze_generator.py`.
- OpenMP implementation of the DFS_DoubleEnd algorithm: `xx_maze_double_dfs.cpp` (where `xx` is the maze size).
- Sequential implementation of the DFS algorithm: `xx_maze_nsingle_dfs.cpp`.

## Generating New Maze Matrices

1. Run the `maze_generator.py` file in the desired folder.
2. Modify the code to specify the desired maze size and file location to save the generated matrix.

## Compilation and Execution

1. SSH into the CIMS server: `ssh xxxxxx@access.cims.nyu.edu`.
2. SSH into Crunchy: `ssh xxxxxx@crunchy1.cims.nyu.edu`.
3. Load the GCC module: `module load gcc-9.2`.
4. Set the stack size limit: `ulimit -s 512000`.
5. Compile and run the OpenMP implementation of the DFS_DoubleEnd algorithm:
    ```
    g++ -fopenmp xx_maze_double_dfs.cpp -o xx_ddfs1
    time ./xx_ddfs1 maze_folder/maze1
    ```
6. Compile and run the sequential implementation of the DFS algorithm:
    ```
    g++ -fopenmp xx_maze_nsingle_dfs.cpp -o xx_ddfs2
    time ./xx_ddfs2 maze_folder/maze1
    ```
7. Compile and run the multi-core DFS algorithm with different core numbers:
    ```
    g++ -fopenmp maze_cores_dfs -o maze
    time ./maze maze_size maze_folder/maze1 core_number
    ```

## Performance Analysis

- Running time log (example for 1001x1001 maze): `1001*1001.txt`.
- Line chart generation script: `Charts.py`.
- Raw data from the experiment: `Multicore-data.csv`.

Firstly, you should decompress this zip, then you copy and paste the extracted files onto your cims server. 
You will find folders with pre-generated maze matrices, named maze10, maze100, maze500, maze800, maze1000, maze1500, maze2000, and maze3000, each containing a maze matrix of corresponding size. 
If you wish to generate new maze matrices, you can run the maze_generator.py file in each folder. However, you need to modify the code to specify the desired maze size and file location to save the generated matrix.
In addition, xx_maze_double_dfs.cpp is the code for our openmp implementation of the DFS_DoubleEnd algorithm, with "xx" indicating the corresponding maze size value, which should match the size of the generated maze matrix. 
You can modify the ROWS and COLS values in the code and recompile the code. We have already compiled the necessary files for our experiment, so you can call them directly. 
Similarly, xx_maze_nsingle _dfs.cpp is the code for our sequential implementation of the DFS algorithm, which has also been compiled. 
The compiled files for the DFS_DoubleEnd algorithm and DFS_Sequential algorithm are named xx_ddfs1 and xx_ddfs2, respectively.

The execution sequence, using a 1001*1001 maze as an example, is as follows:
1.	ssh xxxxxx@access.cims.nyu.edu
2.	ssh xxxxxx@crunchy1.cims.nyu.edu
3.	module load gcc-9.2
4.	ulimit -s 512000
5.	g++ -fopenmp 1001_maze_double_dfs.cpp -o 1001_ddfs1
6.	time ./ 1001_ddfs1 maze1000/maze1
7.	g++ -fopenmp 1001_maze_nsingle_dfs.cpp -o 1001_ddfs2
8.	time ./1001_ddfs2 maze1000/maze1
9.	g++ -fopenmp maze_cores_dfs -o maze
10.	time ./maze 1001 maze1000/maze1 1
11.	time ./maze 1001 maze1000/maze1 4

The 1001*1001.txt file is a log of the running times generated when testing maze1000/maze1 using different methods.
The Charts.py is the file that generates the two line charts in the report.
The Multicore-data.csv is the raw data from the experiment.
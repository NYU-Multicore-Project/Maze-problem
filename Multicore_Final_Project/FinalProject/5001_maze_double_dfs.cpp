#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <omp.h>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <stack>
#include <atomic>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;


#define ROWS 5001
#define COLS 5001


bool isValidCell(int x, int y, int rows, int cols, int **maze, int me) {
    return (x >= 0 && x < rows && y >= 0 && y < cols && maze[x][y] != 1 && maze[x][y] != me && maze[x][y] != 7);
}


/*
2 -- mark path as visited from start point

3 -- mart path as visited from end point

1 7 -- mark as wall

0 -- mark as path

clang++ -Xpreprocessor -fopenmp -I/usr/local/opt/libomp/include -L/usr/local/opt/libomp/lib  -lomp ./double_end.cpp -o double_end


*/

void dfs(int x, int y, int endX, int endY, int rows, int cols, int **maze, atomic<bool> &found, int me, int other) {
    if (found || !isValidCell(x, y, rows, cols, maze, me)) {
        return;
    }

    if ((x == endX && y == endY) || maze[x][y] == other) {
        found = true;
        maze[x][y] = 8;
        cout << "start from " << other << endl;

        return;
    }

    maze[x][y] = me; // Mark the cell as visited

    // Explore neighboring cells
    int dx[] = {-1, 0, 1, 0};
    int dy[] = {0, 1, 0, -1};
   

    for (int i = 0; i < 4; i++) {
        int newX = x + dx[i];
        int newY = y + dy[i];
        dfs(newX, newY, endX, endY, rows, cols, maze, found, me, other);
        if (found) break;
    }

    if (!found && maze[x][y] != other) {
        maze[x][y] = 7; // Mark the backtracking path cell as 7
    }
}



void printMaze(int** maze) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            cout << maze[i][j] << ' ';
        }
        cout << endl;
    }
}

void copyMaze(int src[][COLS], int dest[][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            dest[i][j] = src[i][j];
        }
    }
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <maze_file>\n", argv[0]);
        return 1;
    }

    // int ROWS = atoi(argv[2]);
    // int COLS = atoi(argv[2]);
    const char *file_name = argv[1];

    int **maze = new int*[ROWS];
    for (int i = 0; i < ROWS; i++) {
        maze[i] = new int[COLS];
    }

    FILE *file = fopen(file_name, "r");

    if (file == NULL) {
        printf("Error: Unable to open the file.\n");
        return 1;
    }

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            fscanf(file, "%d", &maze[i][j]);
        }
    }

    fclose(file);

    // // Print the maze to check if it's read correctly
    // for (int i = 0; i < ROWS; ++i) {
    //     for (int j = 0; j < COLS; ++j) {
    //         printf("%d ", maze[i][j]);
    //     }
    //     printf("\n");
    // }

    // printf("\n");

   
    // Set the start and end points
    int startX = 0, startY = 0, endX = ROWS - 1, endY = COLS - 1;


    atomic<bool> found(false);

    // Run the parallel DFS using OpenMP
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            dfs(startX, startY, endX, endY, ROWS, COLS, maze, found, 2, 3);
        }
        #pragma omp section
        {

            dfs(endX, endY, startX, startY, ROWS, COLS, maze, found, 3, 2);
        }
    }

    // Output the result
    if (found) {
        cout << "Path found!" << endl;

        // //Print the combined path
        // for (const auto &p : path1) {
        //     cout << "(" << p.first << ", " << p.second << ") -> ";
        //     //maze[p.first][p.second] =3;
        // }
        // cout << "END" << endl;

        // for (const auto &p : path2) {
        //     cout << "(" << p.first << ", " << p.second << ") -> ";
        //     //maze[p.first][p.second] = 4;
        // }
        // cout << "END" << endl;

        // printMaze(maze);

    } else {
        cout << "Path not found." << endl;
    }

    for (int i = 0; i < ROWS; i++) {
        delete[] maze[i];
    }
    delete[] maze;

    return 0;
}







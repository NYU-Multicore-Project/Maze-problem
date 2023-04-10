#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <omp.h>


bool solveMaze(int maze[][COLS] ,int x, int y, int ROWS, int COLS) {
    if (x == ROWS - 1 && y == COLS - 1) {
        maze[x][y] = 2;
        return true;
    }

    if (maze[x][y] == 0) {
        maze[x][y] = 2;

        // Move in four directions (up, down, left, right)
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};

        bool found = false;
        #pragma omp parallel for
        for (int i = 0; i < 4; ++i) {
            int newX = x + dx[i];
            int newY = y + dy[i];

            if (newX >= 0 && newX < ROWS && newY >= 0 && newY < COLS) {
                #pragma omp critical
                {
                    if (!found) {
                        found = solveMaze(maze, newX, newY, ROWS, COLS);
                    }
                }
            }
        }

        if (found) {
            return true;
        } else {
            maze[x][y] = 0;
        }
    }

    return false;
}


/*
clang -I/usr/local/Cellar/libomp/16.0.1/include -L/usr/local/Cellar/libomp/16.0.1/lib -Xpreprocessor -fopenmp -lomp maze-solver.c -o maze_solver
*/

int main(int argc, char** argv) {
    if (argc < 3) {
        printf("Usage: %s <maze_file> <size_count>\n", argv[0]);
        return 1;
    }

    int ROWS = atoi(argv[2]);
    int COLS = atoi(argv[2]);
    const char *file_name = argv[1];

    int maze[ROWS][COLS];
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

    // Print the maze to check if it's read correctly
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            printf("%d ", maze[i][j]);
        }
        printf("\n");
    }

    printf("\n");

    if (solveMaze(maze, 0, 0, ROWS, COLS)) {
        printf("Solution found:\n");
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                printf("%d ", maze[i][j]);
            }
            printf("\n");
        }
    } else {
        printf("No solution found.\n");
    }

    return 0;
}

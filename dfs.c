#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Maze size
#define ROWS 1001
#define COLS 1001

bool is_valid(int **maze, int row, int col) {
    if (row < 0 || row >= ROWS || col < 0 || col >= COLS) {
        return false;
    }
    if (maze[row][col] == 1 || maze[row][col] == 2) {
        return false;
    }
    return true;
}

bool solveMaze(int **maze, int row, int col) {
    if (row == ROWS - 1 && col == COLS - 1) {
        maze[row][col] = 2;
        return true;
    }

    if (!is_valid(maze, row, col)) {
        return false;
    }

    maze[row][col] = 2;

    int rows[] = {-1, 0, 1, 0};
    int cols[] = {0, 1, 0, -1};
    for (int i = 0; i < 4; i++) {
        if (solveMaze(maze, row + rows[i], col + cols[i])) {
            return true;
        }
    }

    maze[row][col] = 0;
    return false;
}


/*

clang dfs.c -o dfs
*/

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: %s <maze_file>\n", argv[0]);
        return 1;
    }

    // int ROWS = atoi(argv[2]);
    // int COLS = atoi(argv[2]);
    const char *file_name = argv[1];

    int **maze = malloc(ROWS * sizeof(int *));
    for (int i = 0; i < ROWS; i++) {
        maze[i] = malloc(COLS * sizeof(int));
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

    // Print the maze to check if it's read correctly
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            printf("%d ", maze[i][j]);
        }
        printf("\n");
    }

    printf("\n");

    if (solveMaze(maze, 0, 0)) {
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


    for (int i = 0; i < ROWS; i++) {
        free(maze[i]);
    }
    free(maze);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

int maze[MAX_SIZE][MAX_SIZE];
int solution[MAX_SIZE][MAX_SIZE];

int is_valid(int x, int y, int maze_size) {
    return x >= 0 && x < maze_size && y >= 0 && y < maze_size;
}

int solve_maze(int x, int y, int maze_size) {
    if (x == maze_size - 1 && y == maze_size - 1) {
        solution[x][y] = 1;
        return 1;
    }

    if (is_valid(x, y, maze_size) && maze[x][y] == 0) {
        solution[x][y] = 1;

        if (solve_maze(x + 1, y, maze_size))
            return 1;

        if (solve_maze(x, y + 1, maze_size))
            return 1;

        solution[x][y] = 0;
    }

    return 0;
}

void print_solution(int maze_size) {
    for (int i = 0; i < maze_size; i++) {
        for (int j = 0; j < maze_size; j++) {
            printf("%d ", solution[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int maze_size;
    char file_name[100];

    printf("Enter the maze file name: ");
    scanf("%s", file_name);

    FILE *f = fopen(file_name, "r");

    if (f == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    fscanf(f, "%d", &maze_size);

    for (int i = 0; i < maze_size; i++) {
        for (int j = 0; j < maze_size; j++) {
            fscanf(f, "%d", &maze[i][j]);
        }
    }

    fclose(f);

    if (solve_maze(0, 0, maze_size)) {
        printf("Solution:\n");
        print_solution(maze_size);
    } else {
        printf("No solution found.\n");
    }

    return 0;
}

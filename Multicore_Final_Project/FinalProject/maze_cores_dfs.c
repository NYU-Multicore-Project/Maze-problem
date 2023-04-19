#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define MAX_SIZE 100


int rows, cols; // Size of the maze
int start_row, start_col, end_row, end_col; // Start and end positions
int found = 0; // Flag to indicate if the end has been found

// Recursive DFS function
void dfs(int row, int col, int **visited, int **maze) {


    if (found) return; // If the end has been found, stop searching
    
    visited[row][col] = 1; // Mark current cell as visited
    
    if (row == end_row && col == end_col) { // If the end has been found, set the flag
        found = 1;
        return;
    }
    
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
                    // Check adjacent cells
            if ((i == 0 || j == 0) && i != j && row+i >= 0 && row+i < rows && col+j >= 0 && col+j < cols && !visited[row+i][col+j] && maze[row+i][col+j] == 0) {
                #pragma omp task
                {
                    visited[row+i][col+j] = 1;
                    dfs(row+i, col+j, visited, maze); // Recursively search adjacent cell
                    visited[row+i][col+j] = 0;
                }
                #pragma omp taskwait
            }

        }
    }


}

int main(int argc, char *argv[]) {

    FILE *fp;
    int maze_size = atoi(argv[1]);
    char* file_name = argv[2];
    int thread_num = atoi(argv[3]);

    if( (fp = fopen(file_name,"r")) == NULL ){
	    printf("Cannot open the file %s\n", file_name);
	    exit(1);
    }


    int** maze = (int**)malloc(maze_size*sizeof(int*));
    for(int i = 0; i < maze_size; i++){
        maze[i] = (int*)malloc(maze_size*sizeof(int));
    }

    int** visited = (int**)malloc(maze_size*sizeof(int*));
    for(int i = 0; i < maze_size; i++){
        visited[i] = (int*)malloc(maze_size*sizeof(int));
    }

    for(int i = 0; i < maze_size; i++){
        for (int j = 0; j < maze_size; j++)
        {
            fscanf(fp, "%d", &maze[i][j]);
        }
        
    }

    start_row = 0;
    start_col = 0;
    end_row = maze_size - 1;
    end_col = maze_size - 1;
    rows = maze_size;
    cols = maze_size;

    omp_set_num_threads(thread_num);
    
    // Start the search
    #pragma omp parallel
    {
        #pragma omp single nowait
        {
            dfs(start_row, start_col, visited, maze);
        }

    }

    
    // Print result
    if (found) {
        printf("Found a path from (%d,%d) to (%d,%d)\n", start_row, start_col, end_row, end_col);
    } else {
        printf("No path found from (%d,%d) to (%d,%d)\n", start_row, start_col, end_row, end_col);
    }
    
    return 0;
}
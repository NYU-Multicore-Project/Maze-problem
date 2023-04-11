#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAZE_WIDTH 1001
#define MAZE_HEIGHT 1001

typedef struct Node {
    int x, y;
    int g, h, f;
    struct Node *parent;
} Node;

Node *open_list[MAZE_WIDTH * MAZE_HEIGHT];
int open_list_count = 0;
Node *closed_list[MAZE_WIDTH * MAZE_HEIGHT];
int closed_list_count = 0;

int maze[MAZE_HEIGHT][MAZE_WIDTH];

void read_maze_from_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }

    for (int i = 0; i < MAZE_HEIGHT; i++) {
        for (int j = 0; j < MAZE_WIDTH; j++) {
            fscanf(file, "%d", &maze[i][j]);
        }
    }
    fclose(file);
}

int heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

int is_valid_move(int x, int y) {
    return x >= 0 && x < MAZE_WIDTH && y >= 0 && y < MAZE_HEIGHT && maze[y][x] == 0;
}

Node *get_lowest_f() {
    int min_idx = 0;
    for (int i = 1; i < open_list_count; i++) {
        if (open_list[i]->f < open_list[min_idx]->f) {
            min_idx = i;
        }
    }
    Node *node = open_list[min_idx];
    memmove(&open_list[min_idx], &open_list[min_idx + 1], (open_list_count - min_idx - 1) * sizeof(Node *));
    open_list_count--;
    return node;
}

void add_to_open_list(Node *node) {
    open_list[open_list_count++] = node;
}

void add_to_closed_list(Node *node) {
    closed_list[closed_list_count++] = node;
}

int is_in_list(Node **list, int count, int x, int y) {
    for (int i = 0; i < count; i++) {
        if (list[i]->x == x && list[i]->y == y) {
            return 1;
        }
    }
    return 0;
}

Node *find_path(int start_x, int start_y, int end_x, int end_y) {
    Node *start_node = (Node*)malloc(sizeof(Node));
    start_node->x = start_x;
    start_node->y = start_y;
    start_node->g = 0;
    start_node->h = heuristic(start_x, start_y, end_x, end_y);
    start_node->f = start_node->g + start_node->h;
    start_node->parent = NULL;

    add_to_open_list(start_node);

    while (open_list_count > 0) {
        Node *current_node = get_lowest_f();
        add_to_closed_list(current_node);

        if (current_node->x == end_x && current_node->y == end_y) {
            return current_node;
        }

        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};

        for (int i = 0; i < 4; i++) {
            int new_x = current_node->x + dx[i];
            int new_y = current_node->y + dy[i];

            if (!is_valid_move(new_x, new_y)) {
                continue;
            }

            if (is_in_list(closed_list, closed_list_count, new_x, new_y)) {
                continue;
            }

            int tentative_g = current_node->g + 1;

            if (!is_in_list(open_list, open_list_count, new_x, new_y)) {
                Node *new_node = (Node*)malloc(sizeof(Node));
                new_node->x = new_x;
                new_node->y = new_y;
                new_node->g = tentative_g;
                new_node->h = heuristic(new_x, new_y, end_x, end_y);
                new_node->f = new_node->g + new_node->h;
                new_node->parent = current_node;
                add_to_open_list(new_node);
            } else {
                for (int i = 0; i < open_list_count; i++) {
                    if (open_list[i]->x == new_x && open_list[i]->y == new_y) {
                        if (tentative_g < open_list[i]->g) {
                            open_list[i]->g = tentative_g;
                            open_list[i]->f = open_list[i]->g + open_list[i]->h;
                            open_list[i]->parent = current_node;
                        }
                        break;
                    }
                }
            }
        }
    }

    return NULL;
}

void print_path(Node *node) {
    if (node == NULL) {
        printf("No path found.\n");
        return;
    }

    int path_length = 0;
    Node *path[MAZE_WIDTH * MAZE_HEIGHT];

    while (node != NULL) {
        path[path_length++] = node;
        node = node->parent;
    }

    for (int y = 0; y < MAZE_HEIGHT; y++) {
        for (int x = 0; x < MAZE_WIDTH; x++) {
            int is_path = 0;
            for (int i = 0; i < path_length; i++) {
                if (path[i]->x == x && path[i]->y == y) {
                    is_path = 1;
                    break;
                }
            }

            if (is_path) {
                printf("X ");
            } else {
                printf("%d ", maze[y][x]);
            }
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <maze_file>\n", argv[0]);
        return 1;
    }

    read_maze_from_file(argv[1]);
    Node *path = find_path(0, 0, MAZE_WIDTH - 1, MAZE_HEIGHT - 1);
    print_path(path);

    return 0;
}


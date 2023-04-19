import random
import numpy as np


def generate_maze(rows, cols):
    maze = np.ones((rows, cols), dtype=np.int8)
    stack = []

    # Start from the upper-left corner
    start_x, start_y = 0, 0
    maze[start_x][start_y] = 0
    stack.append((start_x, start_y))

    # List of possible moves (up, down, left, right)
    moves = [(0, 1), (0, -1), (1, 0), (-1, 0)]

    while stack:
        x, y = stack[-1]
        possible_moves = []

        for dx, dy in moves:
            nx, ny = x + 2 * dx, y + 2 * dy

            if nx >= 0 and nx < rows and ny >= 0 and ny < cols and maze[nx][ny] == 1:
                possible_moves.append((dx, dy))

        if possible_moves:
            dx, dy = random.choice(possible_moves)
            nx, ny = x + 2 * dx, y + 2 * dy
            maze[x + dx][y + dy] = 0
            maze[nx][ny] = 0
            stack.append((nx, ny))
        else:
            stack.pop()

    # Set the lower-right corner as the end point
    maze[rows - 1][cols - 1] = 0

    return maze

def write_maze_to_file(maze, file_name):
    with open(file_name, 'w') as file:
        for row in maze:
            row_str = ' '.join(str(cell) for cell in row)
            file.write(row_str + '\n')



maze = generate_maze(801, 801)
write_maze_to_file(maze, '/Users/liujunzhou/Desktop/mul_project/Maze-problem/maze/maze5')

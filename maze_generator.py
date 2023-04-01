import random

def is_valid(x, y, maze_size):
    return 0 <= x < maze_size and 0 <= y < maze_size

def generate_maze(maze, x, y):
    directions = [(1, 0), (-1, 0), (0, 1), (0, -1)]
    random.shuffle(directions)

    for dx, dy in directions:
        nx, ny = x + 2 * dx, y + 2 * dy

        if is_valid(nx, ny, len(maze)) and maze[nx][ny] == 1:
            maze[nx - dx][ny - dy] = 0
            maze[nx][ny] = 0
            generate_maze(maze, nx, ny)

def print_maze(maze):
    for row in maze:
        print(' '.join(map(str, row)))

def create_maze(maze_size):
    maze = [[1] * maze_size for _ in range(maze_size)]

    maze[1][1] = 0
    generate_maze(maze, 1, 1)

    return maze

def write_maze_to_file(maze, file_name):
    with open(file_name, 'w') as f:
        for row in maze:
            f.write(' '.join(map(str, row)) + '\n')

maze_size = int(input("Enter the size of the maze (odd number): "))
file_name = input("Enter the file name: ")

# "/Users/hmac/Desktop/Maze-problem/maze/maze10/maze10_1.txt"

if maze_size % 2 == 0:
    print("Please enter an odd number.")
else:
    maze = create_maze(maze_size)
    write_maze_to_file(maze, file_name)

    print_maze(maze)

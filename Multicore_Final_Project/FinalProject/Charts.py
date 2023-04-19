import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("/Users/fandongzhe/Desktop/2023SPRING/Multicore/proj/multicore-data.csv")
df['speedup_1core'] = df['DFS']/df['DFS(1-core)']
df['speedup_4core'] = df['DFS']/df['DFS(4-core)']
df['speedup_double'] = df['DFS']/df['DFS-DoubleEnd']

maze_size = list(df['maze_size'])
DFS_vanilla = list(df['DFS'])
DFS_1_core = list(df['DFS(1-core)'])
DFS_4_core = list(df['DFS(4-core)'])
DFS_DoubleEnd = list(df['DFS-DoubleEnd'])

speedup_1core = list(df['speedup_1core'])
speedup_4core = list(df['speedup_4core'])
speedup_double = list(df['speedup_double'])

plt.title("Maze size and run time")
plt.xlabel("Maze size")
plt.ylabel("Time")
plt.plot(maze_size, DFS_vanilla)
plt.plot(maze_size, DFS_1_core)
plt.plot(maze_size, DFS_4_core)
plt.plot(maze_size, DFS_DoubleEnd)
plt.legend(['DFS', 'DFS_1_core', 'DFS_4_core', 'DFS_DoubleEnd'])
plt.show()

plt.title("Maze size and speedup")
plt.xlabel("Maze size")
plt.ylabel("Speedup")
plt.plot(maze_size, speedup_1core)
plt.plot(maze_size, speedup_4core)
plt.plot(maze_size, speedup_double)
plt.legend(['DFS_1_core', 'DFS_4_core', 'DFS_DoubleEnd'])
plt.show()
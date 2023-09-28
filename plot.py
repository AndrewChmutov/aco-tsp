import os
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

sns.set()
def tsp(n_nodes: int, alpha, beta, rho):
    os.system('cmake --build build')
    os.system(f'./build/ant {n_nodes} {alpha} {beta} {rho}')

    path = []
    with open('data/path.txt') as file:
        for line in file:
            path.append(int(line))
    path.append(path[0])

    df = pd.read_csv('data/graph.csv')
    path = [tuple(df.iloc[i]) for i in path]
    path = list(zip(*path))

    plt.scatter(df['x'], df['y'])
    plt.plot(path[0], path[1])
    plt.savefig("data/plot.jpg")

tsp(10, 0.4, 4.2, 0.5)
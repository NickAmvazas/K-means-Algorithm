from matplotlib import pyplot as plt
import seaborn as sns
import numpy as np

color_collection = ['red', 'blue', 'green', 'teal', 'lightcoral', 'wheat', 'darkslategrey', 'olive', 'purple', 'orange', 'cyan', 'yellow','pink', 'grey']

with open("points_result.txt") as points_file, open("centers_result.txt") as centroids_file:
    points = sorted([line.replace("\n", "").split(" ") for line in points_file], key=lambda x: x[2])
    cluster_ids = [point[2] for point in points]
    centroids = [line.replace("\n", "").split(" ")[:-1] for line in centroids_file]
    clusters = 0
    for centroid in centroids:
        clusters = clusters + 1

    X = np.array(np.array([[float(point[0]), float(point[1])] for point in points]))
    y = np.array(list(map(int, cluster_ids)))
    centroids_float = np.array(np.array([[float(centroid[0]), float(centroid[1])] for centroid in centroids]))

    sns.set(rc={'figure.figsize':(13.5, 10.5)})
    colors = []
   
    for i in range(clusters):
        colors.append(color_collection[i])

    ax = sns.scatterplot(x=X[:, 0], y=X[:, 1], hue=y, palette=colors, alpha=0.5)
    ax = sns.scatterplot(x=centroids_float[:, 0], y=centroids_float[:, 1], hue=range(clusters), palette=colors, ec='black', legend=False, ax=ax)
    plt.show()
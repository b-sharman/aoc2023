import sys
import numpy as np

with open(sys.argv[-1]) as f:
    image = np.array([list(row) for row in f.read().strip().split("\n")])

empty_rows = [(row == ".").all() for row in image]
empty_cols = [(col == ".").all() for col in image.transpose()]
galaxies = [g + int(1e6-1) * np.array((sum(empty_rows[:g[0]]), sum(empty_cols[:g[1]]))) for g in np.transpose(np.where(image == "#"))]
print(sum(np.abs(g0 - g1).sum() for i, g0 in enumerate(galaxies) for g1 in galaxies[i+1:]))

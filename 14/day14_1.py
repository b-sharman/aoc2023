import sys
import numpy as np

with open(sys.argv[-1]) as f:
    image = np.array([list(row) for row in f.read().strip().split("\n")])

ans = 0
for col in image.transpose():
    cubes = np.flatnonzero(col == "#")
    rounds = np.flatnonzero(col == "O")
    for r in rounds:
        cube_row = np.flatnonzero(col[:r] == "#")[-1] if "#" in col[:r] else -1
        x = cube_row + np.logical_and(rounds > cube_row, rounds < r).sum()
        ans += image.shape[1] - x - 1

print(ans)

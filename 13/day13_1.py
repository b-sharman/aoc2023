import sys
import numpy as np

with open(sys.argv[-1]) as f:
    images = [np.array([list(row) for row in pattern.split("\n")]) for pattern in f.read().strip().split("\n\n")]

row_sum = 0
col_sum = 0
for i in images:
    for row in range(1, i.shape[0]):
        extent = min(row, i.shape[0]-row)
        row_sum += row * (i[row-extent:row] == np.flipud(i[row:row+extent])).all()
    for col in range(1, i.shape[1]):
        extent = min(col, i.shape[1]-col)
        col_sum += col * (i[:, col-extent:col] == np.fliplr(i[:, col:col+extent])).all()

print(100*row_sum + col_sum)

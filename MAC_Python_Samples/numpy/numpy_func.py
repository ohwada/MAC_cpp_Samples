# Python: numpy sample
# 2025-04-10  K.OHWADA

# https://qiita.com/k-keita/items/4228839d2fdc8fde7e9e

import numpy as np


arr_1d = np.array([1, 2, 3, 4, 5])

print("one dimensional array: ", arr_1d)

arr_2d = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])

print()
print("two dimensional array:")
print(arr_2d)

print()
print("mean: ", np.mean(arr_2d))
print("standard deviation:", np.std(arr_2d))
print(" sum:", np.sum(arr_2d))

random_int = np.random.randint(0, 10, size=(3, 3))

print()
print("random integer matrix 3x3:")
print(random_int)

import matplotlib.pyplot as plt

core = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]
naive = [32.802, 45.248, 28.926, 26.666, 21.366, 23.048, 19.346,22.032,21.039, 20.362,20.308, 16.317,18.245, 15.323, 16.814, 16.653]
openmp = [39.919, 21.815, 15.662, 12.857, 13.881,12.094,12.575,11.707,10.906,11.056,10.638,10.205,9.829,9.646,9.963,9.619]
opt_naive = [12.826, 6.461, 5.070, 3.979, 4.029,3.927, 3.456, 3.281, 3.220, 3.028, 2.800, 2.722, 2.615, 2.526, 2.461, 2.431]
opt_openmp = [12.923, 6.474, 5.048, 4.031, 4.418, 3.996, 3.518, 3.344, 3.410, 3.069, 2.939, 2.677, 2.672, 2.596, 2.518, 2.458]

plt.plot(core, naive, label='Naive_Thread')
plt.plot(core, openmp, label='OpenMP')
plt.plot(core, opt_naive, label='Optimized_Naive_Thread')
plt.plot(core, opt_openmp, label='Optimized OpenMP')

plt.xlabel('Cores')
plt.ylabel('Real Time(seconds)')
plt.title('Performance of Parallelization')

plt.legend()

plt.show()
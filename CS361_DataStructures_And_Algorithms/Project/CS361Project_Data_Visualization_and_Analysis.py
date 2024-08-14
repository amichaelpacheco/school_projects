import matplotlib.pyplot as plt
from matplotlib.ticker import LogFormatter, LogLocator
import numpy as np
import pandas as pd
import math
from scipy.stats import linregress
import matplotlib.axes as ax

"""
Sorting Algorithm Time Complexity Analysis and Visualisation:
(For both doubles and integers of arrays size n = 2^20<=n<=2^30)
QuadHeap Sort
3-Way MergeSort
Randomized QuickSort
=======================================================================================================================
"""

# Experimental Data
########################################################################################################################
# Integer Sorting Algorithm Runtimes
quadHeapSortRuntimesInt = np.array([0.196, 0.416, 0.932, 1.982, 4.250,
                                    9.293, 21.792, 45.641, 102.827, 219.220, 456.935])
threeWayMergeSortRuntimesInt = np.array([0.214, 0.423, 0.837, 1.691, 3.249,
                                         6.730, 14.174, 27.523, 58.708, 121.499, 241.404])
randomizedQuickSortRuntimesInt = np.array([0.165, 0.314, 0.580, 1.156, 2.419,
                                           5.102, 10.468, 21.134, 44.221, 90.829, 178.102])

# Double Sorting Algorithm Runtimes
quadHeapSortRuntimesDouble = np.array([0.217, 0.483, 1.90, 2.386,
                                       5.66, 11.140, 24.394, 54.295, 119.394, 253.160, 542.676])
threeWayMergeSortRuntimesDouble = np.array([0.247, 0.463, 1.60, 1.779,
                                            3.496, 7.366, 15.152, 30.484, 63.856, 129.405, 267.71])
randomizedQuickSortRuntimesDouble = np.array([0.151, 0.312, 0.614, 1.253,
                                              2.630, 5.262, 10.788, 23.17, 46.984, 95.32, 199.851])

# Array sizes n = 2^20<=n<=2^30
array_sizes = np.array([2**i for i in range(20, 31)])

# Time Complexity Analysis
########################################################################################################################
# Expected Runtimes for expected time complexity of O(nlog(n))
expected_runtimes = (np.array((array_sizes * np.log2(array_sizes))))

# Calculate the Average Constant Factor of all algorithms (Double and Int)
# Calculate the Average Constant Factor for Integer Sorting Algorithms
constant_factors_int = []

# Calculate the ratio of experimental runtime to expected runtime for each algorithm (Integer)
for runtimes in [quadHeapSortRuntimesInt, threeWayMergeSortRuntimesInt, randomizedQuickSortRuntimesInt]:
    ratios = runtimes / expected_runtimes
    # Calculate the average of the ratios
    average_ratio = np.mean(ratios)
    # Append the average ratio to the constant_factor_int list
    constant_factors_int.append(average_ratio)

# Average constant factor (Int)
avg_k_int = np.mean(constant_factors_int)

# Calculate the Average Constant Factor for Double Sorting Algorithms
constant_factors_double = []

# Calculate the ratio of experimental runtime to expected runtime for each algorithm (Double)
for runtimes in [quadHeapSortRuntimesDouble, threeWayMergeSortRuntimesDouble, randomizedQuickSortRuntimesDouble]:
    ratios = runtimes / expected_runtimes
    # Calculate the average of the ratios
    average_ratio = np.mean(ratios)
    # Append the average ratio to the constant_factor_double list
    constant_factors_double.append(average_ratio)

# Average constant factor (Double)
avg_k_double = np.mean(constant_factors_double)

# Calculate linear regression slopes for Integer data type runtimes
slopes_int = []
# Perform linear regression for each algorithm and append the slope
slope, _, _, _, _ = linregress(np.log(array_sizes), np.log(quadHeapSortRuntimesInt))
slopes_int.append(slope)

slope, _, _, _, _ = linregress(np.log(array_sizes), np.log(threeWayMergeSortRuntimesInt))
slopes_int.append(slope)

slope, _, _, _, _ = linregress(np.log(array_sizes), np.log(randomizedQuickSortRuntimesInt))
slopes_int.append(slope)


# Calculate linear regression slopes for Double data type runtimes
slopes_double = []
# Perform linear regression for each algorithm and append the slope
slope, _, _, _, _ = linregress(np.log(array_sizes), np.log(quadHeapSortRuntimesDouble))
slopes_double.append(slope)

slope, _, _, _, _ = linregress(np.log(array_sizes), np.log(threeWayMergeSortRuntimesDouble))
slopes_double.append(slope)

slope, _, _, _, _ = linregress(np.log(array_sizes), np.log(randomizedQuickSortRuntimesDouble))
slopes_double.append(slope)

# Calculate the distances from the expected slope of 10 for both ints and doubles
# Define the input values for calculation
n1 = 2**20
n2 = 2**30

# Calculate values for expected slope
y1 = math.log(n1 * math.log(n1, 2), 2)
y2 = math.log(n2 * math.log(n2, 2), 2)

# Calculate the expected slope for our expected runtime O(nlog(n))
expected_slope = (y2-y1) / (math.log(n2, 2) - math.log(n1, 2))

# Calculate the absolute error from expected
abs_dist_int = [abs(slope - expected_slope) for slope in slopes_int]
abs_dist_double = [abs(slope - expected_slope) for slope in slopes_double]

# Calculate the relative error from expected
rel_dist_int = [((abs(slope - expected_slope)/abs(expected_slope))*100) for slope in slopes_int]
rel_dist_double = [((abs(slope - expected_slope)/abs(expected_slope))*100) for slope in slopes_double]

# Define the algorithm names
algorithms = ['QuadHeap Sort', '3-Way Merge Sort', 'Randomized Quick Sort']

# Create a dictionary for the table
int_table_data = {
    'Algorithm': algorithms,
    'Linear Regression': slopes_int,
    'Absolute Distance': abs_dist_int,
    'Relative Distance': rel_dist_int,
    'Constant Factor': constant_factors_int
}

double_table_data = {
    'Algorithm': algorithms,
    'Linear Regression': slopes_double,
    'Absolute Distance': abs_dist_double,
    'Relative Distance': rel_dist_double,
    'Constant Factor': constant_factors_double
}

# Create a DataFrame
df_slopes_int = pd.DataFrame(int_table_data)
df_slopes_double = pd.DataFrame(double_table_data)

# Set the option to display all rows and columns
pd.set_option('display.max_rows', None)
pd.set_option('display.max_columns', None)
pd.set_option('display.expand_frame_repr', False)

# Display the tables
print("Asymptotic Analysis of Sorting Algorithms (Int)")
print("===============================================================")
print(df_slopes_int)
print("===============================================================")
print("Expected Slope of nlog(n): " + str(expected_slope))
print("Average Constant Factor of All Algorithms: {:.2e}".format(avg_k_int))
print('\n')
print("Asymptotic Analysis of Sorting Algorithms (Double)")
print("==================================================================")
print(df_slopes_double)
print("==================================================================")
print("Expected Slope of nlog(n): " + str(expected_slope))
print("Average Constant Factor of All Algorithms: {:.2e}".format(avg_k_double))

# Visualisation
########################################################################################################################
# Format Both Plots to Log_2()


# Define Unique plot for integer runtime data
plt.figure(figsize=(8, 6))

# Transform input data to log base_2 for input/array sizes 2^20-2^30
array_sizes = np.log2(array_sizes)

# Integer Plot data
# Expected runtimes from asymptotic bound nlog(n) * k ( average constant factor)
expected_runtimes_int = expected_runtimes * avg_k_int
plt.semilogy(array_sizes, expected_runtimes_int, marker='o',
           label='n(log(n)) * avg. constant factor (k): {:.2e}'.format(avg_k_int))

# Plot data and linear fit for Quad Heap Sort (Integers)
plt.semilogy(array_sizes, quadHeapSortRuntimesInt, marker='o', label='QuadHeap Sort')
coeffs = np.polyfit(np.log(array_sizes), np.log(quadHeapSortRuntimesInt), 1)
poly = np.poly1d(coeffs)
plt.plot(array_sizes, np.exp(poly(np.log(array_sizes))), linestyle='--', alpha=0.5, label='Linear Fit')

# Plot data and linear fit for Three Way Merge Sort (Integers)
plt.semilogy(array_sizes, threeWayMergeSortRuntimesInt, marker='o', label='3-Way Merge Sort')
coeffs = np.polyfit(np.log(array_sizes), np.log(threeWayMergeSortRuntimesInt), 1)
poly = np.poly1d(coeffs)
plt.plot(array_sizes, np.exp(poly(np.log(array_sizes))), linestyle='--', alpha=0.5, label='Linear Fit')

# Plot data and linear fit for Randomized Quick Sort (Integers)
plt.semilogy(array_sizes, randomizedQuickSortRuntimesInt, marker='o', label='Randomized Quick Sort')
coeffs = np.polyfit(np.log(array_sizes), np.log(randomizedQuickSortRuntimesInt), 1)
poly = np.poly1d(coeffs)
plt.plot(array_sizes, np.exp(poly(np.log(array_sizes))), linestyle='--', alpha=0.5, label='Linear Fit')

plt.scatter(array_sizes, quadHeapSortRuntimesInt, marker='o')
plt.scatter(array_sizes, threeWayMergeSortRuntimesInt, marker='o')
plt.scatter(array_sizes, randomizedQuickSortRuntimesInt, marker='o')

# Plot Settings (Integer)
plt.xlabel('Array Size, (Scale: log\u2082)')
plt.ylabel('Runtime (sec), (Scale: log\u2081\u2080)')
plt.title('Runtimes of Integer Sorting Algorithms')
plt.grid(True, which="both", ls="--")
plt.legend()

# Double Plot Data
# Define Unique plot for Double-precision float runtime data
plt.figure(figsize=(8, 6))

# Expected runtimes from asymptotic bound nlog(n) * k ( average constant factor)
expected_runtimes_double = expected_runtimes * avg_k_double
plt.semilogy(array_sizes, expected_runtimes_double, marker='o',
           label='n(log(n)) * avg. constant factor (k): {:.2e}'.format(avg_k_double))

# Plot data and linear fit for Quad Heap Sort (Doubles)
plt.semilogy(array_sizes, quadHeapSortRuntimesDouble, marker='o', label='Quad Heap Sort')
coeffs = np.polyfit(np.log(array_sizes), np.log(quadHeapSortRuntimesDouble), 1)
poly = np.poly1d(coeffs)
plt.plot(array_sizes, np.exp(poly(np.log(array_sizes))), linestyle='--', alpha=0.5, label='Linear Fit')

# Plot data and linear fit for Three Way Merge Sort (Doubles)
plt.semilogy(array_sizes, threeWayMergeSortRuntimesDouble, marker='o', label='Three Way Merge Sort')
coeffs = np.polyfit(np.log(array_sizes), np.log(threeWayMergeSortRuntimesDouble), 1)
poly = np.poly1d(coeffs)
plt.plot(array_sizes, np.exp(poly(np.log(array_sizes))), linestyle='--', alpha=0.5, label='Linear Fit')

# Plot data and linear fit for Randomized Quick Sort (Doubles)
plt.semilogy(array_sizes, randomizedQuickSortRuntimesDouble, marker='o', label='Randomized Quick Sort')
coeffs = np.polyfit(np.log(array_sizes), np.log(randomizedQuickSortRuntimesDouble), 1)
poly = np.poly1d(coeffs)
plt.plot(array_sizes, np.exp(poly(np.log(array_sizes))), linestyle='--', alpha=0.5, label='Linear Fit')

plt.scatter(array_sizes, quadHeapSortRuntimesDouble, marker='o')
plt.scatter(array_sizes, threeWayMergeSortRuntimesDouble, marker='o')
plt.scatter(array_sizes, randomizedQuickSortRuntimesDouble, marker='o')

# Plot Settings (Double-precision float)
plt.xlabel('Array Size, (Scale: log\u2082)')
plt.ylabel('Runtime (sec), (Scale: log\u2081\u2080)')
plt.title('Runtimes of Double Sorting Algorithms')
plt.grid(True, which="both", ls="--")
plt.legend()

# Finally show both plots
plt.show()



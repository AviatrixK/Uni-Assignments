# ADA Lab Assignment 1

This repository contains the notebook for **Lab Experiment 1** of Analysis and Design of Algorithms. The work focuses on how different algorithmic strategies solve practical computational problems such as sorting, resource allocation, optimization, and shortest-path routing.

## Project Overview

The notebook implements and compares five important algorithmic approaches:

| Problem | Strategy | Algorithm | Purpose |
| --- | --- | --- | --- |
| 1 | Divide and Conquer | Merge Sort | Efficient sorting of unsorted data |
| 2 | Comparative Analysis | Merge Sort vs Bubble Sort | Performance comparison across input sizes |
| 3 | Greedy | Fractional Knapsack | Maximize value with divisible items |
| 4 | Dynamic Programming | 0/1 Knapsack | Maximize value with indivisible items |
| 5 | Graph Algorithm | Dijkstra's Algorithm | Find shortest path from one source |

## Learning Focus

This assignment demonstrates:

- implementation of multiple algorithmic paradigms in Python
- comparison of theoretical and practical performance
- use of timing plots for scalability analysis
- interpretation of algorithm suitability for real-world scenarios

## Folder Contents

- `lab_assignment_1.ipynb`: main notebook containing all five problems, code, outputs, plots, and observations
- `images/sorting_performance_comparison.png`: exported plot for the sorting performance comparison
- `README.md`: project summary, setup instructions, and usage notes

## Environment Setup

Use Python 3.10 or later. A virtual environment is recommended.

```powershell
python -m venv .venv
.venv\Scripts\activate
pip install matplotlib jupyter
```

## How to Run

1. Open the `Sem_4/ADA` folder in Jupyter Notebook or JupyterLab.
2. Open `lab_assignment_1.ipynb`.
3. Run the notebook from top to bottom to generate all outputs and plots.

## Notebook Structure

Each problem section includes:

- problem context
- explanation of the selected strategy
- Python implementation
- sample output
- complexity discussion
- short observations

## Expected Outputs

The notebook generates:

- a correctly sorted array using Merge Sort
- a line plot comparing Bubble Sort and Merge Sort execution time
- a PNG export of the comparison plot inside the `images` folder
- the maximum value for the Fractional Knapsack problem
- the optimal value and DP table snapshot for the 0/1 Knapsack problem
- the shortest distances from a source node using Dijkstra's algorithm

## Plot Assets

The Matplotlib comparison chart is also saved as a standalone PNG file so it can be directly included in submissions, reports, or documentation without opening the notebook.

## Key Observations

- Merge Sort scales much better than Bubble Sort for larger inputs because of its `O(n log n)` behavior.
- Fractional Knapsack works well with a greedy strategy because the locally best value-to-weight ratio contributes to the global optimum.
- 0/1 Knapsack requires Dynamic Programming because local greedy choices do not always produce the best final solution.
- Dijkstra's algorithm is suitable for route planning and network analysis when all edge weights are non-negative.
- Practical execution times support the theoretical complexity differences discussed in class.

## Conclusion

This assignment shows that algorithm selection depends on problem structure. Divide and Conquer is effective for sorting, Greedy methods are efficient for some optimization problems, Dynamic Programming handles overlapping subproblems, and shortest-path algorithms are important in graph-based systems.

## References

- Cormen, Leiserson, Rivest, and Stein, *Introduction to Algorithms*
- Python documentation for `time` and `heapq`
- Matplotlib documentation: https://matplotlib.org/stable/

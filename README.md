# Sorting Algorithms in C

## 1. Project Information

- **University:** Université Badji Mokhtar – Annaba
- **Department:** Computer Science
- **Module:** Algorithms and Data Structures
- **Instructor:** Dr. Sabri Ghazi
- **Student:** Mohamed Amine Benour
- **Level:** L2 Computer Science and Automation
- **Group:** G1
- **Year:** 2026–2027

## 2. Objectives

In this assignment, we implement five sorting algorithms in C without using `qsort()`. We measure their execution time and memory usage on arrays up to 100,000 numbers, and compare the results with their theoretical complexity.

## 3. Language and Libraries

- **Language:** C (GCC 13.2.0)
- **Libraries:**
  - `stdio.h` for input/output and saving `results/results.csv`
  - `stdlib.h` for `srand()` and `rand()`
  - `time.h` for `clock()`
  - `windows.h` and `psapi.h` for `GetProcessMemoryInfo()`
  - `direct.h` for `_mkdir()`

## 4. How to Compile and Run

```bash
gcc -Wall -Wextra src/main.c -o main.exe -lpsapi
.\main.exe
```

## 5. Sorting Algorithms

- **Bubble Sort:** Checks pairs of adjacent elements and swaps them if needed. Uses a `swapped` flag to stop early if the array is already sorted.
- **Selection Sort:** Finds the smallest element in the unsorted part and swaps it with the first element of that part.
- **Insertion Sort:** Takes each element and puts it in the right place in the sorted left part by shifting bigger elements to the right.
- **Merge Sort:** Splits the array in two recursively, sorts each half, and merges them using `temp_arr`.
- **Quick Sort:** Uses the last element (`arr[right]`) as the pivot in `partition()`. To avoid deep recursion on the stack, it calls `quick_sort()` recursively on the smaller side and uses a `while` loop for the bigger side. Even with this, its worst-case time is still $O(n^2)$ on already-sorted or reverse-sorted arrays.

## 6. Complexity

| Algorithm | Best | Average | Worst | Space |
| :--- | :--- | :--- | :--- | :--- |
| Bubble Sort | $O(n)$ | $O(n^2)$ | $O(n^2)$ | $O(1)$ |
| Selection Sort | $O(n^2)$ | $O(n^2)$ | $O(n^2)$ | $O(1)$ |
| Insertion Sort | $O(n)$ | $O(n^2)$ | $O(n^2)$ | $O(1)$ |
| Merge Sort | $O(n \log n)$ | $O(n \log n)$ | $O(n \log n)$ | $O(n)$ |
| Quick Sort | $O(n \log n)$ | $O(n \log n)$ | $O(n^2)$ | $O(\log n)$ |

## 7. Time and Memory Measurement

- **Time:** Measured using `clock()` around the sorting call only. Each algorithm runs 5 times on copies of the same array (`srand(42)`), then we take the average in ms.
- **Memory:** Measured on Windows with `GetProcessMemoryInfo()` (`WorkingSetSize` after each algorithm, and `PeakWorkingSetSize` at the end).
- **Note:** `WorkingSetSize` and `PeakWorkingSetSize` give the memory of the whole program process, not the exact memory of one function alone.

## 8. Experimental Results

Tested on: Windows 11 Pro, Intel(R) Core(TM) i5-8265U CPU @ 1.60GHz, 8,005 MB RAM, GCC 13.2.0.

Results from `results/results.csv` (random numbers, average of 5 runs):

| Algorithm | 1,000 (ms) | 5,000 (ms) | 10,000 (ms) | 50,000 (ms) | 100,000 (ms) |
| :--- | :---: | :---: | :---: | :---: | :---: |
| Bubble Sort | 2.000 | 52.400 | 305.200 | Skipped | Skipped |
| Selection Sort | 1.200 | 27.400 | 118.800 | Skipped | Skipped |
| Insertion Sort | 0.800 | 16.800 | 63.000 | Skipped | Skipped |
| Merge Sort | 0.000 | 0.800 | 1.600 | 8.200 | 18.200 |
| Quick Sort | 0.200 | 0.400 | 1.000 | 6.200 | 14.400 |

Whole-program Working Set in `results/results.csv` went from `3952.00 KB` (size 1,000) to `5104.00 KB` (size 100,000). Peak memory was `5104.00 KB` (`4.98 MB`).

## 9. Discussion

- Quick Sort and Merge Sort were the fastest. At `100,000` numbers, Quick Sort took `14.400 ms` and Merge Sort took `18.200 ms`.
- Bubble Sort got much slower as the size grew (`52.400 ms` at 5,000 to `305.200 ms` at 10,000) because it does $O(n^2)$ comparisons and swaps.
- Merge Sort and Quick Sort stay fast on large arrays because their average time is $O(n \log n)$.
- Bubble, Selection, and Insertion Sort were skipped for `50,000` and `100,000` because $O(n^2)$ algorithms take too long on big arrays.

## 10. Conclusion

Simple $O(n^2)$ algorithms work well for small arrays, while Merge Sort and Quick Sort are much better for large arrays like `100,000` elements (`18.200 ms` and `14.400 ms`).

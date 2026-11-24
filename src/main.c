#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <psapi.h>
#include <direct.h>

#define MAX_SIZE 100000
#define RUNS 5

int original[MAX_SIZE];
int copy[MAX_SIZE];
int temp_arr[MAX_SIZE];

void bubble_sort(int arr[], int n) {
    int i, j, temp, swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = 0;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        if (swapped == 0) {
            break;
        }
    }
}

void selection_sort(int arr[], int n) {
    int i, j, min, temp;
    for (i = 0; i < n - 1; i++) {
        min = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }
}

void insertion_sort(int arr[], int n) {
    int i, j, key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void merge(int arr[], int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp_arr[k] = arr[i];
            i++;
        } else {
            temp_arr[k] = arr[j];
            j++;
        }
        k++;
    }
    while (i <= mid) {
        temp_arr[k] = arr[i];
        i++;
        k++;
    }
    while (j <= right) {
        temp_arr[k] = arr[j];
        j++;
        k++;
    }
    for (i = left; i <= right; i++) {
        arr[i] = temp_arr[i];
    }
}

void merge_sort(int arr[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int partition(int arr[], int left, int right) {
    int pivot = arr[right];
    int i = left - 1;
    int j, temp;

    for (j = left; j < right; j++) {
        if (arr[j] <= pivot) {
            i++;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    temp = arr[i + 1];
    arr[i + 1] = arr[right];
    arr[right] = temp;
    return i + 1;
}

void quick_sort(int arr[], int left, int right) {
    while (left < right) {
        int p = partition(arr, left, right);

        if (p - left < right - p) {
            quick_sort(arr, left, p - 1);
            left = p + 1;
        } else {
            quick_sort(arr, p + 1, right);
            right = p - 1;
        }
    }
}

void copy_array(int src[], int dest[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

int is_sorted(int arr[], int n) {
    int i;
    for (i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return 0;
        }
    }
    return 1;
}

void print_array(int arr[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

double get_working_set_kb() {
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
        return pmc.WorkingSetSize / 1024.0;
    }
    return -1.0;
}

double get_memory_kb() {
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
        return pmc.PeakWorkingSetSize / 1024.0;
    }
    return -1.0;
}

double measure_sort(int algo, int n) {
    clock_t start, end;
    double total_ms = 0.0;
    int r;

    for (r = 0; r < RUNS; r++) {
        copy_array(original, copy, n);

        start = clock();
        if (algo == 1) {
            bubble_sort(copy, n);
        } else if (algo == 2) {
            selection_sort(copy, n);
        } else if (algo == 3) {
            insertion_sort(copy, n);
        } else if (algo == 4) {
            merge_sort(copy, 0, n - 1);
        } else if (algo == 5) {
            quick_sort(copy, 0, n - 1);
        }
        end = clock();

        total_ms += ((double)(end - start) * 1000.0) / CLOCKS_PER_SEC;

        if (!is_sorted(copy, n)) {
            printf("Error: array not sorted on run %d (algo %d).\n", r + 1, algo);
            return -1.0;
        }
    }

    return total_ms / RUNS;
}

void run_single_algorithm(int algo) {
    int n, i, type;
    double avg_time, mem_kb;

    printf("Enter array size (1 to %d): ", MAX_SIZE);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_SIZE) {
        while (getchar() != '\n');
        printf("Invalid size.\n");
        return;
    }
    while (getchar() != '\n');

    printf("Input type (1=Random, 2=Sorted, 3=Reverse, 4=Duplicates): ");
    if (scanf("%d", &type) != 1 || type < 1 || type > 4) {
        while (getchar() != '\n');
        type = 1;
    } else {
        while (getchar() != '\n');
    }

    srand(42);
    for (i = 0; i < n; i++) {
        if (type == 2) {
            original[i] = i;
        } else if (type == 3) {
            original[i] = n - i;
        } else if (type == 4) {
            original[i] = rand() % 20;
        } else {
            original[i] = rand() % 10000;
        }
    }

    if (n <= 20) {
        printf("Original: ");
        print_array(original, n);
    }

    avg_time = measure_sort(algo, n);
    if (avg_time < 0.0) {
        printf("Sort failed.\n");
        return;
    }
    mem_kb = get_memory_kb();

    if (n <= 20) {
        printf("Sorted:   ");
        print_array(copy, n);
    }

    printf("Sorted correctly: Yes\n");
    printf("Average time (5 runs): %.3f ms\n", avg_time);
    if (mem_kb >= 0.0) {
        printf("Program peak memory: %.2f KB (%.2f MB)\n", mem_kb, mem_kb / 1024.0);
    } else {
        printf("Program peak memory: Unavailable\n");
    }
}

void compare_all() {
    int sizes[5] = {1000, 5000, 10000, 50000, 100000};
    char *names[5] = {"Bubble Sort", "Selection Sort", "Insertion Sort", "Merge Sort", "Quick Sort"};
    double times[5];
    double mems[5];
    double peak_kb;
    int done[5];
    int ranks[5];
    int s, a, i, j, n;

    _mkdir("results");
    FILE *fp = fopen("results/results.csv", "w");
    if (fp != NULL) {
        fprintf(fp, "Algorithm,Array_Size,Average_Time_ms,Process_Working_Set_KB,Rank\n");
    }

    printf("\nBubble, Selection, and Insertion Sort are skipped for sizes > 10000.\n");

    for (s = 0; s < 5; s++) {
        n = sizes[s];
        srand(42);
        for (i = 0; i < n; i++) {
            original[i] = rand() % 100000;
        }

        for (a = 0; a < 5; a++) {
            if (a < 3 && n > 10000) {
                done[a] = 0;
                times[a] = 0.0;
                mems[a] = -1.0;
            } else {
                times[a] = measure_sort(a + 1, n);
                if (times[a] < 0.0) {
                    done[a] = -1;
                    mems[a] = -1.0;
                } else {
                    mems[a] = get_working_set_kb();
                    done[a] = 1;
                }
            }
        }

        for (i = 0; i < 5; i++) {
            if (done[i] != 1) {
                ranks[i] = 0;
            } else {
                int r = 1;
                for (j = 0; j < 5; j++) {
                    if (done[j] == 1 && times[j] < times[i]) {
                        r++;
                    }
                }
                ranks[i] = r;
            }
        }

        printf("\n--- Size: %d ---\n", n);
        printf("%-16s | %-8s | %-10s | %-16s | %-4s\n",
               "Algorithm", "Size", "Time (ms)", "Working Set (KB)", "Rank");
        printf("-----------------+----------+------------+------------------+-----\n");

        for (a = 0; a < 5; a++) {
            if (done[a] == 1) {
                if (mems[a] >= 0.0) {
                    printf("%-16s | %-8d | %-10.3f | %-16.2f | %-4d\n",
                           names[a], n, times[a], mems[a], ranks[a]);
                    if (fp != NULL) {
                        fprintf(fp, "%s,%d,%.3f,%.2f,%d\n",
                                names[a], n, times[a], mems[a], ranks[a]);
                    }
                } else {
                    printf("%-16s | %-8d | %-10.3f | %-16s | %-4d\n",
                           names[a], n, times[a], "N/A", ranks[a]);
                    if (fp != NULL) {
                        fprintf(fp, "%s,%d,%.3f,N/A,%d\n",
                                names[a], n, times[a], ranks[a]);
                    }
                }
            } else if (done[a] == -1) {
                printf("%-16s | %-8d | %-10s | %-16s | %-4s\n",
                       names[a], n, "Failed", "N/A", "N/A");
                if (fp != NULL) {
                    fprintf(fp, "%s,%d,Failed,N/A,N/A\n", names[a], n);
                }
            } else {
                printf("%-16s | %-8d | %-10s | %-16s | %-4s\n",
                       names[a], n, "Skipped", "N/A", "N/A");
                if (fp != NULL) {
                    fprintf(fp, "%s,%d,Skipped,N/A,N/A\n", names[a], n);
                }
            }
        }
    }

    peak_kb = get_memory_kb();
    if (fp != NULL) {
        fclose(fp);
        printf("\nSaved to results/results.csv\n");
    }
    if (peak_kb >= 0.0) {
        printf("Program peak memory: %.2f KB (%.2f MB)\n", peak_kb, peak_kb / 1024.0);
    } else {
        printf("Program peak memory: Unavailable\n");
    }
}

int main() {
    int choice;

    do {
        printf("\n========== SORTING ALGORITHMS ==========\n\n");
        printf("1. Bubble Sort\n");
        printf("2. Selection Sort\n");
        printf("3. Insertion Sort\n");
        printf("4. Merge Sort\n");
        printf("5. Quick Sort\n");
        printf("6. Compare All Algorithms\n");
        printf("0. Exit\n\n");
        printf("Your choice: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Invalid input.\n");
            choice = -1;
            continue;
        }
        while (getchar() != '\n');

        switch (choice) {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
                run_single_algorithm(choice);
                break;
            case 6:
                compare_all();
                break;
            case 0:
                printf("Bye!\n");
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }
    } while (choice != 0);

    return 0;
}

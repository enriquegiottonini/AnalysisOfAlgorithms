#include "sorting_methods.h"

// Auxiliary functions
bool leq(int x, int y) {
    return (x <= y);
}

bool geq(int x, int y) {
    return (x >= y);
}

void printStats(size_t N) {
    struct timeval start, stop;
    double secs = 0;

    printf("\nFor N=%d\n", (int)N);
    int* list = randint_list(N, -N, N);

    // SELECTION SORT
    gettimeofday(&start, NULL);
    int* selection = selection_sort(list, N, leq);
    gettimeofday(&stop, NULL);
    secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
    printf("Selection sort:\t");
    printf("time taken %f ms\n", secs * 1000);

    // INSERTION SORT
    gettimeofday(&start, NULL);
    int* insertion = insertion_sort(list, N, leq);
    gettimeofday(&stop, NULL);
    secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
    printf("Insertion sort:\t");
    printf("time taken %f ms\n", secs * 1000);

    // MERGE SORT
    gettimeofday(&start, NULL);
    int* merge = merge_sort(list, N, leq);
    gettimeofday(&stop, NULL);
    secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
    printf("Merge sort:\t");
    printf("time taken %f ms\n", secs * 1000);

    free(list);
    free(selection);
    free(insertion);
    free(merge);
}

int main(void) {
    struct timeval start, stop;
    double secs = 0;

    gettimeofday(&start, NULL);

    printStats(100);
    printStats(1000);
    printStats(10000);
    printStats(100000);

    gettimeofday(&stop, NULL);
    secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
    printf("\nTotal time taken %f ms\n", secs * 1000);
    return 0;
}
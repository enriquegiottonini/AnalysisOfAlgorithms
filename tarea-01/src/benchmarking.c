#include "sorting_methods.h"

// Auxiliary functions
bool leq(int x, int y) {
    return (x <= y);
}

bool geq(int x, int y) {
    return (x >= y);
}

int power(int base, int exp) {
    if (exp == 0)
        return 1;
    else if (exp % 2)
        return base * power(base, exp - 1);
    else {
        int temp = power(base, exp / 2);
        return temp * temp;
    }
}

double bench(size_t N, int* list, int* (*sort_method)()) {
    struct timeval start, stop;
    double secs = 0;
    printf("\nFor N=%d\n", (int)N);
    gettimeofday(&start, NULL);

    int* sorted = sort_method(list, N, leq);
    gettimeofday(&stop, NULL);
    secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
    printf("time taken %f ms\n", secs * 1000);
    free(sorted);
    return secs;
}

void bench_average_ktimes(int k, int* (*sort_method)()) {
    float times[k];
    for (int t = 1; t < k + 1; t++) {
        size_t N = 1000 * t;
        int* random_list = randint_list(N, -N, N);
        float secs = bench(N, random_list, sort_method);
        times[t - 1] = secs;
        free(random_list);
    }
    // Print times array
    printf("[");
    for (int j = 0; j < k - 1; j++) {
        printf("%f,", times[j]);
    }
    printf("%f]\n", times[k - 1]);
}

// already sorted list
void bench_best_ktimes(int k, int* (*sort_method)()) {
    float times[k];
    for (int t = 1; t < k + 1; t++) {
        size_t N = 1000 * t;
        int* random_list = randint_list(N, -N, N);
        int* sorted_list = merge_sort(random_list, N, leq);
        float secs = bench(N, sorted_list, sort_method);
        times[t - 1] = secs;
        free(random_list);
        free(sorted_list);
    }

    // Print times array
    printf("[");
    for (int j = 0; j < k - 1; j++) {
        printf("%f,", times[j]);
    }
    printf("%f]\n", times[k - 1]);
}

// already sorted but reversed list
void bench_worst_ktimes(int k, int* (*sort_method)()) {
    float times[k];
    for (int t = 1; t < k + 1; t++) {
        size_t N = 1000 * t;
        int* random_list = randint_list(N, -N, N);
        int* sorted_list = merge_sort(random_list, N, geq);  // Reversed
        float secs = bench(N, sorted_list, sort_method);
        times[t - 1] = secs;
        free(random_list);
        free(sorted_list);
    }

    // Print times array
    printf("[");
    for (int j = 0; j < k - 1; j++) {
        printf("%f,", times[j]);
    }
    printf("%f]\n", times[k - 1]);
}

int main(void) {
    struct timeval start, stop;
    double secs = 0;

    gettimeofday(&start, NULL);

    int k = 10;
    printf("===========================\n");
    printf("\tSELECTION SORT\n");
    printf("===========================\n");
    printf("Best Case:\n");
    bench_best_ktimes(k, selection_sort);
    printf("===========================\n");
    printf("Worst case:\n");
    bench_worst_ktimes(k, selection_sort);
    printf("===========================\n");
    printf("Average case:\n");
    bench_average_ktimes(k, selection_sort);

    printf("===========================\n");
    printf("\tINSERTION SORT\n");
    printf("===========================\n");
    printf("Best Case:\n");
    bench_best_ktimes(k, insertion_sort);
    printf("===========================\n");
    printf("Worst case:\n");
    bench_worst_ktimes(k, insertion_sort);
    printf("===========================\n");
    printf("Average case:\n");
    bench_average_ktimes(k, insertion_sort);

    printf("===========================\n");
    printf("\tMERGE SORT\n");
    printf("===========================\n");
    printf("Best Case:\n");
    bench_best_ktimes(k, merge_sort);
    printf("===========================\n");
    printf("Worst case:\n");
    bench_worst_ktimes(k, merge_sort);
    printf("===========================\n");
    printf("Average case:\n");
    bench_average_ktimes(k, merge_sort);

    gettimeofday(&stop, NULL);
    secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
    printf("\nTotal time taken %f ms\n", secs * 1000);
    return 0;
}
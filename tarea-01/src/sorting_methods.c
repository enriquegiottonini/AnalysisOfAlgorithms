#include "sorting_methods.h"

void printList(int* lst, size_t n) {
    if (lst == NULL) {
        printf("[]\n");
        return;
    }

    printf("[");
    for (size_t i = 0; i < n - 1; i++) printf("%d, ", *(lst + i));
    printf("%d]\n", *(lst + n - 1));
}

void histogram(int* lst, size_t n) {
    if (lst == NULL) return;
    for (int i = 0; i < (int)n; i++) {
        int freq = *(lst + i);
        if (freq < 0) freq = 0;  // No negative numbers...
        printf("%3d:", freq);
        for (int j = 0; j < freq; j++) printf("*");
        printf("\n");
    }
}

int* randint_list(int n, int lower, int upper) {
    if (n <= 0) return NULL;

    int* lst = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        *(lst + i) = (rand() % (upper + 1 - lower)) + lower;
    }
    return lst;
}

bool is_ordered(int* lst, size_t n, bool (*f)()) {
    if (lst == NULL) return false;

    for (int i = 0; i < (int)n - 1; i++) {
        int curr = *(lst + i);
        int next = *(lst + i + 1);
        if (!(f(curr, next))) return false;
    }
    return true;
}

int* selection_sort(int* lst, size_t n, void (*f)()) {
    int* new_lst = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < (int)n; i++) {
        *(lst + i) = i;
    }

    f(lst, n);

    return new_lst;
}
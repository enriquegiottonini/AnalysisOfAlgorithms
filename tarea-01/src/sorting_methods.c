#include "sorting_methods.h"

int* selection_sort(int* lst, size_t n, bool (*f)()) {
    if (lst == NULL) return NULL;

    int* ordered_lst = copy_list(lst, n);
    for (int i = 0; i < (int)n - 1; i++) {
        int selected_key = i;
        for (int j = i + 1; j < (int)n; j++) {
            int current = *(ordered_lst + j);
            // Update selected element if the compare function f is satisfies it.
            if (f(current, *(ordered_lst + selected_key)))
                selected_key = j;
        }
        swap(ordered_lst + i, ordered_lst + selected_key);
    }
    return ordered_lst;
}

int* insertion_sort(int* lst, size_t n, bool (*f)()) {
    if (lst == NULL) return NULL;

    int* ordered = copy_list(lst, n);
    for (int i = 1; i < (int)n; i++) {
        int j = i;
        while ((j > 0) && (f(*(ordered + j), *(ordered + j - 1)))) {
            swap(ordered + j, ordered + j - 1);
            j--;
        }
    }
    return ordered;
}

void print_list(int* lst, size_t n) {
    if (lst == NULL) {
        printf("[]\n");
        return;
    }
    // print a list of the form [a, b, c, ..., z].
    printf("[");
    for (size_t i = 0; i < n - 1; i++) printf("%d, ", *(lst + i));
    printf("%d]\n", *(lst + n - 1));
}

void histogram(int* lst, size_t n) {
    if (lst == NULL) return;

    // For each positive integer in the list, print corresponding '*'
    for (int i = 0; i < (int)n; i++) {
        int freq = *(lst + i);
        // Negative numbers are mapped to 0.
        if (freq < 0) freq = 0;
        printf("%3d:", freq);
        for (int j = 0; j < freq; j++) printf("*");
        printf("\n");
    }
}

int* randint_list(int n, int lower, int upper) {
    if (n <= 0) return NULL;

    int* lst = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        // elements are numbers are between [lower, upper] bound.
        *(lst + i) = (rand() % (upper + 1 - lower)) + lower;
    }
    return lst;
}

bool is_ordered(int* lst, size_t n, bool (*f)()) {
    if (lst == NULL) return false;

    // for each consecutive pair x , y element in list
    // check that f(x, y) is satisfied.
    for (int i = 0; i < (int)n - 1; i++) {
        int curr = *(lst + i);
        int next = *(lst + i + 1);
        if (!(f(curr, next))) return false;
    }
    return true;
}
int* copy_list(int* lst, size_t n) {
    if (lst == NULL) return NULL;

    int* new_lst = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < (int)n; i++) {
        *(new_lst + i) = *(lst + i);
    }
    return new_lst;
}

void swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}
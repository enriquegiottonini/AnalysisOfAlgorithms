#include "sorting_methods.h"

/*

   (      (                        )    )
   )\     )\ (  (       (   (   ( /( ( /(     )
((((_)(  ((_))\))(  (   )(  )\  )\()))\())   (     (
 )\ _ )\  _ ((_))\  )\ (()\((_)(_))/((_)\    )\  ' )\
 (_)_\(_)| | (()(_)((_) ((_)(_)| |_ | |(_) _((_)) ((_)
  / _ \  | |/ _` |/ _ \| '_|| ||  _|| ' \ | '  \()(_-<
 /_/ \_\ |_|\__, |\___/|_|  |_| \__||_||_||_|_|_| /__/
            |___/

*/

int* selection_sort(int* lst, size_t n, bool (*f)()) {
    if (lst == NULL) return NULL;

    int* ordered_lst = copy_list(lst, n);
    for (int i = 0; i < (int)n - 1; i++) {
        int selected_key = i;
        for (int j = i + 1; j < (int)n; j++) {
            int current = ordered_lst[j];
            // Update selected element if the compare function f is satisfies it.
            if (f(current, ordered_lst[selected_key]))
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
        while ((j > 0) && (f(ordered[j], ordered[j - 1]))) {
            swap(ordered + j, ordered + j - 1);
            j--;
        }
    }
    return ordered;
}

int* merge(int* lst1, size_t n1, int* lst2, size_t n2, bool (*f)()) {
    // Both lists have to hold f property of ordering
    if (!((is_ordered(lst1, n1, f)) && (is_ordered(lst2, n2, f)))) return NULL;

    int* merged_lst = (int*)malloc((n1 + n2) * sizeof(int));

    for (int k = 0, i = 0, j = 0; k < (int)(n1 + n2);) {
        // If there is elements on j to check and (no elements in i or f(j, i))
        if ((j < (int)n2) && (i == (int)n1 || (f(lst2[j], lst1[i]))))
            merged_lst[k++] = lst2[j++];
        else
            merged_lst[k++] = lst1[i++];
    }

    return merged_lst;
}

int* merge_sort(int* lst, size_t n, bool (*f)()) {
    if (lst == NULL) return NULL;
    if (n == 1) {
        int* el = (int*)malloc(sizeof(int));
        el[0] = lst[0];
        return el;
    }

    int half_size = floor(n / 2);
    int* l1 = copy_list(lst, half_size);
    int* l2 = copy_list(lst + half_size, n - half_size);
    int* sorted_l1 = merge_sort(l1, half_size, f);
    int* sorted_l2 = merge_sort(l2, n - half_size, f);
    int* merged = merge(sorted_l1, half_size, sorted_l2, n - half_size, f);

    if (l1 != NULL) free(l1);
    if (l2 != NULL) free(l2);
    if (sorted_l1 != NULL) free(sorted_l1);
    if (sorted_l2 != NULL) free(sorted_l2);

    return merged;
}

/*

____ ____ ____ ____ ____ ____ _    ___  __   ____ ____
| . \| __\| . \|  _\|   || . \|\/\ |  \ | \|\| __\| __\
| __/|  ]_|  <_| _\ | . ||  <_|   \| . \|  \|| \__|  ]_
|/   |___/|/\_/|/   |___/|/\_/|/v\/|/\_/|/\_/|___/|___/


*/

void time_execution(void (*f)()) {
    struct timeval start, stop;
    double secs = 0;

    gettimeofday(&start, NULL);

    f();

    gettimeofday(&stop, NULL);
    secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
    printf("time taken %f ms\n", secs * 1000);
}

/*
  _   _ _   _ _ _ _   _
 | | | | |_(_) (_) |_(_) ___  ___
 | | | | __| | | | __| |/ _ \/ __|
 | |_| | |_| | | | |_| |  __/\__ \
  \___/ \__|_|_|_|\__|_|\___||___/

*/

void print_list(int* lst, size_t n) {
    if (lst == NULL) {
        printf("[]\n");
        return;
    }
    // print a list of the form [a, b, c, ..., z].
    printf("[");
    for (size_t i = 0; i < n - 1; i++) printf("%d, ", lst[i]);
    printf("%d]\n", lst[n - 1]);
}

void histogram(int* lst, size_t n) {
    if (lst == NULL) return;

    // For each positive integer in the list, print corresponding '*'
    for (int i = 0; i < (int)n; i++) {
        int freq = lst[i];
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
        lst[i] = (rand() % (upper + 1 - lower)) + lower;
    }
    return lst;
}

bool is_ordered(int* lst, size_t n, bool (*f)()) {
    if (lst == NULL) return false;

    // for each consecutive pair x , y element in list
    // check that f(x, y) is satisfied.
    for (int i = 0; i < (int)n - 1; i++) {
        int curr = lst[i];
        int next = lst[i + 1];
        if (!(f(curr, next))) return false;
    }
    return true;
}
int* copy_list(int* lst, size_t n) {
    if (lst == NULL) return NULL;

    int* new_lst = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < (int)n; i++) {
        new_lst[i] = lst[i];
    }
    return new_lst;
}

void swap(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}
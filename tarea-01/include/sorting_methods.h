/** @file sorting_methods.h
 *  @brief functions for sorting arrays of integers.
 *
 *  Contains functions for sorting arrays, as well as
 *  utilities for creating them in random order, displaying,
 *  and benchmarking.
 *
 *  @author Enrique Giottonini
 */

#ifndef SORTING_METHODS_H
#define SORTING_METHODS_H

#include <stdbool.h>  //bool
#include <stdio.h>    //printf
#include <stdlib.h>   //malloc, free, rand, srand
#include <time.h>     //time

/*
  _   _ _   _ _ _ _   _
 | | | | |_(_) (_) |_(_) ___  ___
 | | | | __| | | | __| |/ _ \/ __|
 | |_| | |_| | | | |_| |  __/\__ \
  \___/ \__|_|_|_|\__|_|\___||___/

*/

/** @brief Prints a representation of list.
 *
 *  Prints a list L in the form [l1, l2, ..., ln]
 *
 *  @param lst Pointer to list.
 *  @param n Number of elements list
 *  @return void
 */
void printList(int*, size_t);

/** @brief Creates a random list of integer.
 *
 *  Creates a random list of integers between a
 *  lower bound and an upper bound.
 *  @param n Number of elements list
 *  @param lower Lower bound
 *  @param upper Number of elements list
 *
 *  @return *int pointer to created list
 */
int* randint_list(int, int, int);

// TODO
// Check if a list is ordered
// print list with frecuencies

// ALGORITHMS
// selection
// insertion
// merge
int* selection_sort(int* lst, size_t n, void (*f)());

// PERFOMANCE
// time a function
// plot times?
// reporte en latex

#endif

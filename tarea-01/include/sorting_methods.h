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

   (      (                        )    )
   )\     )\ (  (       (   (   ( /( ( /(     )
((((_)(  ((_))\))(  (   )(  )\  )\()))\())   (     (
 )\ _ )\  _ ((_))\  )\ (()\((_)(_))/((_)\    )\  ' )\
 (_)_\(_)| | (()(_)((_) ((_)(_)| |_ | |(_) _((_)) ((_)
  / _ \  | |/ _` |/ _ \| '_|| ||  _|| ' \ | '  \()(_-<
 /_/ \_\ |_|\__, |\___/|_|  |_| \__||_||_||_|_|_| /__/
            |___/

*/

// selection
// insertion
// merge

/** @brief implementation of selection sort
 *
 *  Returns a new list that is ordered, it does
 *  not mutate the original list.
 *  Order can be defined by a compare function as a parameter.
 *
 *  best case : O(n²)
 *  worst case: O(n²)
 *
 *  Selection sort always iterate thorugh the list, selecting an
 *  element from each iteration.
 *
 *  @param int* pointer to list
 *  @param size_t number of elements in list
 *  @param bool(*f) pointer to a compare function that takes two arguments and returns a bool
 *  @return int* ordered list
 */
int* selection_sort(int* lst, size_t n, bool (*f)());

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
void print_list(int*, size_t);

/** @brief Prints a representation of list.
 *
 *  Prints a list L in the form
 *  l1: *********
 *  l2: ****
 *  l3: *****
 *  ...
 *  ln: **
 *
 *  @param lst Pointer to list of natural numbers.
 *  @param n number of elements in list.
 *  @return void
 */
void histogram(int*, size_t);

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

/** @brief copy a list
 *
 *  @param int* pointer to list
 *  @param size_t number of elements in list
 *
 *  @return pointer to copy of list
 */
int* copy_list(int*, size_t);

/** @brief check that a list is ordered via afunction f
 *
 *  For every e_i element from a list check that
 *  the function satisfies f(e_i, e_{i+1})
 *  @param int* pointer to list
 *  @param size_t number of elements in list
 *  @param bool(*f) pointer to a function that takes two arguments and returns a bool
 *
 *  @return bool if is ordered false otherwise
 */
bool is_ordered(int* lst, size_t n, bool (*f)());

// PERFOMANCE
// time a function
// plot times?
// reporte en latex

#endif

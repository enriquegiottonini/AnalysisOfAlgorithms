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

#include <math.h>      //floor
#include <stdbool.h>   //bool
#include <stdio.h>     //printf
#include <stdlib.h>    //malloc, free, rand, srand
#include <sys/time.h>  //start.tv_used
#include <time.h>      //time, gettimeofday

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

/** @brief implementation of selection sort
 *
 *  Returns a new list that is ordered, it does
 *  not mutate the original list.
 *  Order can be defined by a compare function f as a parameter.
 *
 *  best case : O(n²)
 *  worst case: O(n²)
 *
 *  Selection sort always iterate forward twice through the list, selecting the best
 *  element that satisfies f from each iteration, incrementally sorting the list.
 *
 *  @param int* pointer to list
 *  @param size_t number of elements in list
 *  @param bool(*f) pointer to a compare function that takes two arguments and returns a bool
 *  @return int* ordered list
 */
int* selection_sort(int* lst, size_t n, bool (*f)());

/** @brief implementation of insertion sort
 *
 *  Returns a new list that is ordered, it does
 *  not mutate the original list.
 *  Order can be defined by a compare function as a parameter.
 *
 *  best case : O(n)    when the list is already ordered.
 *  worst case: O(n²)   when the list is ordered with the complement to the compare function f
 *
 *  Iterates forwards and then backwards through the list inserting an element to
 *  an ordered sublist each iteration.
 *
 *  @param int* pointer to list
 *  @param size_t number of elements in list
 *  @param bool(*f) pointer to a compare function that takes two arguments and returns a bool
 *  @return int* ordered list
 */
int* insertion_sort(int* lst, size_t n, bool (*f)());

/** @brief merge two ordered lists
 *
 *  Returns a new list that is ordered, it does
 *  not mutate the original list.
 *  Merge two lists ordered by the same property f.
 *
 *  Iterates forwards and then backwards through the list inserting an element to
 *  an ordered sublist each iteration.
 *
 *  @param int* pointer to list 1
 *  @param n1 size of list 1
 *  @param int* pointer to list 2
 *  @param n2 size of list 2
 *  @param bool (*f)() property of ordering, f: (x, y) -> bool
 *
 *  @returns  NULL is lst1 or lst2 are not ordered by f.
 *            int* merged list otherwise.
 */
int* merge(int*, size_t, int*, size_t, bool (*f)());

/** @brief implementation of insertion sort
 *
 *  Returns a new list that is ordered, it does
 *  not mutate the original list.
 *  Order can be defined by a compare function as a parameter.
 *
 *  best case : O(nlog(n))
 *  worst case: O(nlog(n))
 *
 *  Divide the list in half recursively and merge the ordered sublists.
 *
 *  @param int* pointer to list
 *  @param size_t number of elements in list
 *  @param bool(*f) pointer to a compare function that takes two arguments and returns a bool
 *  @return int* ordered list
 */
int* merge_sort(int* lst, size_t n, bool (*f)());

/*

____ ____ ____ ____ ____ ____ _    ___  __   ____ ____
| . \| __\| . \|  _\|   || . \|\/\ |  \ | \|\| __\| __\
| __/|  ]_|  <_| _\ | . ||  <_|   \| . \|  \|| \__|  ]_
|/   |___/|/\_/|/   |___/|/\_/|/v\/|/\_/|/\_/|___/|___/


*/

// @author K_K, Jul 27, 2015
void time_execution(void (*f)());

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

/** @brief Creates a random list of integers.
 *
 *  Creates a random list of integers between a
 *  lower bound and an upper bound.
 *  @param size_t Number of elements list
 *  @param lower Lower bound
 *  @param upper Number of elements list
 *
 *  @return *int pointer to created list
 */
int* randint_list(int, int, int);

/** @brief check that a list is ordered via a function f
 *
 *  For every e_i element from a list check that
 *  the function satisfies f(e_i, e_{i+1}),
 *  for example if f is the function that represents less than
 *  is_ordered checks if the list satisfies that every element is
 *  less than the next position i.e. the list has an ascending order.
 *  @param int* pointer to list
 *  @param size_t number of elements in list
 *  @param bool(*f) pointer to a function that takes two arguments and returns a bool
 *
 *  @return bool if is ordered false otherwise
 */
bool is_ordered(int* lst, size_t n, bool (*f)());

/** @brief copy a list
 *
 *  @param int* pointer to list
 *  @param size_t number of elements in list
 *
 *  @return pointer to copy of list
 */
int* copy_list(int*, size_t);

/** @brief swap the values of two variables
 *
 *  @param int* pointer to a variable x
 *  @param int* pointer to a variable y
 *
 *  @return void
 */
void swap(int*, int*);

#endif

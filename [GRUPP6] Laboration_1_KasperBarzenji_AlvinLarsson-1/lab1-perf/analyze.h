#ifndef ANALYZE_H
#define ANALYZE_H

#define SIZE_START 512
// ÄNDRAT ITERATIONER TILL 1
#define ITERATIONS 4

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

// algorithm_t defines different algorithms
typedef enum
{
	bubble_sort_t,
	insertion_sort_t,
	quick_sort_t,
	linear_search_t,
	binary_search_t
} algorithm_t;

// case_t defines different cases
typedef enum
{
	best_t,
	worst_t,
	average_t,
} case_t;

typedef enum
{
	// bubble sort messages
	bubble_best_msg,
	bubble_worst_msg,
	bubble_avg_msg,
	// insertion sort messages
	insert_best_msg,
	insert_worst_msg,
	insert_avg_msg,
	// quick sort messages
	quick_best_msg,
	quick_worst_msg,
	quick_avg_msg,
	// linear search messages
	linear_best_msg,
	linear_worst_msg,
	linear_avg_msg,
	// binary search messages
	binary_best_msg,
	binary_worst_msg,
	binary_avg_msg,
} welcome_t;

// result_t defines a timed measurement for a given array size
typedef struct
{
	int size;
	double time;
} result_t;

typedef void (*func_sort)(int *, int);
typedef bool (*func_search)(const int *, int, int);

// benchmark benchmarks an algorithm a for a specific case c, writing n results
// to the result buffer buf
void benchmark(const algorithm_t a, const case_t c, result_t *buf, int n);

#endif
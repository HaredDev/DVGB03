#include "analyze.h"
#include "algorithm.h"

#define BILLION 1E9

//
// Private
//

// global struct clock_t variable used to clock functions
struct timespec start, stop;

static void add_ordered(int *arr, int size)
{
    // add elements to array in order
    for (int i = 0; i < size; i++)
    {
        *(arr + i) = i;
    }
}

static void add_reverse_ordered(int *arr, int size)
{
    // add elements to array in reverse order
    for (int i = size - 1; i > 0; i--)
    {
        *(arr + i) = i;
    }
}

static void add_random(int *arr, int size)
{
    // randomly generate elements into array
    for (int i = 0; i < size; i++)
    {
        // generate random numbers and put in array
        int r = rand() % size + 1;
        *(arr + i) = r;
    }
}

// option 0 == add_ordered, option 1 == add_reverse_ordered & option 2 == add_random
static double generate_time_sort(func_sort funParam, result_t *buf, int n, int option)
{
    // initialize a temporary array to memory
    int *tmp_array = (int *)malloc(buf->size * sizeof(int));

    if (option == 0)
    {
        add_ordered(tmp_array, buf->size);
    }
    else if (option == 1)
    {
        add_reverse_ordered(tmp_array, buf->size);
    }
    else if (option == 2)
    {
        add_random(tmp_array, buf->size);
    }
    else
    {
        return -1;
    }

    // tic
    clock_gettime(CLOCK_MONOTONIC, &start);
    // calling function
    funParam(tmp_array, buf->size);
    // toc
    clock_gettime(CLOCK_MONOTONIC, &stop);
    // get time in nano seconds
    buf->time = (stop.tv_sec - start.tv_sec) + (stop.tv_nsec - start.tv_nsec) / BILLION;
    // return time
    return buf->time;
}

static double generate_time_search(func_search funParam, result_t *buf, int n, int key)
{
    // initialize a temporary array to memory
    int *tmp_array = (int *)malloc(buf->size * sizeof(int));

    // for binary search to work it has to be an ordered array
    add_ordered(tmp_array, buf->size);

    // tic
    clock_gettime(CLOCK_MONOTONIC, &start);
    // calling function
    bool test = funParam(tmp_array, buf->size, key);

    if (test)
    {
        printf("Value: %d was found!\n", key);
    }
    else
    {
        // key we are looking for not found
    }

    // toc
    clock_gettime(CLOCK_MONOTONIC, &stop);
    // get time in nano seconds
    buf->time = (stop.tv_sec - start.tv_sec) + (stop.tv_nsec - start.tv_nsec) / BILLION;
    // return time
    printf("TIME: %f", buf->time);
    return buf->time;
}

//
// Public
//

void benchmark(algorithm_t a, const case_t c, result_t *buf, int n)
{
    // setting seed to null
    srand(time(NULL));
    // initialize value to the buf size as the start value (512)
    buf->size = SIZE_START;
    // allocating buf->size slots of integers in the array
    int *arr = (int *)malloc(buf->size * sizeof(int));

    // check wheter arr is successfully allocated into heap
    if (arr)
    {
        // used to store time and then the average time depending on number of ITERATIONS
        double time, avg_time, sum;

        switch (a)
        {
        // algorithm is bubble sort
        case 0:
            printf("BENCHMARKING BUBBLE SORT ALGORITHM\n");
            switch (c)
            {
            // bubble sort - best case
            case 0:
                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < ITERATIONS; j++)
                    {
                        time = generate_time_sort(bubble_sort, buf, n, 0);
                        sum += time;
                        printf("%d\t\t%f\t\t%e\t\t%e\t\t%e\n", buf->size, time, time / log10(n), time / n, time / n * log10(n));
                    }

                    avg_time = sum / ITERATIONS;
                    printf("_________________________________________________________________________________________________\n");
                    printf("AVG: %d\t%f\t\t%e\t\t%e\t\t%e\n", buf->size, avg_time, avg_time / log10(n), avg_time / n, avg_time / n * log10(n));
                    printf("_________________________________________________________________________________________________\n");
                    // increase size by 2
                    buf->size *= 2;
                    // set avg time, time and sum to 0
                    time = 0, avg_time = 0, sum = 0;
                    // allocate more memory to array
                    arr = (int *)realloc(arr, buf->size * sizeof(int));
                }
                break;
            // bubble sort - worst case
            case 1:
                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < ITERATIONS; j++)
                    {
                        time = generate_time_sort(bubble_sort, buf, n, 1);
                        sum += time;
                        printf("%d\t\t%f\t\t%e\t\t%e\t\t%e\n", buf->size, time, time / n * log10(n), time / n * n, time / n * n * n);
                    }

                    avg_time = sum / ITERATIONS;
                    printf("_________________________________________________________________________________________________\n");
                    printf("AVG: %d\t%f\t\t%e\t\t%e\t\t%e\n", buf->size, avg_time, avg_time / n * log10(n), avg_time / n * n, avg_time / n * n * n);
                    printf("_________________________________________________________________________________________________\n");
                    // increase size by 2
                    buf->size *= 2;
                    // set avg time, time and sum to 0
                    time = 0, avg_time = 0, sum = 0;
                    // allocate more memory to array
                    arr = (int *)realloc(arr, buf->size * sizeof(int));
                }
                break;
            // bubble sort - avg case
            case 2:
                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < ITERATIONS; j++)
                    {
                        time = generate_time_sort(bubble_sort, buf, n, 2);
                        sum += time;
                        printf("%d\t\t%f\t\t%e\t\t%e\n", buf->size, time, time / n * log10(n), time / n * n);
                    }

                    avg_time = sum / ITERATIONS;
                    printf("_________________________________________________________________________________________________\n");
                    printf("AVG: %d\t%f\t\t%e\t\t%e\n", buf->size, avg_time, avg_time / n * log10(n), avg_time / n * n);
                    printf("_________________________________________________________________________________________________\n");
                    // increase size by 2
                    buf->size *= 2;
                    // set avg time, time and sum to 0
                    time = 0, avg_time = 0, sum = 0;
                    // allocate more memory to array
                    arr = (int *)realloc(arr, buf->size * sizeof(int));
                }
                break;
            }
            break;
        // algorithm is insertion sort
        case 1:
            printf("BENCHMARKING INSERTION SORT ALGORITHM\n");
            switch (c)
            {
            case 0:
                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < ITERATIONS; j++)
                    {
                        time = generate_time_sort(insertion_sort, buf, n, 0);
                        sum += time;
                        printf("%d\t\t%f\t\t%e\t\t%e\n", buf->size, time, time / n * log10(n), time / n * n);
                    }

                    avg_time = sum / ITERATIONS;
                    printf("_________________________________________________________________________________________________\n");
                    printf("AVG: %d\t%f\t\t%e\t\t%e\n", buf->size, avg_time, avg_time / n * log10(n), avg_time / n * n);
                    printf("_________________________________________________________________________________________________\n");
                    // increase size by 2
                    buf->size *= 2;
                    // set avg time, time and sum to 0
                    time = 0, avg_time = 0, sum = 0;
                    // allocate more memory to array
                    arr = (int *)realloc(arr, buf->size * sizeof(int));
                }
                break;
            case 1:
                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < ITERATIONS; j++)
                    {
                        time = generate_time_sort(insertion_sort, buf, n, 1);
                        sum += time;
                        printf("%d\t\t%f\t\t%e\t\t%e\n", buf->size, time, time / n * log10(n), time / n * n);
                    }

                    avg_time = sum / ITERATIONS;
                    printf("_________________________________________________________________________________________________\n");
                    printf("AVG: %d\t%f\t\t%e\t\t%e\n", buf->size, avg_time, avg_time / n * log10(n), avg_time / n * n);
                    printf("_________________________________________________________________________________________________\n");
                    // increase size by 2
                    buf->size *= 2;
                    // set avg time, time and sum to 0
                    time = 0, avg_time = 0, sum = 0;
                    // allocate more memory to array
                    arr = (int *)realloc(arr, buf->size * sizeof(int));
                }
                break;
            case 2:
                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < ITERATIONS; j++)
                    {
                        time = generate_time_sort(insertion_sort, buf, n, 2);
                        sum += time;
                        printf("%d\t\t%f\t\t%e\t\t%e\n", buf->size, time, time / n * log10(n), time / n * n);
                    }

                    avg_time = sum / ITERATIONS;
                    printf("_________________________________________________________________________________________________\n");
                    printf("AVG: %d\t%f\t\t%e\t\t%e\n", buf->size, avg_time, avg_time / n * log10(n), avg_time / n * n);
                    printf("_________________________________________________________________________________________________\n");
                    // increase size by 2
                    buf->size *= 2;
                    // set avg time, time and sum to 0
                    time = 0, avg_time = 0, sum = 0;
                    // allocate more memory to array
                    arr = (int *)realloc(arr, buf->size * sizeof(int));
                }
                break;
            }
            break;
        // algorithm is quick sort
        case 2:
            printf("BENCHMARKING QUICK SORT ALGORITHM\n");
            switch (c)
            {
            case 0:
                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < ITERATIONS; j++)
                    {
                        time = generate_time_sort(quick_sort, buf, n, 0);
                        sum += time;
                        printf("%d\t\t%f\t\t%e\t\t%e\n", buf->size, time, time / n * log10(n), time / n * n);
                    }

                    avg_time = sum / ITERATIONS;
                    printf("_________________________________________________________________________________________________\n");
                    printf("AVG: %d\t%f\t\t%e\t\t%e\n", buf->size, avg_time, avg_time / n * log10(n), avg_time / n * n);
                    printf("_________________________________________________________________________________________________\n");
                    // increase size by 2
                    buf->size *= 2;
                    // set avg time, time and sum to 0
                    time = 0, avg_time = 0, sum = 0;
                    // allocate more memory to array
                    arr = (int *)realloc(arr, buf->size * sizeof(int));
                }
                break;
            case 1:
                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < ITERATIONS; j++)
                    {
                        time = generate_time_sort(quick_sort, buf, n, 1);
                        sum += time;
                        printf("%d\t\t%f\t\t%e\t\t%e\n", buf->size, time, time / n * log10(n), time / n * n);
                    }

                    avg_time = sum / ITERATIONS;
                    printf("_________________________________________________________________________________________________\n");
                    printf("AVG: %d\t%f\t\t%e\t\t%e\n", buf->size, avg_time, avg_time / n * log10(n), avg_time / n * n);
                    printf("_________________________________________________________________________________________________\n");
                    // increase size by 2
                    buf->size *= 2;
                    // set avg time, time and sum to 0
                    time = 0, avg_time = 0, sum = 0;
                    // allocate more memory to array
                    arr = (int *)realloc(arr, buf->size * sizeof(int));
                }
                break;
            case 2:
                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < ITERATIONS; j++)
                    {
                        time = generate_time_sort(quick_sort, buf, n, 2);
                        sum += time;
                        printf("%d\t\t%f\t\t%e\t\t%e\n", buf->size, time, time / n * log10(n), time / n * n);
                    }

                    avg_time = sum / ITERATIONS;
                    printf("_________________________________________________________________________________________________\n");
                    printf("AVG: %d\t%f\t\t%e\t\t%e\n", buf->size, avg_time, avg_time / n * log10(n), avg_time / n * n);
                    printf("_________________________________________________________________________________________________\n");
                    // increase size by 2
                    buf->size *= 2;
                    // set avg time, time and sum to 0
                    time = 0, avg_time = 0, sum = 0;
                    // allocate more memory to array
                    arr = (int *)realloc(arr, buf->size * sizeof(int));
                }
                break;
            }
            break;
        // algorithm is linear search
        case 3:
            printf("BENCHMARKING LINEAR SEARCH ALGORITHM\n");
            switch (c)
            {
            case 0:
                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < ITERATIONS; j++)
                    {
                        // looking for value 0, meaning it first element in array
                        time = generate_time_search(linear_search, buf, n, 0);
                        sum += time;
                        printf("%d\t\t%f\t\t%e\t\t%e\n", buf->size, time, time / n * log10(n), time / n * n);
                    }

                    avg_time = sum / ITERATIONS;
                    printf("_________________________________________________________________________________________________\n");
                    printf("AVG: %d\t%f\t\t%e\t\t%e\n", buf->size, avg_time, avg_time / n * log10(n), avg_time / n * n);
                    printf("_________________________________________________________________________________________________\n");
                    // increase size by 2
                    buf->size *= 2;
                    // set avg time, time and sum to 0
                    time = 0, avg_time = 0, sum = 0;
                    // allocate more memory to array
                    arr = (int *)realloc(arr, buf->size * sizeof(int));
                }
                break;
            case 1:
                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < ITERATIONS; j++)
                    {
                        // worse case would be to go through whole list, meaning the end of array
                        time = generate_time_search(linear_search, buf, n, buf->size - 1);
                        sum += time;
                        printf("%d\t\t%f\t\t%e\t\t%e\n", buf->size, time, time / n * log10(n), time / n * n);
                    }

                    avg_time = sum / ITERATIONS;
                    printf("_________________________________________________________________________________________________\n");
                    printf("AVG: %d\t%f\t\t%e\t\t%e\n", buf->size, avg_time, avg_time / n * log10(n), avg_time / n * n);
                    printf("_________________________________________________________________________________________________\n");
                    // increase size by 2
                    buf->size *= 2;
                    // set avg time, time and sum to 0
                    time = 0, avg_time = 0, sum = 0;
                    // allocate more memory to array
                    arr = (int *)realloc(arr, buf->size * sizeof(int));
                }
                break;
            case 2:
                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < ITERATIONS; j++)
                    {
                        // avg case is random number depending on buf->size
                        int num = rand() % buf->size;
                        time = generate_time_search(linear_search, buf, n, num);
                        printf("Random number is: %d\n", num);
                        sum += time;
                        printf("%d\t\t%f\t\t%e\t\t%e\n", buf->size, time, time / n * log10(n), time / n * n);
                    }

                    avg_time = sum / ITERATIONS;
                    printf("_________________________________________________________________________________________________\n");
                    printf("AVG: %d\t%f\t\t%e\t\t%e\n", buf->size, avg_time, avg_time / n * log10(n), avg_time / n * n);
                    printf("_________________________________________________________________________________________________\n");
                    // increase size by 2
                    buf->size *= 2;
                    // set avg time, time and sum to 0
                    time = 0, avg_time = 0, sum = 0;
                    // allocate more memory to array
                    arr = (int *)realloc(arr, buf->size * sizeof(int));
                }
                break;
            }
            break;
        // algorithm is binary search
        case 4:
            printf("BENCHMARKING BINARY SEARCH ALGORITHM\n");
            switch (c)
            {
            case 0:
                for (int i = 0; i < n; i++)
                {
                    int size = buf->size;
                    for (int j = 0; j < ITERATIONS; j++)
                    {
                        // best case is middle value which is array size divided by half
                        time = generate_time_search(binary_search, buf, n, size / 2);
                        sum += time;
                        printf("%d\t\t%f\t\t%e\t\t%e\n", buf->size, time, time / n * log10(n), time / n * n);
                    }

                    avg_time = sum / ITERATIONS;
                    printf("_________________________________________________________________________________________________\n");
                    printf("AVG: %d\t%f\t\t%e\t\t%e\n", buf->size, avg_time, avg_time / n * log10(n), avg_time / n * n);
                    printf("_________________________________________________________________________________________________\n");
                    // increase size by 2
                    buf->size *= 2;
                    // set avg time, time and sum to 0
                    time = 0, avg_time = 0, sum = 0;
                    // allocate more memory to array
                    arr = (int *)realloc(arr, buf->size * sizeof(int));
                    printf("END\n");
                }
                break;
            case 1:
                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < ITERATIONS; j++)
                    {
                        // worst case is either most left side or most right side
                        // since its reverse order i chose the most right side
                        time = generate_time_search(binary_search, buf, n, 0);
                        sum += time;
                        printf("%d\t\t%f\t\t%e\t\t%e\n", buf->size, time, time / n * log10(n), time / n * n);
                    }

                    avg_time = sum / ITERATIONS;
                    printf("_________________________________________________________________________________________________\n");
                    printf("AVG: %d\t%f\t\t%e\t\t%e\n", buf->size, avg_time, avg_time / n * log10(n), avg_time / n * n);
                    printf("_________________________________________________________________________________________________\n");
                    // increase size by 2
                    buf->size *= 2;
                    // set avg time, time and sum to 0
                    time = 0, avg_time = 0, sum = 0;
                    // allocate more memory to array
                    arr = (int *)realloc(arr, buf->size * sizeof(int));
                }
                break;
            case 2:
                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < ITERATIONS; j++)
                    {
                        //  average is emulated by randomizing a number depending on buf size
                        time = generate_time_search(binary_search, buf, n, rand() % buf->size);
                        sum += time;
                        printf("%d\t\t%f\t\t%e\t\t%e\n", buf->size, time, time / n * log10(n), time / n * n);
                    }

                    avg_time = sum / ITERATIONS;
                    printf("_________________________________________________________________________________________________\n");
                    printf("AVG: %d\t%f\t\t%e\t\t%e\n", buf->size, avg_time, avg_time / n * log10(n), avg_time / n * n);
                    printf("_________________________________________________________________________________________________\n");
                    // increase size by 2
                    buf->size *= 2;
                    // set avg time, time and sum to 0
                    time = 0, avg_time = 0, sum = 0;
                    // allocate more memory to array
                    arr = (int *)realloc(arr, buf->size * sizeof(int));
                }
                break;
            }
            break;
        }

        // free arr pointer
        free(arr);
    }
    else
    {
        printf("Allocation failed! Aborting\n");
    }
}
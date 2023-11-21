#include "analyze.h"
#include "algorithm.h"

#define BILLION 1E9

//
// Private
//

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

static double generate_time_search(func_search funcpara, result_t *buf, int n, int key)
{

    int *tmp_array = (int*)malloc(buf->size * sizeof(int));

    add_ordered(tmp_array, buf->size);

    clock_gettime(CLOCK_MONOTONIC, &start);

    bool test = funcpara(tmp_array, buf->size, key); 

    if (test)
    {
        printf("Value: %d was found!\n", key);
    }
    else
    {
        printf("Value: %d was not found!\n", key);
    }

    clock_gettime(CLOCK_MONOTONIC, &stop);

    buf->time = (stop.tv_sec - start.tv_sec) + (stop.tv_nsec - start.tv_nsec) / BILLION;

    printf("TIME: %f", buf->time);
    return buf->time;

}

static double generate_time_sort(func_sort funcpara, result_t *buf, int n, int option)
{

    int *tmp_array = (int*)malloc(buf->size * sizeof(int));

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

    clock_gettime(CLOCK_MONOTONIC, &start);

    funcpara(tmp_array, buf->size);

    clock_gettime(CLOCK_MONOTONIC, &stop);

    buf->time = (stop.tv_sec - start.tv_sec) + (stop.tv_nsec - start.tv_nsec) / BILLION;

    return buf->time;

}

//
// Public
//
void benchmark(const algorithm_t a, const case_t c, result_t *buf, int n)
{
    srand(time(NULL));

    buf->time = SIZE_START;

    int *arr = (int *)malloc(buf->size * sizeof(int));

    // algorithm is bubble sort
    if(arr)
    {

        // used to store time and then the average time depending on number of ITERATIONS
        double time, avg_time, sum;

        if(a == bubble_sort_t)
        {
                
            printf("BENCHMARKING BUBBLE SORT ALGORITHM!\n");

            for(int i = 0; i < n; i++)
            {
                for(int j = 0; j < ITERATIONS; j++)
                {
                    switch(c)
                    {
                        case best_t:
                            time = generate_time_sort(bubble_sort, buf, n, 0);
                            sum += time;
                            printf("%d\t\t%f\t\t%e\t\t%e\t\t%e\n", buf->size, time, time / log10(n), time / n, time / n * log10(n));
                        break;
                        case worst_t:
                            time = generate_time_sort(bubble_sort, buf, n, 1);
                            sum += time;
                            printf("%d\t\t%f\t\t%e\t\t%e\t\t%e\n", buf->size, time, time / n * log10(n), time / n * n, time / n * n * n);
                        break;
                        case average_t:
                            time = generate_time_sort(bubble_sort, buf, n, 2);
                            sum += time;
                            printf("%d\t\t%f\t\t%e\t\t%e\n", buf->size, time, time / n * log10(n), time / n * n);
                        break;
                    }
                }

                avg_time = sum / ITERATIONS;

                printf("_________________________________________________________________________________________________\n");
                switch(c)
                {
                    case best_t:
                        printf("AVG: %d\t%f\t\t%e\t\t%e\t\t%e\n", buf->size, avg_time, avg_time / log10(n), avg_time / n, avg_time / n * log10(n));
                    break;
                    case worst_t:
                        printf("AVG: %d\t%f\t\t%e\t\t%e\t\t%e\n", buf->size, avg_time, avg_time / n * log10(n), avg_time / n * n, avg_time / n * n * n);
                    break;
                    case average_t:
                        printf("AVG: %d\t%f\t\t%e\t\t%e\n", buf->size, avg_time, avg_time / n * log10(n), avg_time / n * n);
                    break;
                }
                printf("_________________________________________________________________________________________________\n");

                // increase size by 2
                buf->size *= 2;
                // set avg time, time and sum to 0
                time = 0, avg_time = 0, sum = 0;
                // allocate more memory to array
                arr = (int *)realloc(arr, buf->size * sizeof(int));

            }
        }   
            // algorithm is insertion sort
            if(a == insertion_sort_t)
            {

                printf("BENCHMARKING INSERTION SORT ALGORITHM!\n");

                for(int i = 0; i < n; i++)
                {
                    for(int j = 0; j < ITERATIONS; j++)
                    {
                        time = generate_time_sort(insertion_sort, buf, n, c);
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
            }    

            // algorithm is quick sort
            if(a == quick_sort_t)
            {

                printf("BENCHMARKING QUICK SORT ALGORITHM!\n");

                for(int i = 0; i < n; i++)
                {
                    for(int j = 0; j < ITERATIONS; j++)
                    {
                        time = generate_time_sort(quick_sort, buf, n, c);
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
            }    

            // algorithm is linear search
            if(a == linear_search_t)
            {

                printf("BENCHMARKING LINEAR SEARCH ALGORITHM!\n");

                for(int i = 0; i < n; i++)
                {
                    for(int j = 0; j < ITERATIONS; j++)
                    {
                        switch(c)
                        {
                            case 0:
                                time = generate_time_search(linear_search, buf, n, 0);
                            break;
                            case 1:
                                time = generate_time_search(linear_search, buf, n, buf->size-1);
                            break;
                            case 2:
                                time = generate_time_search(linear_search, buf, n, rand() % buf->size);
                            break;
                        }
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
            }    

            // algorithm is binary search
            if(a == binary_search_t)
            {

                printf("BENCHMARKING BINARY SEARCH ALGORITHM!\n");

                for(int i = 0; i < n; i++)
                {
                    for(int j = 0; j < ITERATIONS; j++)
                    {
                        switch(c)
                        {
                            case 0:
                                time = generate_time_search(binary_search, buf, n, buf->size/2);
                            break;
                            case 1:
                                time = generate_time_search(binary_search, buf, n, 0);
                            break;
                            case 2:
                                time = generate_time_search(binary_search, buf, n, rand() % buf->size);
                            break;
                        }
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
            } 


        // free arr pointer
        free(arr);   

        } 
        else 
        {
            printf("Allocation failed! Aborting\n");
        }

    }



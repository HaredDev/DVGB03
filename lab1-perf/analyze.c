#include "analyze.h"
#include "algorithm.h"

//
// Private
//

//
// Public
//
void benchmark(const algorithm_t a, const case_t c, result_t *buf, int n)
{
    srand(time(null));

    buf->time = SIZE_START;

    int* arr = (int*)malloc(buf->size * sizeof(int));

}

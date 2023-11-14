#include "algorithm.h"
#include "analyze.h"

//
// Private
//

//
// Public
//
void bubble_sort(int *a, int n)
{
	// bool isSorted = true; //the assumption is that the array is sorted
	int sort = 1;

	// int num = 0;
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - 1; j++)
		{
			// num++;
			if (a[j] > a[j + 1]) // if two elements are misaligned then array is not sorted
			{
				// isSorted = false;
				sort = 0;
				int tmp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = tmp;
			}
		}

		if (sort == 1)
		{ // if array is already sorted then no further iterations
			// printf("break! i: %d\n", i);
			break;
		}

		sort = 1; // resets sorted state so it can be determined again next iteration
	}
}

void insertion_sort(int *a, int n)
{
	for (int i = 0; i < n; i++)
	{
		int compare = a[i];
		int switchpos = i;
		for (int z = i; z >= 0; z--)
		{
			if (compare < a[z])
			{
				int temp = a[z];
				a[switchpos] = temp;
				a[z] = compare;
				switchpos = z;
			}
		}
	}
}

int partition(int *a, int low, int high)
{
	int pivot = a[low];
	int leftwall = low;

	for (int i = low + 1; i < high; i++)
	{
		if (a[i] < pivot)
		{
			int temp = a[leftwall];
			a[leftwall] = a[i];
			a[i] = temp;
			leftwall += 1;
		}
	}

	int pivotPos; // search through array to find pivot value
	for (int i = 0; i < high; i++)
	{
		if (a[i] == pivot)
		{
			pivotPos = i;
		}
	}

	int temp = a[leftwall];
	a[leftwall] = pivot;
	a[pivotPos] = temp;

	return leftwall;
}

void quickSort(int *a, int low, int high)
{ // quick_sorts elaka storebror(han är smartare)
	if (low < high)
	{
		int pivot_location = partition(a, low, high);
		quickSort(a, low, pivot_location);
		quickSort(a, pivot_location + 1, high);
	}
}

void quick_sort(int *a, int n)
{
	quickSort(a, 0, n);
}

bool linear_search(const int *a, int n, int v)
{
	for (int i = 0; i < n; i++)
	{
		// linear search, looping through whole array looking for the key
		if (a[i] == v)
		{
			return true;
		}
	}
	return false;
}

bool binary_search(const int *a, int n, int v)
{
	// need to find low, middle and high
	int middle, low, high;

	// lowest number is now our first element in the array
	low = a[0];
	// highest number is now the last element in the array
	high = n;

	printf("Low: %d, High: %d\n", low, high);

	while (low <= high)
	{
		// middle number is low + high divided by 2
		middle = (low + high) / 2;

		// our searched value is middle index in our array
		// best case
		if (a[middle] == v)
		{
			return true;
		}
		// lower part of array
		else if (a[middle] < v)
		{
			// change low to be middle + 1
			low = middle + 1;
		}
		// upper part of array
		else
		{
			// set low to middle - 1
			high = middle - 1;
		}
	}

	return false;
}

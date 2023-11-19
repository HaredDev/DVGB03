#include "algorithm.h"

//
// Private
//

//
// Public
//
void bubble_sort(int *a, int n)
{
	int sort = 1;

	for(int i = 0; i < n-1; i++)
	{
		for(int j = 0; j < n-1; j++)
		{
			if(a[j] > a[j+1])
			{
				sort = 0;
				int tmp = a[j];
				a[j] = a[j+1];
				a[j+1] = tmp;
			}
		}

		if(sort == 1)
			break;

		sort = 1;

	}

}

void insertion_sort(int *a, int n)
{
	for(int i = 0; i < n; i++)
	{
		int comp = a[i];
		int switchpos = i;
		for(int j = i; j >= i; j--)
		{
			if(comp < a[j])
			{
				int tmp = a[j];
				a[j] = comp;
				a[switchpos] = tmp;
				switchpos = j;
			}
		}
	}
}

int partition(int *a, int low, int high)
{
	int pivot = a[low];
	int left = low;
	for(int i = low+1; i < high; i++)
	{
		if(a[i] < pivot)
		{
			int tmp = a[left];
			a[left] = a[i];
			a[i] = tmp;
			left += 1;
		}
	}

	int pivotloc;
	for(int i = 0; i < high; i++)
	{
		if(a[i] == pivot)
			pivotloc = i;
	}

	int tmp = a[left];
	a[left] = pivot;
	a[pivotloc] = tmp;

	return left;

}

void quickSort(int *a, int low, int high)
{
	if(low < high)
	{
		int pivot = partition(a, low, high);
		quickSort(a, low, pivot);
		quickSort(a, pivot+1, high);
	}
}

void quick_sort(int *a, int n)
{
	quickSort(a, 0, n);
}

bool linear_search(const int *a, int n, int v)
{
	for(int i = 0; i < n; i++)
	{
		if(a[i] == v)
			return true;
	}
	return false;
}

bool binary_search(const int *a, int n, int v)
{

	int low, middle, high;

	low = a[0];
	high = n;

	printf("Low: %d, High: %d\n", low, high);

	while(low <= high)
	{
		middle = (low+high)/2;

		if(a[middle] == v)
			return true;
		else if(a[middle] < v)
			low = middle+1;
		else
			high = middle-1;

	}

	return false;
}

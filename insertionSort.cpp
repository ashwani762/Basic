// DSA.cpp : Defines the entry point for the application.
//

#include "header.h"

using namespace std;

void insertionSort(int* a, int n)
{
	for (int i = 1; i < n; ++i)
	{
		int curr = a[i];
		int j = i - 1;
		while ((j >= 0) && (a[j] > curr))
		{
			a[j + 1] = a[j];
			j--;
		}

		a[j + 1] = curr;
	}
}

void selectionSort(int* a, int n)
{
	for (int i = 0; i < n; ++i)
	{
		int min = i;
		for (int j = i + 1; j < n; ++j)
		{
			if (a[j] < a[min])
				min = j;
		}
		swap(a[i], a[min]);
	}
}

void merge(int* a, int p, int q, int r)
{
	int n1 = q - p + 1;
	int n2 = r - q;

	int *L = new int[n1], *R = new int[n2];

	for (int i = 0; i < n1; ++i) L[i] = a[p + i];
	for (int j = 0; j < n2; ++j) R[j] = a[q + j + 1];

	int i = 0, j = 0;

	int k = p;

	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			a[k] = L[i];
			++i;
		}
		else
		{
			a[k] = R[j];
			++j;
		}
		++k;
	}

	while (i < n1)
	{
		a[k] = L[i];
		++i;
		++k;
	}

	while (j < n2)
	{
		a[k] = R[j];
		++j;
		++k;
	}
	delete[] L;
	delete[] R;
}


void mergeSort(int *a, int p, int r) 
{
	if (p < r)
	{
		int q = p + (r - p) / 2;
		mergeSort(a, p, q);
		mergeSort(a, q + 1, r);
		merge(a, p, q, r);
	}
}

int main()
{
	int a[] = { 4,2,6,7,1,3,2,6,8 };
	//selectionSort(a, 9);
	mergeSort(a, 0, 8);

	for (int i = 0; i < 9; ++i)
	{
		cout << a[i] << " ";
	}
	return 0;
}

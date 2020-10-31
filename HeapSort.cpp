#include "header.h"

U_NS_STD

//inline auto parent(int i)
//{
//	return i >> 1;
//}
//
//inline auto left(int i)
//{
//	return (i << 1) + 1;
//}
//
//inline auto right(int i)
//{
//	return (i << 1) + 2;
//}

void heapify(vector<int>& arr, int n, int i)
{
    int largest = i; // Initialize largest as root 
    int l = 2 * i + 1; // left = 2*i + 1 
    int r = 2 * i + 2; // right = 2*i + 2 

    // If left child is larger than root 
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // If right child is larger than largest so far 
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // If largest is not root 
    if (largest != i)
    {
        swap(arr[i], arr[largest]);

        // Recursively heapify the affected sub-tree 
        heapify(arr, n, largest);
    }
}

// main function to do heap sort 
void heapSort(vector<int> &arr)
{
    // Build heap (rearrange array) 
    for (int i = arr.size() / 2 - 1; i >= 0; i--)
        heapify(arr, arr.size(), i);

    // One by one extract an element from heap 
    for (int i = arr.size() - 1; i > 0; i--)
    {
        // Move current root to end 
        swap(arr[0], arr[i]);

        // call max heapify on the reduced heap 
        heapify(arr, i, 0);
    }
}


SM
	vector<int> a{4,1,3,2,16,9,10,14,8,7};
	heapSort(a);
	for (int x : a)
	{
		cout << x << " ";
	}
EM

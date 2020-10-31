#include "header.h"

U_NS_STD

int partition(vector<int>& a, int p, int r)
{
    int pivot = a[r];
    int i = (p - 1);

    for (int j = p; j < r; ++j)
    {
        if (a[j] <= pivot)
        {
            i++;
            swap(a[i], a[j]);
        }
    }

    swap(a[i + 1], a[r]);
    return (i + 1);

}
 
void QuickSort(vector<int>& a, int p, int r)
{
    if (p < r)
    {
        int q = partition(a, p, r);
        QuickSort(a, p, q - 1);
        QuickSort(a, q + 1, r);
    }
}


SM
    vector<int> a{ 4,1,3,2,16,9,10,14,8,7 };
    QuickSort(a, 0, a.size() - 1);
    for (int x : a)
    {
        cout << x << " ";
    }
EM

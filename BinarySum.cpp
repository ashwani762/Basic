#include "header.h"

using namespace std;

int binarySum(int* a, int i, int n)
{
	if (n == 1)
		return a[i];
	return binarySum(a, i, n / 2) + binarySum(a, i + (n / 2), (n + 1) / 2);
}

int main()
{
	int a[] = { 1,1,1,1,1,1,1,1,1,1 };
	int sum = binarySum(a, 0, 10); 

	cout << sum;

	return 0;
}
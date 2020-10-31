#include "header.h"

U_NS_STD

tuple<int, int, int> findMaxCrossSubArray(int* a, int low, int mid, int high)
{
	int max_left, max_right;
	int left_sum = numeric_limits<int>::min();
	int sum = 0;
	for (int i = mid; i >= low; --i)
	{
		sum = sum + a[i];
		if (sum > left_sum)
		{
			left_sum = sum;
			max_left = i;
		}
	}

	int right_sum = numeric_limits<int>::min();
	sum = 0;
	for (int j = mid + 1; j <= high; ++j)
	{
		sum = sum + a[j];
		if (sum > right_sum)
		{
			right_sum = sum;
			max_right = j;
		}
	}

	return { max_left, max_right, left_sum + right_sum };
}

tuple<int, int, int> findMaxSubArray(int* a, int low, int high)
{
	if (high == low)
		return { low, high, a[low] };
	else
	{
		int mid = low + (high - low) / 2;

		// same as tie(var1, var2) = function returning tuples CXX11
		auto [left_low, left_high, left_sum] = findMaxSubArray(a, low, mid);
		auto [right_low, right_high, right_sum] = findMaxSubArray(a, mid + 1, high);
		auto [cross_low, cross_high, cross_sum] = findMaxCrossSubArray(a, low, mid, high);

		if (left_sum >= right_sum && left_sum >= cross_sum)
			return { left_low, left_high, left_sum };
		else if (right_sum >= left_sum && right_sum >= cross_sum)
			return { right_low, right_high, right_sum };
		else
			return { cross_low, cross_high, cross_sum };
	}
}

auto main() -> int {
	int arr[] = { 13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7 };
	int n = sizeof(arr) / sizeof(arr[0]);
	
	auto [i, j, sum] = findMaxSubArray(arr, 0, n-1);

	cout << i << " " << j << " " << sum;
	return 0;
}
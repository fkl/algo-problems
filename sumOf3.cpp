// find 3 numbers from an array whose sum is n
// For now assume array is sorted (which can be sorted in nlogn separately.
int sum_of_3(int arr[], int size, int n)
{
	// loop all elements in arr.
	// For each arr[idx], find two numbers x and y, such that x+y = n-arr[idx]

	for(int i=0; i<size; i++)
	{
		int sum = n-arr[i];
		int x_idx, y_idx;

		// Find only one such pair whose sum is equal to n-arr[i]

		// IMP: x_idx can start from i+1 because i is already checked for other combinations.
		for(x_idx=i+1, y_idx=size-1; x_idx < y_idx;)
		{
			int cur_sum = arr[x_idx]+arr[y_idx];

			if(cur_sum < sum)
				x_idx++; // if total sum is less, increment the left side idx so we can get a bigger value
			else if(cur_sum > sum)
				y_idx--;

			else { // found one
				printf("numbers are %d %d %d\n", arr[i], arr[x_idx], arr[y_idx]);
				return 1;
			}

		}
	}

	printf("Failed finding a set\n");
	return -1;

}

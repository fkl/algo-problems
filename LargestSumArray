int mssl(int a[], int s)
{
//There's actually a very elegant, very efficient solution using dynamic programming. It takes O(1) space, and O(n) time -- this can't be beat!
//Define A to be the input array (zero-indexed) and B[i] to be the maximum sum over all sublists ending at, but not including position i (i.e. all sublists A[j:i]).
// Therefore, B[0] = 0, and B[1] = max(B[0]+A[0], 0), B[2] = max(B[1]+A[1], 0), B[3] = max(B[2]+A[2], 0), and so on. Then, clearly, the solution is given simply by max(B[0], ..., B[n]).
//Since every B value depends only on the previous B, we can avoid storing the whole B array, thus giving us our O(1) space guarantee.
//def mssl(l):
//    best = cur = 0
//    for i in l:
//        cur = max(cur + i, 0)
//        best = max(best, cur)
//    return best

	// find sum of array ending at index i, return the highest one
	int g_sum = -1, cur_sum=-1;
	int st, end;

	for(int c=0; c<s; c++) {
		if (cur_sum < 0) {
			cur_sum = a[c];
			st = c;
		}

		else cur_sum += a[c];

		if(cur_sum > g_sum) {
			g_sum = cur_sum;
			end = c;
		}
	}

	for(; st <=end; st++)
		printf("%d\t", a[st]);
	printf("\n");

	return g_sum;
}

// Likely REPEAT

// find consequtive sub array with largest sum in a given array
// print largest sum for now
int largest_sub_array(int arr[], int size)
{
	int gmax, cur_max;
	gmax=-1;
	cur_max = -1;

	// find sum of array ending at current index
	for(int i=0; i<size; i++)
	{
		if(cur_max < 0)
			cur_max = arr[i];
		else
			cur_max += arr[i];

		if(cur_max > gmax)
			gmax = cur_max;
	}

	return gmax;
}

// find a number which occurs only once in an array. All others exist twice.
// NOTE Remaining numbers occurring twice vs thrice have different approaches
int find_non_repeated_num(int a[], int size)
{
	int res = 0;

	for(int i=0; i<size; i++) {
		res = res ^ a[i];
	}

	return res;
}



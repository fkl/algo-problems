// largest consequtive sum in array
int subsum_conseq(int a[], int size)
{
	// find sum of array ending at each index using prior sums.
	// Keep one global and one current max

	int g_max = -1, c_max=-1;
	int st, end;

	for(int i=0; i<size; ++i)
	{
		if(c_max < 0) {
			c_max = a[i];
			st = i; // array starts here
		}
		else
			c_max += a[i];

		if(c_max > g_max) {
			g_max = c_max;
			end = i; // ends here
		}
	}

	while(st<=end)
		printf("%d\t", a[st++]);

	printf("\n");

	return g_max;
}


int main()
{
	//INT A[] = {-4,2,-5,1,2,3,6,-13,7,6};

	//PRINTF("SUM IS %D \N", SUBSUM_CONSEQ(A, SIZEOF(A)/SIZEOF(INT)));

}

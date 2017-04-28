#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>


#define MAX 10


int coin_change(int denom[], int size, int sum)
{
	int *res = (int *)malloc( (sum+1) * sizeof(int));
	memset(res, 0,  (sum+1) * sizeof(int));

	
	if(!res)
		return -1; // error failed allocation

	res[0] = 1;

	//for(int a=0; a<  (sum+1) * sizeof(int); ++a)
	//	printf("%d\t", res[a]);

	// for each denom
	for(int i=0; i<size; ++i)
	{
 		int d = denom[i];
		// for each sum value starting from denom[i] to sum
		for(int j=d; j<sum+1; j++) {
			res[j] = res[j] + res[j-d];
			//printf("res[j]=%d\t", res[j]);
		}
	
	}

	return res[sum];
}


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

	//INT D[] ={1,2,5};

	//FOR(INT C=1; C<=10; ++C) {
	//	INT WAYS = COIN_CHANGE(D, SIZEOF(D)/SIZEOF(INT), C);
	//	PRINTF("%D CAN BE SUMMED IN %D WAYS\N", C, WAYS);
	//}

	_getche();
	return 0;
}

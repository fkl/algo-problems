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


int main()
{
	FOR(INT C=1; C<=10; ++C) {
		INT WAYS = COIN_CHANGE(D, SIZEOF(D)/SIZEOF(INT), C);
		PRINTF("%D CAN BE SUMMED IN %D WAYS\N", C, WAYS);
	}

	_getche();
	return 0;
}

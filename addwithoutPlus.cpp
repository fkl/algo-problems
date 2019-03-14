#if 0
int Add(int x, int y)
{
    // Iterate till there is no carry  
    while (y != 0)
    {
        // carry now contains common set bits of x and y
        int carry = x & y;  
 
        // Sum of bits of x and y where at least one of the bits is not set
        x = x ^ y; 
 
        // Carry is shifted by one so that adding it to x gives the required sum
        y = carry << 1;
    }
    return x;
}
#endif

// Add A and B without + operator
int add(int a, int b)
{
	// idea is that for bits which are not set in both a and b, XOR would pick sum of bits
	// For bits which are both set, & would get carry
	int carry, sum = a;

	while(b > 0)
	{
		carry = sum & b;
		sum = sum ^ b;
		b = carry << 1;
	}

	return sum;
}

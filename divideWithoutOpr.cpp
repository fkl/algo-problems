// Find x / y (integer division) without using divison or multiplication operator
int divide(int divident, int divisor) // 8/3
{
	int d = divisor;
	int q = 1; // quotient starts from 0 here

	// TODO - Handle special cases latter. (divide by 0), numbers being same or divisor being greater. First get the general algo

	//while( d < divident) {
	//	d = d + divisor; // really slow but for 8/3 add 3 every time 
	//	q+=1; q starts from zero in this case
	//}

	if(divisor == 0)
		return -1;
	if(divisor == divident)
		return 1;

	if(divisor > divident)
		return 0;

	// Instead try doubling d every time
	while( d < divident) {
		d = d << 1; 
		q = q << 1;// q starts from 1 here
	}

	if (d > divident) {
		d = d >> 1;
		q = q >> 1;
		return q + divide(divident-d, divisor);
	}

	return q;
}

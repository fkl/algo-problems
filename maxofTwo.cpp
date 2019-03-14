
int max(int a, int b)
{
	int diff = a-b;
	int sign = (diff >> 31) & 1;

	// if a < b, diff < 0 and sign is 1. So equation becomes a - diff. 
	// Substitute a-b for diff (from first eq) we get max = a - (a-b) so return b
	// if a > b, diff > 0 and sign is 0. So a - 0 * diff returns a
	int max = a - sign * diff;
	return  max;
}

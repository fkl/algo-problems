
// Find all palindromic substrings in a given string.

// helper function
//is_palindrome() not needed.

void print(char *a, int st, int end)
{
	for(int i=st; i<=end; i++)
		printf("%c", a[i]);
	printf("\n");
}

void extend_odd(char *s, int start, int size)
{
	int ofset=1; // offset on both sides 

	while(start-ofset >=0 && start+ofset < size) { // condition latter
		if (s[start-ofset] == s[start+ofset])
			print(s, start-ofset, start+ofset);
			//printf() // print string between -ofset .. start ... +ofset 
		else
			break;
		ofset++;
	}
}

void find_all_pals(char *s)
{
	int size = strlen(s);

	// for each position, assume palindrome is centered around it
	for(int idx=0; idx<size; idx++)
	{
		extend_odd(s, idx, size);
		//extend_even();
	}

}


int main()
{
	find_all_pals("ababa");
}

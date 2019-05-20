// Decrypt a given text which used two large primes from a list of primes
// Primes are first computed using Sieve of Erth algorithm
// The challenge is finding which primes were used and then computing original
// chars back using the relative prime index (i.e. first to last)

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <map>
#include <unordered_map>
#include <vector>
#include <cstdlib>
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* qsort */
#include <set>

using namespace std;

//#define SIZE 100

// upper is the largest number up to which we find primes. The number of primes smaller than upper should be less than size of array primes[]
int EratosthenesSieve (int upper, int primes[])
{
	/* the function takes the upper limit to which we test the numbers in the arguments, as the array in which we store the numbers,
	 but it returns the exact number of primes */
	int size=0;
	//int i;
	int sieve[18000]; // enough for 2000 primes....
	memset(sieve,0,sizeof sieve);
	int tmp;
	// ignore 2 as prime i.e. instead of starting i from 2, start from 3 and instead of i++, do i+=2
	for(int i(3); i<=upper; i+=2)
	{
		if(!sieve[i])
		{
			primes[size++] = i;
			tmp = i+i;
			while(tmp<=upper)
			{
				sieve[tmp] = 1;
				tmp+=i;
			}
		}
	}
	return size;
}

// The starting and ending indexes of primes used in current test case
int start_idx, end_idx;
set<long> s;

// Following function finds two prime factors that are multipled to get the corresponding original text letter
// 217 shoudl result in CJ (C=7 and J=31)
// last p is the common multiplier that has to be used next i.e. J in the above example to be used next
vector<char> compute_actual_facts(long cipher, vector<int> primes_used) {
	
	// Now we only iterate through the 26 primes actually used from the set
	
	int left = 0;
	int right = (int)primes_used.size();
	vector<char> r;
	
	//cout << "right is: " << right << endl;
	while(left < right) {
		
		long pl = primes_used[left];
		long pr = primes_used[right];
		
		if(pl*pr < cipher) {
			left++;
		}
		
		else if (pl*pr > cipher) {
			right--;
		}
		
		else { // when equal
			char f, s;
			f = 'A' + left;
			s = 'A' + right;
			
			if(isupper(f) && isupper(s)){ // only if both are valid capital charters
				r.push_back(f);
				r.push_back(s);
				
				cout << "First letter: " << f << "\t and Second letter: " << s << endl;
				break;
			}
		}
	}
	return	r;
}

// pass 7 return C's index (yet to update documentation once start and end index of primes are not known)
// Problem is that there are many more primes computed and all we know is that the chosen ones
// are used in sorted order. The problem is to find the starting and ending prime being
// used for each test case
int map_p_to_a(long p, int prime[], int max_prime) {
	
	int c;
	//int cnt=0;
	
	// looping from start to max_prime to print index
	for(c=0; c<max_prime; ++c) {
		if(prime[c] == p)
			break;
	}
	
	// Below is earlier original order of end to start
	/*for(c=max_prime-1; c>=0; --c, cnt++) {
		if(prime[c] == p) {
			break;
		}
	}*/
	
	//cout << "Index:" << c << "\tPrime is:" << prime[c] << endl;
	return c;
}

// Following function finds two prime factors that are multipled to get the corresponding original text letter
// 217 shoudl result in CJ (C=7 and J=31)
// last p is the common multiplier that has to be used next i.e. J in the above example to be used next

// Update: Because we don't know which primes are used, this function now only finds which 26 primes
// to use and updates start and end indexes from the primes array. Actually finding the facts is
// moved to another function compute_actual_facts()
vector<char> find_primes_used(long cipher, int primes[], int max_prime) {
	
	vector<char> r;
	// pick two extreme end primes first and last
	// if their product is equal to cipher return them, if less increment first, if greater decrement last
	
	// take the right most 26 primes
	int right = max_prime-1;
	int left = 0;
	
	while(left < right) {
		
		long pl =primes[left];
		long pr = primes[right];
		if(pl*pr < cipher)
			left++;
		else if(pl*pr > cipher)
			right--;
		else { // product of two primes is equal here
			
			cout << "Encrypted text: " << cipher << "   Primes used are: " << pl << " and " << pr << endl;
			
			int f_id = map_p_to_a(pl, primes, max_prime);
			int s_id = map_p_to_a(pr, primes, max_prime);
			
			if(f_id < start_idx)
				start_idx = f_id;
			
			if(s_id > end_idx)
				end_idx = s_id;
			
			s.insert(pl);
			s.insert(pr);
			
			break;
		}
	}

	return r;
}

// problem from google code jam 2019
void Cryptopangrams() {
	// Test code for finding and printing first s primes
	/*int arr[SIZE];
	 int largest_prime = 100;
	 int s = EratosthenesSieve(largest_prime, arr);
	 cout << "Numer of primes s less than " << largest_prime <<  " is: " << s << endl;
	 
	 for(int c=0; c<s; ++c) {
	 cout << arr[c] << "\t";
	 }
	 cout << endl;*/
	

	 int num_tests = 1;
	 //cin >> num_tests;
	 
	 
	for(int idx=1; idx<=num_tests; ++idx) {
		int n, l;
		vector<int>cipher_text;
		
		//cin >> n >> l;
		//n = 103;
		//l=31;
		n = 10000;
		l = 25;
		// find at least 26 primes less than n
		int primes[10000];
		//int cnt_primes =
		int prime_cnt = EratosthenesSieve(n, primes);
		//cout << "Num primes: " << prime_cnt << endl;
		
		start_idx = 1000000;
		end_idx = -1;
		
		// 103 25
		/*int val_arr[] = {217, 1891, 4819, 2291, 2987, 3811, 1739, 2491, 4717, 445, 65, 1079, 8383, 5353, 901, 187, 649, 1003, 697, 3239, 7663, 291, 123, 779, 1007, 3551, 1943, 2117, 1679, 989, 3053};*/
		
		
		//10000 25
		int val_arr[] = {3292937, 175597, 18779, 50429, 375469, 1651121, 2102, 3722, 2376497, 611683, 489059, 2328901, 3150061, 829981, 421301, 76409, 38477, 291931, 730241, 959821, 1664197, 3057407, 4267589, 4729181, 5335543};
		
		
		string result = "";
		vector<char> r;
		int list_i;
		//char last_prime = ' ';
		for(list_i=0; list_i<l; ++list_i) {
			int val;
			//cin >> val;
			val = val_arr[list_i];
			cipher_text.push_back(val);
			
			r = find_primes_used(val, primes, prime_cnt);
			
			//if(r.size() < 2){
			//	cout << "Failed to find 2 primes with the product" << endl;
			//exit(1);
			//}
			
			// Some times the common prime between the two is not the first one.
			// E.g. QUIZ (Find facts would return IU in order, but the common prime multiplier is I, not U)
			// Following if else fixes that.
			/*if(last_prime != ' ') {
			 
			 if(r[0] != last_prime) {
			 result += r[1];
			 last_prime = r[0];
			 }
			 
			 else if(r[0] == last_prime) {
			 result += r[0];
			 last_prime = r[1];
			 }
			 }
			 
			 else {
			 result += r[0];
			 last_prime = r[1];
			 }*/
		}
			
		//result += r[1];

		vector<int> primes_used(s.begin(), s.end());
		
		// loop again from start to end of the cipher text and decode, now that we know which primes to use
		/*for(list_i=0; list_i<l; ++list_i) {
			compute_actual_facts(val_arr[list_i], primes_used);
			
		}*/

		
		cout << "Start idx:" << start_idx << "\tEnd idx:" << end_idx << endl;
		
		int i_p=0;
		//int p=1531; // looks a random test limit, not needed really
		for(auto it = 0; it < primes_used.size(); it++,i_p++){
			
			cout << primes_used[it] << " ";
		}
		//cout << "\ncount of indexes: " << i_p << endl;
		//cout << primes_used.size() << endl;
		//cout << s.count(89) << endl;
		
		/*cout << "Comparing with primes from original array" << endl;
		
		for(int idx=start_idx; idx<=end_idx; ++idx) {
			cout << primes[idx] << " ";
		}
		*/
		cout << endl;
		
		//cout << "Case #" << num_tests << ": " << endl; // << result << endl;
		//cout << "array size:" << cipher_text.size() << "and Count of primes is: " << cnt_primes << endl;
		//CJQUIZKNOWBEVYOFDPFLUXALGORITHMS
	}
	
}

int main() {
	
	Cryptopangrams();
	
	return 0;
}

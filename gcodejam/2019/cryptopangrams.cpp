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
#include <iomanip> // for setw
using namespace std;

// Stuff kept global temporarily (really bad idea but was just fast during contest)
// The starting and ending indexes of primes used in current test case
int start_idx, end_idx;
set<long> s; // to avoid duplicated primes as well as maintain them in oder
vector<long> primes_orig; // primes in original order in which they appear in the encrypted string
vector<long> sorted_primes; // set converted to array for convenience

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
	
	// UPDATE: BIG MISTAKE was ignoring two, found large values which could only be factored using 2
	primes[0] = 2;
	size++;
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

int index_in_prime_set(long prime) {
	
	int idx=0;
	
	for(auto it=s.begin(); it!=s.end(); ++it, ++idx) {
		if(*it == prime) {
			cout << " Index is: " << idx;
			return idx;
		}
	}
	
	return -1;
}

// Following function finds two prime factors that are multipled to get the corresponding original text letter
// 217 shoudl result in CJ (C=7 and J=31)
// last p is the common multiplier that has to be used next i.e. J in the above example to be used next
vector<char> compute_actual_facts(long cipher) {
	
	// Now we only iterate through the 26 primes actually used from the set
	
	long left = 0;
	long right = sorted_primes.size()-1;
	
	vector<char> r;
	
	//cout << "right is: " << right << endl;
	while(left < right) {
		
		long pl = sorted_primes[left];
		long pr = sorted_primes[right];
		
		if(pl*pr < cipher) {
			left++;
		}
		
		else if (pl*pr > cipher) {
			right--;
		}
		
		else { // when equal
			char f, s;
			f = 'A' + index_in_prime_set(pl); //+ 1;
			s = 'A' + index_in_prime_set(pr); //+ 1;
			
			if(isupper(f) && isupper(s)){ // only if both are valid capital charters
				r.push_back(f);
				r.push_back(s);
				
				cout << " First: " << f << "\t Second: " << s << endl;
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
	
	return c;
}

// Because we don't know which primes are used, this function only finds which 26 primes
// to use and updates start and end indexes from the primes array. Actually finding the facts is
// moved to another function compute_actual_facts()
 void find_primes_used(long cipher, int primes[], int max_prime) {
	
	// pick two extreme end primes first and last
	// if their product is equal to cipher return them, if less increment first, if greater decrement last
	
	// take the right most 26 primes
	int right = max_prime-1;
	int left = 0;
	
	while(left <= right) {
		
		long pl =primes[left];
		long pr = primes[right];
		if(pl*pr < cipher)
			left++;
		else if(pl*pr > cipher)
			right--;
		else { // product of two primes is equal here

			int f_id = map_p_to_a(pl, primes, max_prime);
			int s_id = map_p_to_a(pr, primes, max_prime);

			cout << "Enc val" << setw(8) << cipher << " Primes are: " << setw(4) << pl << "(idx:"<< setw(4) << f_id
			<< ") and " << setw(4) << pr << "(idx:" << setw(4) << s_id << ")" <<  endl;

			if(f_id < start_idx)
				start_idx = f_id;
			
			if(s_id > end_idx)
				end_idx = s_id;
			
/*			long last_pm = primes_orig.size()-1;
			
			if(last_pm > 0) {
				if(primes_orig[last_pm] != pl && primes_orig[last_pm-1] != pl)*/
					primes_orig.push_back(pl);
			//	if(primes_orig[last_pm] != pr && primes_orig[last_pm-1] != pr)
					primes_orig.push_back(pr);
			//}
			s.insert(pl);
			s.insert(pr);
			
			break;
		}
	}
	 
	if(left>right)
		cout << "Failed to find prime factors for cipher: " << cipher << endl;
}

void Cryptopangrams() {

	 int num_tests = 1;
	 //cin >> num_tests;

	for(int idx=1; idx<=num_tests; ++idx) {
		int n, l;
		//vector<int>cipher_text;
		
		//cin >> n >> l;
		//n = 103;
		//l=31;
		n = 10000;
		l = 25;
		// find at least 26 primes less than n
		int primes[10000];
		int prime_cnt = EratosthenesSieve(n, primes);
		
		start_idx = 1000000;
		end_idx = -1;
		
		// 103 25
		/*int val_arr[] = {217, 1891, 4819, 2291, 2987, 3811, 1739, 2491, 4717, 445, 65, 1079, 8383, 5353, 901, 187, 649, 1003, 697, 3239, 7663, 291, 123, 779, 1007, 3551, 1943, 2117, 1679, 989, 3053};*/

		//10000 25
		int val_arr[] = {3292937, 175597, 18779, 50429, 375469, 1651121, 2102, 3722, 2376497, 611683, 489059, 2328901, 3150061, 829981, 421301, 76409, 38477, 291931, 730241, 959821, 1664197, 3057407, 4267589, 4729181, 5335543};
		
		string result = "";
		vector<char> r;
		int list_i;
		for(list_i=0; list_i<l; ++list_i) {
			
			int val;
			//cin >> val;
			val = val_arr[list_i];
			
			find_primes_used(val, primes, prime_cnt);
		}
		
		sorted_primes.assign(s.begin(), s.end());

		// loop again from start to end of the cipher text and decode, now that we know which primes to use
		for(list_i=0; list_i<l; ++list_i) {
			compute_actual_facts(val_arr[list_i]);
		}

		
		/*cout << "Start idx:" << start_idx << "\tEnd idx:" << end_idx << endl;
		
		int i_p=0;
		for(auto it = 0; it < primes_orig.size(); it++,i_p++){
			
			cout << primes_orig[it] << " ";
		}
		
		cout << "\nComparing with primes from set" << endl;
		
		for(auto it=sorted_primes.begin(); it!=sorted_primes.end(); ++it) {
			cout << *it << " ";
		}*/
		
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

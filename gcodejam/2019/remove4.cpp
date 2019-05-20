
/* Problem
Someone just won the Code Jam lottery, and we owe them N jamcoins! However, when we tried to print out an oversized check, we encountered a problem. The value of N, which is an integer, includes at least one digit that is a 4... and the 4 key on the keyboard of our oversized check printer is broken.

Fortunately, we have a workaround: we will send our winner two checks for positive integer amounts A and B, such that neither A nor B contains any digit that is a 4, and A + B = N. Please help us find any pair of values A and B that satisfy these conditions.

Input
The first line of the input gives the number of test cases, T. T test cases follow; each consists of one line with an integer N.

Output
For each test case, output one line containing Case #x: A B, where x is the test case number (starting from 1), and A and B are positive integers as described above.

It is guaranteed that at least one solution exists. If there are multiple solutions, you may output any one of them. (See "What if a test case has multiple correct solutions?" in the Competing section of the FAQ. This information about multiple solutions will not be explicitly stated in the remainder of the 2019 contest.)

Limits
1 ≤ T ≤ 100.
Time limit: 10 seconds per test set.
Memory limit: 1GB.
At least one of the digits of N is a 4.

Test set 1 (Visible)
1 < N < 105.

Test set 2 (Visible)
1 < N < 109.

Solving the first two test sets for this problem should get you a long way toward advancing. The third test set is worth only 1 extra point, for extra fun and bragging rights!

Test set 3 (Hidden)
1 < N < 10100.

Sample

Input 
 	
Output 
 
3
4
940
4444

  
Case #1: 2 2
Case #2: 852 88
Case #3: 667 3777

  
In Sample Case #1, notice that A and B can be the same. The only other possible answers are 1 3 and 3 1.

*/


#include <cstdio>
#include <iostream>

//using namespace std;

/* LOGIC TO REMOVE 4 digit by digit - ONLY fails when second number has a digit 4
 
 int num=1;
 
 int tcase;
 
 
 //944 ... 943 and 1
 //        933    10+1
 
 
 // 9444   9443 1  ... 9433 and 10+1
 // 4444
 for(tcase=1; tcase<=num; ++tcase) {
 
 long int n = 441;
 //cin >> n;
 
 long a=0, b=0;
 int base = 1;
 long orig = n;
 long lastd_a;
 int lastb = 1;
 
 while(n>0) {
 int digit = n%10;
 
 if(digit == 4){
 lastd_a = a%10;
 a=(n-1)*base;
 a+=lastd_a*(lastb++);
 b = orig-a;
 }
 
 n/=10;
 base*=10;
 }
 
 cout << "Case #" << tcase << ": " << a << " " << b << endl;
 }
 
 */


bool is_4free(long n) {
	
	while(n > 0) {
		int d = n%10;
		if (d==4)
			return false;
		n = n/10;
	}
	return true;
}

vector<long> find2_4free(long n) {
	
	long a=0, b=0;
	int base = 1;
	long orig = n;
	long lastd_a;
	int lastb = 1;
	
	while(n>0) {
		int digit = n%10;
		
		if(digit == 4){
			lastd_a = a%10;
			a=(n-1)*base;
			a+=lastd_a*(lastb++);
			b = orig-a;
		}
		
		n/=10;
		base*=10;
	}
	
	vector<long> res;
	res.push_back(a);
	res.push_back(b);
	
	return res;
}

int main(){
	int num=1;

	int tcase;

	
	//944 ... 943 and 1
	//        933    10+1
	
	
	// 9444   9443 1  ... 9433 and 10+1
	// 4444
	for(tcase=1; tcase<=num; ++tcase) {
		
		long int n = 4444444444;
		//cin >> n;
		
		vector<long> r = find2_4free(n);
		long a = r[0];
		long b = r[1];
		
		while(!is_4free(b)) { // while b is not 4 free
			r = find2_4free(b);
			
			// r[0] is surely 4 free
			b = r[1]+a;
			a = r[0];
		}
		
		cout << "Case #" << tcase << ": " << a << " " << b << endl;
	}
	
	return 0;
}


// THE FIRST SLOW solution that worked for 10^5
 
 
 bool is_4freeOrig(long n) {
 
 while(n > 0) {
 int d = n%10;
 if (d==4)
 return false;
 n = n/10;
 }
 return true;
 }
 
 /* int main(){
 int num;
 cin >> num;
 
 int tcase;
 for(tcase=1; tcase<=num; ++tcase) {
 
 long int n;
 cin >> n;
 
 long a=n-1, b=1;
 //long orig =n;
 
 while(1) {
 if(is_4free(a) && is_4free(b)){
 cout << "Case #" << tcase << ": " << a << " " << b << endl;
 break;
 }
 
 else {
 a--;
 b++;
 }
 }
 }
 
 return 0;
 }*/

 

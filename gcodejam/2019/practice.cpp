// Practice interactive question from GCJ 2019

int main() {
	
	int num_tests;
	
	//cout << "STARTING" << endl;
	
	cin >> num_tests;
	//cout  << "num_tests: " << num_tests << endl;
	
	for(int idx=0; idx<num_tests; ++idx) {
		int A, B, N;
		cin >> A >> B;
		//cout << "A:" << A << " B:" << B << endl;
		cin >> N;
		//cout << "N:" << N << endl;

		for(int i=0; i<N && A<B; ++i) {
			int m = (A+B)/2;
			
			cout << m << endl;
			
			string resp;
			//cout << "Enter resp:" << endl;
			cin >> resp;
			//cout << "resp is: " << resp << endl;
			
			if(resp == "TOO_SMALL")
				A = m+1;
			else if(resp == "TOO_BIG")
				B = m;
			else if(resp == "WRONG_ANSWER" || resp=="CORRECT")
				break;

		}
	}
}

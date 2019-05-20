// This was a question from amzon online test related to sorting, sample test case is in main

void print(vector<string> p) {
	
	for(int i=0; i<p.size(); ++i)
		cout << p[i] << endl;
	cout << endl;
	
}

bool isDigit(string a){
	
	int idx=0;
	
	while(a[idx] != ' ')
		idx++;
	
	idx++;
	
	// found first space so next char should be digit for new
	if(a[idx] >= '0' && a[idx] <= '9')
		return true;
	else return false;
}

// I just didn't touch c/c++ strings in a while and ran into api compiler issues
// i am tokenizing each string with C token api and then comparing each one by one
bool isLess(string a, string b) {
	
	
	//const char * c_a = a.c_str();
	//const char * c_b = b.c_str();
	
	char c_a[a.size()+1];
	memcpy(c_a, a.c_str(), a.size() + 1 );
	c_a[a.size()] = '\0';
	char *p_a = c_a;
	
	char c_b[b.size()+1];
	memcpy(c_b, b.c_str(), b.size() + 1 );
	c_b[b.size()] = '\0';
	char *p_b = c_b;
	
	char * a_tok = strtok(p_a, " ,\0");
	char * b_tok = strtok(p_b,", \0");
	
	int res;
	while(a_tok || b_tok) {
		res = strcmp(a_tok,b_tok);
		if(res < 1)
			return true;
		else if(res > 1)
			return false;
		
		else { // keep going
			a_tok = strtok(NULL, " ,\0");
			b_tok = strtok(NULL, " ,\0");
		}
		
	}
	
	return true;
}

vector<string> orderedJunctionBoxes(int numberOfBoxes, vector<string> boxList)
{
	// WRITE YOUR CODE HERE
	
	// consider using built in sort with comparison function like qsort()
	// but first thought is to do a pass and move all new gens to the end after
	// counting them in the original order then sort the rest. Lets see if this
	// works. Look at qsort sdk online to ensure it would work after verifying if
	// this would work. No it won't work because size in bytes of each element is
	// a param which doesn't work here (string of variable length)
	
	// So lets sort it manually then implementing a function
	
	
	// count and move new ones to END in res;
	vector<string> res(numberOfBoxes); // reason for choosing new is that swap
	// was complicated i.e. what if i move a new from end to start
	
	int cnt_new=0;
	for(int i=0; i<numberOfBoxes; ++i) {
		if(isDigit(boxList[i]))  // new boxes use numerics
			cnt_new++;
	}
	
	//cout << "Cout new: " << cnt_new << endl;
	
	// now move to end in original order
	int st_idx = numberOfBoxes-cnt_new;  // 6-2=4 start of new elements start_n_idx
	
	for(int j=0, s=st_idx; j<numberOfBoxes; ++j) {
		
		if(isDigit(boxList[j])) {
			res[s] = boxList[j];
			//cout << "COPIED " <<  res[s] << endl;
			s++;
		}
	}
	
	
	// Verified, now sort the initial part, selection sort like
	
	/*int res_id=0;
	
	for(int out=0; out<st_idx; ++out) { // need to sort only until st_idx
		
		int idx_min = -1; // has to be first !isDigit() index
		
		for(int in=out+1; in<numberOfBoxes; ++in) { // find smallest in remaining
			
			if(boxList[in]=="" || isDigit(boxList[in]))
				continue;
			
			
			else if(idx_min == -1 || isLess(boxList[in], boxList[idx_min])) {
				idx_min = in;
			}
			
		}
		
		res[res_id++] = boxList[idx_min];
		
		// need to invalidate original in boxList
		boxList[idx_min] = ""; // some marker
	}*/
	
	//print(res);
	
	
	return res;
}

void swap(string &fir, string &sec) {
	string temp=fir;
	fir = sec;
	sec = temp;
}

int comp(const void * a, const void * b)
{
	//return ( *(int*)a - *(int*)b );
	
	string * f = *(string * const *)a;
	string * s = *(string * const *)b;
	
	//char * f = (char *)a;
	//cout << "Printing f here if its only type issue: " << f[0] << f[1] << f[2] << endl;
	cout << *f << endl;
	//out << *s << endl;

	char c_a[7], b_a[7];
	strcpy(c_a, f->c_str());
	strcpy(b_a, s->c_str());

	int res = strcmp(c_a, b_a);
	//cout << "strcmp " << f->c_str() << " and " << s->c_str() << "\t RES: "  << res <<  endl;
	
	return res;
}

vector<string> orderedJunctionBoxes2(int numberOfBoxes, vector<string> boxList)
{
	// 1) try qsort or stl sort while handling every thing in the comp function if possible
	// 2) Try in place manual sort by first copying new entries towards the end
	
	int new_idx=numberOfBoxes-1; // last index
	
	for(int i=numberOfBoxes-1; i>=0; --i) {
		
		if(isDigit(boxList[i])) { // if new
			// swap with the end node
			swap (boxList[i],boxList[new_idx--]);
		}
	}
	
	// sort the remaining old boxes from 0-new_indx inclusive
	auto it = boxList.end();
	for(int i=(int)boxList.size(); i!=new_idx+1; --i)
		it--;
	
	sort(boxList.begin(), it);
	return boxList;
}


int main()
{
	//cout<<"TESTING IN main";
	
	vector<string> in = {"def 343", "qhr 923", "4s3 xyz", "4s3 defgh", "4s3 abc"};
	//vector<string> in = {"4s3 xyz", "4s3 abc"};

	vector<string> res = orderedJunctionBoxes2((int)in.size(), in);
	
	print(res);
	
	return 0;
}

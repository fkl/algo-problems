
// a usaco problem requiring finding some money exchange among friends and used map etc.

int main() {
	
/*	ofstream fout ("gift1.out");
	ifstream fin("gift1.in");
	unordered_map<string, int> mp;
	vector<string> vmap;
	
	if(fin.fail())
		cout << "failed to open" << endl;
	int np = 0;
	char names[15];
	int money, num_friends;
	
	fin >> np; // number of friends total
	for (int i=0; i<np; ++i) {
		fin >> names;
		vmap.push_back(names);
		mp[names] = 0;
	}
	
	for (int j=0; j<np; ++j) {
		fin >> names; // name of person whose money and friends list
		//cout << names << endl;
		fin >> money >> num_friends;
		//cout << money << " "  << num_friends << endl;
		
		// divide evenly
		int eachShare = 0;
		if(num_friends > 0) {
			mp[names] -= money;
			eachShare = money / num_friends;
		
			// add to giver if any remains
			int rem = money % num_friends;
		
			if(rem > 0)
				mp[names] += rem;
		
			for(int i=0; i<num_friends; ++i) {
				fin >> names; // name of each friend he shares with
				//cout << names << "\t";
				mp[names] += eachShare;
			}
		}
		//cout << endl;
	}
	
	//for(map<string, int>::const_iterator it = mp.begin(); it != mp.end(); ++it) {
	//	cout <<  it->first << " " << it->second << endl;
	//}

	// Traversing an unordered or ordered map
	//for (auto x : mp)
	//	cout << x.first << " " << x.second << endl;

	// Use vector for insert order
	//for (int c=0; c<vmap.size();  ++c)
	for (auto name: vmap)
		cout << name << " " << mp[name] << endl; */
	
/*	for (int j=0; j<np; ++j) {
		
		char temp[15];
		fin.getline(temp, sizeof(temp)-1);
		
		if(temp[0] >= 'a' && temp[0] <= 'z')  // its a name
			cout << temp << endl;
		else {  // its a pair of values
			
			char *first = strtok(temp, " ,");
			money = atoi(first);
			char *sec = strtok(NULL, " ,");
			num_friends = atoi(sec);
			cout << money << " " << num_friends << endl;
		}
	}*/

	return 0;
}

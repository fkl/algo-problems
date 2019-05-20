/* LANG can be C++11 or C++14 for those more recent releases */
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


void visit_ng(vector<vector<int>> & m, vector<vector<int>> &v, int x, int y, int &c)  {
	
/*	cout << "v size: " << v.size() << " ";
	cout << "v[0] size: " <<  v[0].size() << endl;
	for (auto c: v) {
		for(auto d: c)
			cout  << "visited d: " << d << "\t";
		cout << endl;
	}*/

	
	if(x<0 || y<0 || x>= m.size() || y>=m[0].size() || m[x][y] == 0 || v[x][y] == 1)
		return;
	
	else {
		
		v[x][y] = 1; // marked visited
		c++;
		visit_ng(m, v, x-1, y, c);
		visit_ng(m, v, x-1, y-1, c);
		visit_ng(m, v, x-1, y+1, c);
		visit_ng(m, v, x, y+1, c);
		visit_ng(m, v, x, y-1, c);
		visit_ng(m, v, x+1, y-1, c);
		visit_ng(m, v, x+1, y, c);
		visit_ng(m, v, x+1, y+1, c);
	}
}

// Complete the connectedCell function below.
int connectedCell(vector<vector<int>> matrix) {
	
	// dfs
	// for each cell, visit all of its eight neighbors recursively where
	// you keep going until you find neighbors with value 1s and are not yet visited
	
	int count=0;
	vector<vector<int>> v(matrix.size(), vector<int> (matrix[0].size(),0));
	
	/*for (auto c : v) {
		for (auto d : c) {
			d = 0;
			cout << "d: " << d << "\t";
		}
		cout << endl;
	}*/
	
	visit_ng(matrix, v, 0, 0, count);
	
	cout << "Count from 0 0 is: " << count << endl;
	
	return count;
}

int main() {
	
vector<vector<int>> m { { 1, 1, 0, 0 },
							{ 0, 1, 1, 0 },
							{ 0, 0, 1, 0},
							{ 1, 0, 0, 0} };

	
	connectedCell(m);
  return 0;
}

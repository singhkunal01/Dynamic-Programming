#include<bits/stdc++.h>
using namespace std;


/*recursion and memoization code -

For Memoization - TC :O(N*N) & SC: O(N*N) + O(N)
For Recursion - TC : >O(2^N) & SC: >O(N) */

int waysToCutRod(int part, vector<int> &price, vector<vector<int>> &memo, int currLength) {
	if (part == 0) {
		return currLength * price[0];
	}
	if (memo[part][currLength] != -1) return memo[part][currLength];
	int notCut = waysToCutRod(part - 1, price, memo, currLength);
	int cut = INT_MIN;
	int currRodLength = part + 1;
	if (currRodLength <= currLength) cut = price[part] + waysToCutRod(part, price, memo, currLength - currRodLength);
	return memo[part][currLength] = max(cut, notCut);
}


/*tabulation approach */
int waysToCutRodTabul(vector<int> &price, int n) {
	vector<vector<int>> memo(n, vector<int> (n + 1, -1));
//for the base case
	for (int i = 0; i <= n; i++)memo[0][i] = i * price[0];
	for (int part = 1; part < n; part++) {
		for (int currLength = 0; currLength <= n; currLength++) {
			int notCut = memo[part - 1][currLength];
			int cut = INT_MIN;
			int currRodLength = part + 1;
			if (currRodLength <= currLength)cut = price[part] + memo[part][currLength - currRodLength];
			memo[part][currLength] = max(cut, notCut);
		}
	}
	return memo[n - 1][n];
}


/*space optimisation approach */
int waysToCutRodSpaceOpt(vector<int> &price, int n) {
	vector<int> prev(n + 1), curr(n + 1);
//for the base case
	for (int i = 0; i <= n; i++)prev[i] = i * price[0];
	for (int part = 1; part < n; part++) {
		for (int currLength = 0; currLength <= n; currLength++) {
			int notCut = prev[currLength];
			int cut = INT_MIN;
			int currRodLength = part + 1;
			if (currRodLength <= currLength)cut = price[part] + curr[currLength - currRodLength];
			curr[currLength] = max(cut, notCut);
		}
		prev = curr;
	}
	return prev[n];
}

int cutRod(vector<int> &price, int n) {

	//for memoization -
	// vector<vector<int>> memo(n, vector<int> (n + 1, -1));
	// int res = waysToCutRod(n - 1, price, memo, n);

	//for tabulation
	// int res = waysToCutRodTabul(price, n);

	//for space optimisation
	int res = waysToCutRodSpaceOpt(price, n);
	return res;
}


int main() {

	int totalLength ;
	cin >> totalLength;
	vector<int> price(totalLength);
	for (int &i : price) cin >> i;
	cout << "Total Profit: " << cutRod(price, totalLength);
	return 0;

}
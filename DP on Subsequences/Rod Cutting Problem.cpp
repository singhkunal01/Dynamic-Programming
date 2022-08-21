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

int cutRod(vector<int> &price, int n) {
	vector<vector<int>> memo(n, vector<int> (n + 1, -1));
	int res = waysToCutRod(n - 1, price, memo, n);
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
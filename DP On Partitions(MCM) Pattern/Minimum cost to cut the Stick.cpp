#include<bits/stdc++.h>
using namespace std;

//memoisation code

long giveCost(int i, int j, vector<int>&cuts, vector<vector<int>> &dp) {
	if (i > j) return 0;
	if (dp[i][j] != -1) return dp[i][j];
	long minCost = INT_MAX;
	for (int k = i; k <= j; k++) {
		long cost = cuts[j + 1] - cuts[i - 1] + giveCost(i, k - 1, cuts, dp) + giveCost(k + 1, j, cuts, dp);
		minCost = min(minCost, cost);
	}
	return dp[i][j] = minCost;
}

//main code
int minCost(int n, vector<int>& cuts) {
	int m = cuts.size();
	cuts.insert(cuts.begin(), 0);
	cuts.push_back(n);
	sort(begin(cuts), end(cuts));
	vector<vector<int>> dp(m + 1, vector<int> (m + 1, -1));
	return giveCost(1, m, cuts, dp);
}


int main() {
	int n ; cin >> n;
	int len; cin >> len; //total length of stick
	vector<int> cuts(n);
	for (int &i : cuts)cin >> i;
	cout << minCost(len, cuts);
	return 0;

}
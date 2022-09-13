#include<bits/stdc++.h>
using namespace std;

//memoisation code
long giveCost(int i, int j, vector<int>&cuts, vector<vector<int>> &dp) {
	if (i > j) return 0;
	if (dp[i][j] != -1) return dp[i][j];
	long miniCost = INT_MAX;
	for (int k = i; k <= j; k++) {
		long cost = cuts[j + 1] - cuts[i - 1] + giveCost(i, k - 1, cuts, dp) + giveCost(k + 1, j, cuts, dp);
		miniCost = min(miniCost, cost);
	}
	return dp[i][j] = miniCost;
}

//tabulation code
long giveCostTabul(int m, vector<int> &cuts) {
	vector<vector<int>> dp(m + 2, vector<int> (m + 2, 0));
	for (int i = m; i > 0; i--) {
		for (int j = 1; j <= m; j++) {
			if (i > j) continue;
			long miniCost = (int)INT_MAX;
			for (int ind = i; ind <= j; ind++) {
				long cost = cuts[j + 1] - cuts[i - 1] + dp[i][ind - 1] + dp[ind + 1][j];
				miniCost = min(miniCost, cost);
			}
			dp[i][j] = miniCost;
		}
	}
	return dp[1][m];
}


//main code
int minCost(int n, vector<int>& cuts) {
	int m = cuts.size();
	cuts.insert(cuts.begin(), 0);//insert the 0 at starting
	cuts.push_back(n);
	sort(begin(cuts), end(cuts));

	// for memoisation
	// vector<vector<int>> dp(m + 1, vector<int> (m + 1, -1));
	// int res =  giveCost(1, m, cuts, dp);


	//for tabulation
	int res = giveCostTabul(m, cuts);
	return res;
}


int main() {
	int n ; cin >> n;
	int len; cin >> len; //total length of stick
	vector<int> cuts(n);
	for (int &i : cuts)cin >> i;
	cout << minCost(len, cuts);
	return 0;

}
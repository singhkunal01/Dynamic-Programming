#include<bits/stdc++.h>
using namespace std;

bool isPalindrome(string &str) {
	int n = str.size(), i = 0;
	while (i <= n / 2) {
		if (str[i] != str[n - i - 1])
			return false;
		i++;
	}
	return true;
}

// memoisation code
int doPartitions(int ind, string &s, vector<int>&dp) {
//base case
	if (ind == s.size()) return 0;
	if (dp[ind] != -1) return dp[ind];
	int minCost = INT_MAX;
	string substr;
	for (int j = ind; j < s.size(); j++) {
		substr += s[j];
		if (isPalindrome(substr)) {
			int cost = 1 + doPartitions(j + 1, s, dp);
			minCost = min(cost, minCost);
		}
	}
	return dp[ind] = minCost;;

}

// tabulation code
int doPartitionsTabul(string &s) {
	int n = s.size();
	vector<int> dp(n + 1 , 0);//why n+1 because the base case in memo is i==n so for that we have to add dp[n]=0 so take +1 size
	for (int ind = n - 1; ind >= 0; ind--) {
		int minCost = INT_MAX;
		string substr;
		for (int j = ind; j < s.size(); j++) {
			substr += s[j];
			if (isPalindrome(substr)) {
				int cost = 1 + dp[j + 1];
				minCost = min(cost, minCost);
			}
			dp[ind] = minCost;
		}
	}
	return dp[0] - 1;
}


//main function
int minCut(string s) {
	int n = s.size();
	/*for memoisation code */
	vector<int> dp(n, -1);
	// int res = doPartitions(0, s, dp) - 1;//as we are also adding the last partition which is at the end of string so for removing that do -1.
	/*for tabulation*/
	int res = doPartitionsTabul(s);
	return res;
}



int main() {

	string s;
	cin >> s;
	cout << minCut(s);
	return 0;

}


class Solution {
	int solve(int i, int j , vector<vector<int>> &grid, vector<vector<int>> &dp) {
		if (i == 0 and j == 0) return grid[0][0];
		if (i < 0 or j < 0) return -1e9;
		if (dp[i][j] != -1) return dp[i][j];
		int up = grid[i][j] + solve(i - 1, j, grid, dp) ;
		int left = grid[i][j] + solve(i , j - 1, grid, dp);
		return dp[i][j] = max(up, left);
	}
	int collectMaximumCoins(vector<vector<int>>& mat) {
		int n = mat.size(), m = mat[0].size();
		vector<vector<int>> dp(n, vector<int> (m, -1));
		return solve(n - 1, m - 1, mat, dp);
	}
};




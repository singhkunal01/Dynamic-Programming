#include<bits/stdc++.h>
using namespace std;

#define INF 1e9;//for adding the at max value in our answer when we reach to out of boundaries so that we cannot take that sum path


/*Memoisation approach - TC - O(m*n) and SC = O(path length) */

int findMinumumSumUsingMemoisation(int i, int j , vector<vector<int>> &grid, vector<vector<int>> &dp) {
	if (i == 0 and j == 0) return grid[0][0];
	if (i < 0 or j < 0) return INF;
	//overlapping case
	if (dp[i][j] != -1) return dp[i][j];
	int up = grid[i][j] + findMinumumSumUsingMemoisation(i - 1, j, grid, dp) ;
	int left = grid[i][j] + findMinumumSumUsingMemoisation(i , j - 1, grid, dp);
	return dp[i][j] = min(up, left);
}


/*Tabulation approach TC = O(M*N) and SC = O(M*N)*/
int findMinumumSumUsingTabulation(vector<vector<int>> &grid, vector<vector<int>> &dp) {
	int n = grid.size(), m = grid[0].size();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			//base case
			if (i == 0 and j == 0) dp[i][j] = grid[i][j];
			else {
				int up = grid[i][j];
				if (i > 0)up += dp[i - 1][j];
				else up += 1e9;//remember these key points as memoisation these are the base case where if we
				// go out of bound then for ignoring that sum upto that point we add the larger value in the upward
				int left = grid[i][j];
				if (j > 0)left += dp[i][ j - 1];
				else left += 1e9;//remember these key points as memoisation these are the base case where if we
				// go out of bound then for ignoring that sum upto that point we add the larger value in the leftward
				dp[i][j] = min(up, left);
			}
		}
	}
	return dp[n - 1][m - 1];
}

int minPathSum(vector<vector<int>>& grid) {
	int n = grid.size(), m = grid[0].size();
	vector<vector<int>> dp(n, vector<int> (m, -1));
//for memoisation
	// int ans = findMinumumSumUsingMemoisation(n - 1, m - 1, grid, dp);

//for tabulation
	int ans = findMinumumSumUsingTabulation(grid, dp);
	return ans;

}


int main() {
	int m, n;
	cin >> m >> n;
	vector<vector<int>> grid(m, vector<int> (n));
	for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) cin >> grid[i][j];
	cout << minPathSum(grid) << endl;
	return 0;

}
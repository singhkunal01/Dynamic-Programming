/*======= GRID UNIQUE PATHS - II ============================*/
/* In leetcode obstacles are treated as 1 and on code studio they are treated as -1 so  by that  take the values accordingly*/
#include<bits/stdc++.h>
using namespace std;


/*Recursive approach TC - 2^(m*n) and SC = O(path length) */
int givePathsRecursive2(int m , int n, vector<vector<int>> &grid) {
	//check for the obstacles
	if (m >= 0 and n >= 0 and grid[m][n] == -1) return 0;
	if (m == 0 and n == 0) return 1;//reached the destination
	if (m < 0 or n < 0) return 0;//out of bounds
	int left = givePathsRecursive2(m, n - 1, grid);
	int up = givePathsRecursive2(m - 1, n, grid);
	return  up + left;
}

/*Memoisation approach TC = O(M*N) and SC = O(M*N) + O(path length) */

int givePathsMemo2(int m , int n,  vector<vector<int>> &dp, vector<vector<int>> &grid) {
	//check for the obstacles
	if (m >= 0 and n >= 0 and grid[m][n] == -1) return 0;
	if (m == 0 and n == 0) return 1;//reached the destination
	if (m < 0 or n < 0) return 0;//out of bounds
	if (dp[m][n] != -1) return dp[m][n];
	return dp[m][n] = givePathsMemo2(m - 1, n, dp, grid) + givePathsMemo2(m, n - 1, dp, grid);
}

/*Tabulation approach TC = O(M*N) and SC = O(M*N)*/
int givePathsTabu2(int m, int n, vector<vector<int>> &grid) {
	vector<vector<int>> dp(m, vector<int>(n, 0));
	for (int i = 0 ; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (grid[i][j] == -1) dp[i][j] = 0;
			else if (i == 0 and j == 0)dp[i][j] = 1;
			else {
				int left = 0, up = 0;
				if (j > 0)
					left = dp[i][j - 1];
				if (i > 0)
					up = dp[i - 1][j];
				dp[i][j] = up + left;
			}
		}

	}
	return dp[m - 1][n - 1];
}

/*Space optimisation -  TC - O(M*N) and SC - O(N)*/
int givePathsMostOptimal2(int m, int n, vector<vector<int>> &grid) {
	vector< int>  prev(n);
	for (int i = 0; i < m; i++) {
		vector<int> curr(n);
		for (int j = 0; j < n; j++) {
			if (grid[i][j] == -1) curr[j] = 0;
			else if (i == 0 and j == 0) curr[j] = 1;
			else {
				int up = 0, left = 0;
				if (i > 0) up = prev[j];
				if (j > 0) left = curr[j - 1];
				curr[j] = (up + left);
			}
		}
		prev = curr;
	}
	return prev[n - 1];
}




int uniquePaths(int m, int n, vector<vector<int>> &grid) {
	vector<vector<int>> dp(m, vector<int>(n, -1));
//recursive approach
	// int ans = givePathsRecursive2(m - 1, n - 1, grid);

	//memoise approach
	// int ans = givePathsMemo2(m - 1, n - 1, dp, grid);

	//tabulation approach
	// int ans = givePathsTabu2(m, n, grid);

	int ans = givePathsMostOptimal2(m, n, grid);

	return ans;
}
int main() {

	int m, n;
	cin >> m >> n;
	vector<vector<int>> grid(m, vector<int> (n));
	for (int i = 0; i < m; i++) for (int j = 0; j < n; j++) cin >> grid[i][j];
	cout << uniquePaths(m, n, grid) << endl;
	return 0;

}
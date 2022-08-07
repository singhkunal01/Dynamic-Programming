/*======= GRID UNIQUE PATHS ============================*/

#include<bits/stdc++.h>
using namespace std;


/*Recursive approach TC - 2^(m*n) and SC = O(path length) */
int givePathsRecursive(int m , int n) {
	if (m == 0 and n == 0) return 1;
	if (m < 0 or n < 0) return 0;
	int left = givePathsRecursive(m, n - 1);
	int up = givePathsRecursive(m - 1, n);
	return  up + left;
}

/*Memoisation approach TC = O(M*N) and SC = O(M*N) + O(path length) */

int givePathsMemo(int m , int n,  vector<vector<int>> &dp) {
	if (m == 0 and n == 0) return 1;
	if (m < 0 or n < 0) return 0;
	if (dp[m][n] != -1) return dp[m][n];
	return dp[m][n] = givePathsMemo(m - 1, n, dp) + givePathsMemo(m, n - 1, dp);
}

/*Tabulation approach TC = O(M*N) and SC = O(M*N)*/
int givePathsTabu(int m, int n) {
	vector<vector<int>> dp(m, vector<int>(n, 0));
	for (int i = 0 ; i < m; i++) {
		for (int j = 0; j < n; j++) {
			int left = 0, up = 0;
			if (i == 0 and j == 0)dp[0][0] = 1;
			else {
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


int uniquePaths(int m, int n) {
	// vector<vector<int>> dp(m, vector<int>(n, -1));
//recursive approach
	// int ans = givePathsRecursive(m - 1, n - 1);

	//memoise approach
	// int ans = givePathsMemo(m - 1, n - 1, dp);

	//tabulation approach
	int ans = givePathsTabu(m, n);
	return ans;
}

int main() {
	int m, n;
	cin >> m >> n;
	cout << uniquePaths(m, n) << endl;
	return 0;

}
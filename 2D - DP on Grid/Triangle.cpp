#include<bits/stdc++.h>
using namespace std;

//memoisation approach

int findPathSum(int i, int j, vector<vector<int>> &triangle, int n, vector<vector<int>> &dp) {
	// there is no out of bound when we reach at the last row automatic return that value
	if (i == n - 1) return triangle[i][j];
	if (dp[i][j] != -1) return dp[i][j];//memoise step
	int curr = triangle[i][j] + findPathSum(i + 1, j, triangle, n, dp);
	int next = triangle[i][j] + findPathSum(i + 1, j + 1, triangle, n, dp);
	return dp[i][j] = min(curr, next);
}

//tabulation approach
int findPathSumTabul(vector<vector<int>> &triangle) {
	int n = triangle.size();
	vector<vector<int>> dp(n, vector<int>(n));

	//base case
	for (int j = 0; j < n; j++) dp[n - 1][j] = triangle[n - 1][j];

//rest of the code
	for (int i = n - 2; i >= 0; i--) {
		for (int j = i; j >= 0; j--) {
			int curr = triangle[i][j] + dp[i + 1][j];
			int next = triangle[i][j] + dp[i + 1][j + 1];
			dp[i][j] = min(curr, next);
		}
	}
	return dp[0][0];
}



int minimumTotal(vector<vector<int>>& triangle) {
	int n = triangle.size();
	//for memoisation approach
	// vector<vector<int>> dp(n, vector<int>(n, -1));
	// int res = findPathSum(0, 0, triangle, n, dp);

	//for tabulation approach
	int res = findPathSumTabul(triangle);
	return res;
}

int main() {
	int n;
	cin >> n ;
	vector<vector<int>> triangle(n);
	for (int i = 0 ; i < n; i++) {
		vector<int> v(i + 1);
		for (int j = 0; j < i + 1; j++)
			cin >> v[j];
		triangle[i] = v;
	}
	cout << minimumTotal(triangle);
	return 0;
}
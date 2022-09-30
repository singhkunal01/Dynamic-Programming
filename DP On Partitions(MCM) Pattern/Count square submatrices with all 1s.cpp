#include<bits/stdc++.h>
using namespace std;

int numSubmat(vector<vector<int>>& mat) {
	int n = mat.size(), m = mat[0].size();
	vector<vector<int>> dp(n, vector<int> (m, 0));
	//base case fixed the values for the first row and coloumns
	for (int i = 0; i < n; i++) dp[i][0] = mat[i][0];
	for (int j = 0; j < m; j++) dp[0][j] = mat[0][j];
//now iterate over all remaining rows and columns
	for (int i = 1; i < n; i++) {
		for (int j = 1; j < m; j++) {
			if (mat[i][j] == 0) dp[i][j] = 0;
			else dp[i][j] = max({dp[i][j - 1], dp[i - 1][j - 1], dp[i - 1][j]}) + 1;
		}
	}
//find the total submatrices
	int totalSubmat = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			totalSubmat += dp[i][j];

	return totalSubmat;

}


int main() {
	int n, m; cin >> n >> m;
	vector<vector<int>> grid(n, vector<int> (m));
	cout << numSubmat(grid);
	return 0;

}
#include<bits/stdc++.h>
using namespace std;

/*tabulation code*/
int matrixChainMultiplication(vector<int>&arr) {
	int n = arr.size();
	vector<vector<int>> dp(n, vector<int>(n, 0));
//base case
	for (int i = 0; i < n; i++)dp[i][i] = 0;

	for (int i = n - 1; i > 0; i--) {
		for (int j = i + 1; j < n; j++) {
			/*as the i is always in left of j so if we start j from 1 it recalculates
			some area again so for ignoring it start from i+1 everytime*/
			int minOperations = 1e9;
			for (int k = i; k < j; k++) {
				int totalSteps = (arr[i - 1] * arr[k] * arr[j]) + dp[i][k] + dp[k + 1][j];
				minOperations = min(totalSteps, minOperations);
			}
			dp[i][j] = minOperations;
		}
	}
	return dp[1][n - 1];
}


int main() {
	int n;
	cin >> n;
	vector<int>arr(n);
	for (int &i : arr) cin >> i;
	cout << matrixChainMultiplication(arr);
	return 0;


}
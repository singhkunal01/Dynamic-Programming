#include<bits/stdc++.h>
using namespace std;

/*Recursive code for the MCM - */
int calculateOperations(int i, int j, vector<int> &arr) {
	if (i == j) return 0;
	//iterate to  check over all indices to create a partition from that index
	int minOperations = 1e9;
	for (int k = i; k < j; k++) {
		int totalSteps = (long long)(arr[i - 1] * arr[k] * arr[j])
		                 + calculateOperations(i, k, arr) +
		                 calculateOperations(k + 1, j, arr);
		minOperations = min(minOperations, totalSteps);
	}
	return minOperations;
}

/*memoization code using 2D dp*/
int calculateOperationsMemo(int i, int j, vector<int> &arr, vector<vector<int>> &dp) {
	if (i == j) return 0;
	//iterate to  check over all indices to create a partition from that index
	if (dp[i][j] != -1) return dp[i][j];
	int minOperations = 1e9;
	for (int k = i; k < j; k++) {
		int totalSteps = (long long)(arr[i - 1] * arr[k] * arr[j])
		                 + calculateOperationsMemo(i, k, arr, dp) +
		                 calculateOperationsMemo(k + 1, j, arr, dp);
		minOperations = min(minOperations, totalSteps);
	}
	return dp[i][j] = minOperations;
}


int matrixChainMultiplication(vector<int>&arr) {
	int n = arr.size();
	//for recursion
	// int res = calculateOperations(1, n - 1, arr);

	//for memoization
	vector<vector<int>> dp(n, vector<int>(n, -1));
	int res = calculateOperationsMemo(1, n - 1, arr, dp);

	return res;
}


int main() {
	int n;
	cin >> n;
	vector<int>arr(n);
	for (int &i : arr) cin >> i;
	cout << matrixChainMultiplication(arr);
	return 0;

}
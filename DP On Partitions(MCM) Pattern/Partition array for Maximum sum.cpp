#include<bits/stdc++.h>
using namespace std;

//memoisation approach
int doPartitions(int ind, vector<int> &arr, int k, vector<int> &dp) {
	int n = arr.size();
	//base case
	if (ind == n)  return 0;
	if (dp[ind] != -1) return dp[ind];
	//main stuff
	int lenOfSubarr = 1, maxValue = INT_MIN, maxi = INT_MIN/*for storing the max value for each subarray*/;
	for (int j = ind; j < min(n, ind + k); j++) {
		maxi = max(maxi, arr[j]);
		int cost = (lenOfSubarr++ * maxi) + doPartitions(j + 1, arr, k, dp);
		cout << cost << " ";
		maxValue = max(cost, maxValue);
	}
	return dp[ind] = maxValue;
}


//main problem function
int maxSumAfterPartitioning(vector<int>& arr, int k) {
	int n = arr.size();
//memoisation code
	vector<int> dp(n, -1);
	int res = doPartitions(0, arr, k, dp);
	return res;
}

int main() {
	int n;
	cin >> n;
	vector<int> arr(n);
	for (int &i : arr) cin >> i;
	int k; cin >> k;
	cout << maxSumAfterPartitioning(arr, k);
	return 0;

}
#include <bits/stdc++.h>
using namespace std;


//this is the recursive and memoization solution for the problem

int findMaxAmongAll(int i, vector<int> &a, vector<int> &dp) {
	//base case
	if (i == 0) return a[i];
	if (i < 0) return 0;
	if (dp[i] != -1) return dp[i];
	int pick = a[i] + findMaxAmongAll(i - 2, a, dp);
	int notPick = findMaxAmongAll(i - 1, a, dp);
	return dp[i] = max(pick, notPick);
}


//tabulation of the same problem
int maximumNonAdjacentSumTabul(vector<int> &nums) {
	int n = nums.size();
	vector<int> dp(n, -1);
	//base case
	dp[0] = nums[0];
	for (int i = 1; i < n; i++) {
		int pick =  pick = nums[i];
		if (i > 1)pick += dp[i - 2];
		int notPick = dp[i - 1];
		dp[i] = max(pick, notPick);
	}
	return dp[n - 1];
}


//most optimal solution using space optimisation

int maximumNonAdjacentSumSpaceOpt(vector<int> &nums) {
	int n = nums.size();
	int prev = nums[0], prev2 = 0, currI  = 0;
	for (int i = 1 ; i < n; i++) {
		int pick = nums[i];
		if (i > 1) pick += prev2;
		int notPick = prev;
		currI = max(pick, notPick);
		prev2 = prev;
		prev = currI;
	}
	return prev;
}

int maximumNonAdjacentSum(vector<int> &nums) {
	// Write your code here.
	int n = nums.size();
	vector<int> dp(n + 1, -1);
	return findMaxAmongAll(n - 1, nums, dp);
}

int main() {
	int n;
	cin >> n;
	vector<int> nums(n);
	for (int &i : nums) cin >> i;
	// cout << maximumNonAdjacentSum(nums) << endl;
	// cout << maximumNonAdjacentSumTabul(nums) << endl;
	cout << maximumNonAdjacentSumSpaceOpt(nums) << endl;
}
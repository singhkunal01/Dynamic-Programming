#include<bits/stdc++.h>
using namespace  std;

//using basic recursion
int frogJumpKSteps(int ind, int k, vector<int> &heights) {
	if (ind == 0) return 0;//base case
	//now for the k steps
	int  minSteps = INT_MAX;
	for (int j = 1; j <= k; j++) {
		if (ind - j >= 0) {
			int jumps = frogJumpKSteps(ind - j, k, heights) + abs(heights[ind] - heights[ind - j]);
			minSteps = min(minSteps, jumps);
		}
	}
	return minSteps;

}

//another approach using memoization
int frogJumpKSteps(int ind, int k, vector<int> &heights, vector<int> &dp) {
	if (ind == 0) return 0;//base case
	//now for the k steps
	if (dp[ind] != -1) return dp[ind];
	int  minSteps = INT_MAX;
	for (int j = 1; j <= k; j++) {
		if (ind - j >= 0) {
			int jumps = frogJumpKSteps(ind - j, k, heights, dp) + abs(heights[ind] - heights[ind - j]);
			minSteps = min(minSteps, jumps);
		}
	}
	return dp[ind] = minSteps;

}

//another approach using tabulation
int frogJumpKStepsTab(int n, int k, vector<int> &heights) {
	vector<int> dp(n, -1);
	dp[0] = 0;//base case
	for (int i = 1; i < n; i++) {
		int	minSteps = INT_MAX;
		for (int j = 1; j <= k; j++) {
			if (i - j >= 0) {
				int jumps = dp[i - j] + abs(heights[i] - heights[i - j]);
				minSteps = min(minSteps, jumps);
			}
		}
		dp[i] = minSteps;
	}
	return dp[n - 1];
}


//main function
int main() {
	int n, k; cin >> n >> k;
	vector<int> heights(n);
	vector<int> dp(n, -1);
	for (int &i : heights)cin >> i;
	// cout << frogJumpKSteps(n - 1, k, heights) << endl;
	cout << frogJumpKStepsTab(n, k, heights) << endl;
	// cout << frogJumpKSteps(n - 1, k, heights, dp) << endl;
	return 0;
}

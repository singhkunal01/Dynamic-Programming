#include<bits/stdc++.h>
using namespace std;

int findWays(int ind, int target, vector<int> &num, vector<vector<int>> &dp) {
//if we are on the 0th index then if the target is the multiple of the current denomination then only we can pick it
	if (ind == 0) {
		if (target % num[ind] == 0) return target / num[0];
		else return 1e9;
	}
	if (dp[ind][target] != -1)return dp[ind][target];

	int notTake = findWays(ind - 1, target, num, dp);
	int take = 1e9;
	if (num[ind] <= target) take = 1 + findWays(ind, target - num[ind], num, dp);
	return dp[ind][target] = min(take, notTake);
}

int findWaysTabul(vector<int> &num, int target) {
	int n = num.size();
	vector<vector<int>> dp(n, vector<int>(target + 1, 1e8));
	for (int ind = 0; ind <= target; ind++)if (ind % num[0] == 0) dp[0][ind] = ind / num[0];
	for (int ind = 1; ind < n; ind++) {
		for (int tempTarget = 0; tempTarget <= target; tempTarget++) {
			int notTake = dp[ind - 1][tempTarget];
			int take = 1e8;
			if (num[ind] <= tempTarget) take = 1 + dp[ind][tempTarget - num[ind]];
			dp[ind][tempTarget] = min(take, notTake);
		}
	}
	int ans = dp[n - 1][target];
	return ans < 1e8 ? ans : -1;
}


// space optimisation approach using 1d Dp
int findWaysSpaceOpt(vector<int> &num, int target) {
	int n = num.size();
	vector<int> prev(target + 1, 1e9), curr(target + 1, 1e9);
	for (int ind = 0; ind <= target; ind++)if (ind % num[0] == 0) prev[ind] = ind / num[0];
	for (int ind = 1; ind < n; ind++) {
		for (int tempTarget = 0; tempTarget <= target; tempTarget++) {
			int notTake = prev[tempTarget];
			int take = 1e9;
			if (num[ind] <= tempTarget) take = 1 + curr[tempTarget - num[ind]];
			curr[tempTarget] = min(take, notTake);
		}
		prev = curr;
	}
	int ans = prev[target];
	return ans < 1e9 ? ans : -1;
}


int minimumElements(vector<int> &num, int target)
{
	// write your code here
	int n = num.size();
	// vector<vector<int>> dp(n, vector<int>(target + 1, -1));
	//for memoisation + recursion
	// int ans = findWays(n - 1, target, num, dp);
	//for tabulation
	int ans = findWaysTabul(num, target);
	//space optimised
	// int ans = findWaysSpaceOpt(num, target);
	return ans < 1e9 ? ans : -1;
}

int main() {
	int n;
	cin >> n;
	int target; cin >> target;
	vector<int> num(n);
	for (int &i : num)cin >> i;
	cout << minimumElements(num, target);
	return 0;

}
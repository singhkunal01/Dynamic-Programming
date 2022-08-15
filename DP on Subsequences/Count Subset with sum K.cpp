#include<bits/stdc++.h>
using namespace std;

//code using recursive approach TC -O(2^N) SC - O(N)auxiliary stack space
int countPossibleSubsets(int ind, vector<int> &nums, int target) {
//base case
	if (target == 0)return 1;
	if (ind == 0) return nums[ind] == target;
	//as the question is on subsets then we can break down in terms of indices
	int pick = 0;
	if (nums[ind] <= target)pick = countPossibleSubsets(ind - 1, nums, target - nums[ind]);
	int notPick = countPossibleSubsets(ind - 1, nums, target);
	return pick + notPick;
}


//code for dp memoisation approach
int countPossibleSubsetsMemo(int ind, vector<int> &nums, int target, vector<vector<int>> &memo) {
//base case
	if (ind == 0) {
		if (target == 0 and nums[ind] == 0) return 2;//if both the condition satisfies then the answer will be 2 if the first index is 0 we have to include it too in our subset
		if (target == 0 or nums[ind] == target) return 1;
		return 0;
	}

	if (memo[ind][target] != -1) return memo[ind][target];
	//as the question is on subsets then we can break down in terms of indices
	int pick = 0;
	if (nums[ind] <= target)pick = countPossibleSubsetsMemo(ind - 1, nums, target - nums[ind], memo);
	int notPick = countPossibleSubsetsMemo(ind - 1, nums, target, memo);
	return memo[ind][target] = pick + notPick;
}

//tabulation approach
int countPossibleSubsetsTabul(vector<int> &num, int target) {
	int n = num.size();
	vector<vector<int>> dp(n, vector<int> (target + 1));

	//base cases
	/*breaking down the first base case like this , suppose if the index is 0 and target is 0 which means we have to fill
	dp[0][0] by 2 but under the condition  if (num[0] == 0) for the other rest cases */

	dp[0][0] = (num[0] == 0) ?  2 : 1;

	/*	now for the seond base where the index is 0 but target can be equal to the num[ind] i.e., num[0] , but for that we have to take care of some
	conditions like if (num[0] != 0) because previously we have take care of when the num[0] == 0 and as similar to the SUBSET SUM EQUAL TO TARGET
	we have to add the other condition for the first index which we pick only when num[0] <= target;*/
	if (num[0] != 0 and num[0] <= target) dp[0][num[0]] = 1;

//for the rest stuff
	for (int ind = 1; ind < n; ind++) {
		for (int tar = 0; tar <= target; tar++) {
			int notPick = dp[ind - 1][tar];
			int pick = 0;
			if (num[ind] <= tar) pick = dp[ind - 1][tar - num[ind]];
			dp[ind][tar] = pick + notPick;
		}
	}
	return dp[n - 1][target];
}

// space optimisation approach
int countPossibleSubsetsSpaceOpt(vector<int> &num, int target) {
	int n = num.size();
	vector<int> prev(target + 1), curr(target + 1);

	//base cases
	/*breaking down the first base case like this , suppose if the index is 0 and target is 0 which means we have to fill
	dp[0][0] by 2 but under the condition  if (num[0] == 0) for the other rest cases */

	prev[0] = (num[0] == 0) ?  2 : 1;

	/*	now for the seond base where the index is 0 but target can be equal to the num[ind] i.e., num[0] , but for that we have to take care of some
	conditions like if (num[0] != 0) because previously we have take care of when the num[0] == 0 and as similar to the SUBSET SUM EQUAL TO TARGET
	we have to add the other condition for the first index which we pick only when num[0] <= target;*/
	if (num[0] != 0 and num[0] <= target) prev[num[0]] = 1;

//for the rest stuff
	for (int ind = 1; ind < n; ind++) {
		for (int tar = 0; tar <= target; tar++) {
			int notPick = prev[tar];
			int pick = 0;
			if (num[ind] <= tar) pick = prev[tar - num[ind]];
			curr[tar] = pick + notPick;
		}
		prev = curr;
	}
	return prev[target];
}


int findWays(vector<int> &num, int tar) {
	// Write your code here.
	int n = num.size();
	vector<vector<int>> memo(n , vector<int>(tar + 1, -1));
	// int result = countPossibleSubsets(n - 1, num, tar);
	// int result = countPossibleSubsetsMemo(n - 1, num, tar, memo);
	// int result = countPossibleSubsetsTabul(num, tar);
	int result = countPossibleSubsetsSpaceOpt(num, tar);
	return result;
}

int main() {

	int n; cin >> n;
	int target; cin >> target;
	vector<int> arr(n);
	for (int &i : arr) cin >> i;
	cout << "Total Ways : " << findWays(arr, target) << endl;
	return 0;

}

#include<bits/stdc++.h>
using namespace std;

//recursive solution TC - O(2^N) SC - O(N);
bool checkForTheValidSubset(int currInd, int target,  vector<int> &arr) {
	if (target == 0) return true;
	if (currInd == 0) return arr[0] == target;
	int notPick = checkForTheValidSubset(currInd - 1, target, arr);
	int pick = false;
	if (target >= arr[currInd])pick = checkForTheValidSubset(currInd - 1, target - arr[currInd], arr);
	return (pick or notPick);
}


//memoisation approach - TC - O(N* target) SC - O(N*target)+O(N)
bool checkForTheValidSubsetMemo(int currInd, int target,  vector<int> &arr, vector<vector<int>> &dp) {
	if (target == 0) return true;
	if (dp[currInd][target] != -1) return dp[currInd][target];
	if (currInd == 0) return arr[0] == target;
	int notPick = checkForTheValidSubsetMemo(currInd - 1, target, arr, dp);
	int pick = false;
	if (target >= arr[currInd])pick = checkForTheValidSubsetMemo(currInd - 1, target - arr[currInd], arr, dp);
	return dp[currInd][target] = (pick or notPick);
}

// tabulation approach -  TC - O(N* target) SC - O(N*target)
bool checkForTheValidSubsetTabul(int n, int target, vector<int> &arr) {
	vector<vector<bool>> dp(n, vector<bool> (target + 1, false));
	//for the first base case considering target as 0
	for (int i = 0 ; i < n; i++) dp[i][0] = true;
//for the second base considering the index as 0
	if (arr[0] <= target) dp[0][arr[0]] = true;
//for rest stuff
	for (int index = 1; index < n; index++) {
		for (int givenTarget = 1; givenTarget <= target ; givenTarget++) {
			bool notPick = dp[index - 1][givenTarget];
			bool pick = false;
			if (givenTarget >= arr[index]) pick = dp[index - 1][givenTarget - arr[index]];
			dp[index][givenTarget] = (pick or notPick);
		}
	}
	return dp[n - 1][target];
}


//space optimised approach -
bool checkForTheValidSubsetSpaceOptimise(int n, int target, vector<int> &arr) {
	vector<bool> prev(target + 1, false), curr(target + 1, false);
	//for the first base case considering target as 0
	prev[0] = curr[0] = true;
//for the second base considering the index as 0
	prev[arr[0]] = true;
//for rest stuff
	for (int index = 1; index < n; index++) {
		for (int givenTarget = 1; givenTarget <= target ; givenTarget++) {
			bool notPick = prev[givenTarget];
			bool pick = false;
			if (givenTarget >= arr[index]) pick = prev[givenTarget - arr[index]];
			curr[givenTarget] = (pick or notPick);
		}
		prev = curr;
	}
	return prev[target];
}


bool subsetSumToK(int n, int target, vector<int> &arr) {
	vector<vector<int>> dp(n + 1, vector<int> (target + 1, -1));
	// int ans = checkForTheValidSubset(n - 1, target, arr);
	int ans = checkForTheValidSubsetMemo(n - 1, target, arr, dp);
	// int ans = checkForTheValidSubsetTabul(n, target, arr);
	// int ans = checkForTheValidSubsetSpaceOptimise(n, target, arr);
	return ans;
}

int main() {
	int size;
	cin >> size;
	vector<int> arr(size);
	for (int &i : arr) cin >> i;
	int target; cin >> target;
	if (subsetSumToK(size, target, arr)) cout << "Is Valid Subsequence" << endl;
	else cout << "Is Invalid Subsequence" << endl;
	return 0;

}
#include<bits/stdc++.h>
using namespace std;

//recursive solution
bool checkForTheValidSubset(int currInd, int target,  vector<int> &arr, vector<vector<int>> &dp) {
	if (target == 0) return true;
	if (dp[currInd][target] != -1) return dp[currInd][target];
	if (currInd == 0) return arr[0] == target;
	int notPick = checkForTheValidSubset(currInd - 1, target, arr, dp);
	int pick = false;
	if (target >= arr[currInd])pick = checkForTheValidSubset(currInd - 1, target - arr[currInd], arr, dp);
	return dp[currInd][target] = (pick or notPick);
}

bool subsetSumToK(int n, int target, vector<int> &arr) {
	vector<vector<int>> dp(n + 1, vector<int> (target + 1, -1));
	return checkForTheValidSubset(n - 1, target, arr, dp);
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
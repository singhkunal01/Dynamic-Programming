#include<bits/stdc++.h>
using namespace std;

/*This code is valid only for the Codestudio one problem not for the leetcode one because leetcode one has negatives also*/

//most optimal approach
int minSubsetSumDifference(vector<int>& arr, int n)
{
	int target = accumulate(arr.begin(), arr.end(), 0);
	vector<vector<bool>> dp(n, vector<bool> (target + 1, false));
	//for the first base case considering target as 0
	for (int i = 0 ; i < n; i++) dp[i][0] = true;
//for the second base considering the index as 0
	if (arr[0] <= target)dp[0][arr[0]] = true;
//for rest stuff
	for (int index = 1; index < n; index++) {
		for (int givenTarget = 1; givenTarget <= target ; givenTarget++) {
			bool notPick = dp[index - 1][givenTarget];
			bool pick = false;
			if (givenTarget >= arr[index]) pick = dp[index - 1][givenTarget - arr[index]];
			dp[index][givenTarget] = (pick or notPick);
		}
	}
	/*	here the required ans is in this row dp[n - 1][target] , where target lies from 0 to totalSum but
		as we saw that there will be half values which occurs in both the sets at a time so for optimising we
		can use totalSum / 2 */
	int miniAbsDiff = INT_MAX;
	for (int setFirst = 0; setFirst <= target / 2; setFirst++) {
		if (dp[n - 1][setFirst]) {
			miniAbsDiff = min(miniAbsDiff, abs((target - setFirst) - setFirst));
			//here target - setFirst can be visualised as the second subset and setFirst is the first subset
		}
	}
	return miniAbsDiff;
}

int main() {
	int n; cin >> n;
	vector<int> arr(n);
	for (int &i : arr) cin >> i;
	cout << "minSubsetSumDifference : " << minSubsetSumDifference(arr, n) << endl;
	return 0;

}
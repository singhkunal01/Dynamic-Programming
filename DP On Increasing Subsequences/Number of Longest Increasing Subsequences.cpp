#include<bits/stdc++.h>
using namespace std;


int findNumberOfLIS(vector<int>& nums) {
	int n = nums.size();
	vector<int> dp(n, 1), curr(n, 1);
	int maxLength = 0;
	for (int i =  0; i < n; i++) {
		for (int prev = 0; prev < i; prev++) {
			if (nums[i] > nums[prev] && dp[i] < 1 + dp[prev]) {//another condition is for preventing it to change afterward if somewhere the value is same
				dp[i] = max(dp[i], 1 + dp[prev]);
				curr[i] = curr[prev];
			}
			else if (nums[i] > nums[prev] && dp[i] == 1 + dp[prev]) curr[i] += curr[prev];
		}
		maxLength = max(maxLength, dp[i]);
	}

	/*	for (int i : dp) cout << i << " ";
		cout << endl;
		for (int i : curr) cout << i << " ";
		cout << endl;
	*/
	int totalCount = 0;
	for (int i = 0 ; i < n; i++) {
		if (dp[i] == maxLength) totalCount += curr[i];
	}
	return totalCount;
}

int main() {
	int n; cin >> n;
	vector<int> arr(n);
	for (int &i : arr) cin >> i;
	cout << findNumberOfLIS(arr);
	return 0;

}
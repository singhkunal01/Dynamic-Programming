#include<bits/stdc++.h>
using namespace std;


vector<int> largestDivisibleSubset(vector<int>& nums) {
	sort(nums.begin(), nums.end());
	int n = nums.size();
	vector<int> dp(n, 1), track(n);
	int lastIdx = -1, maxLength = 0;
	for (int i = 0 ; i < n; i++) track[i] = i;
	for (int i =  0; i < n; i++) {
		for (int prev = 0; prev < i; prev++) {
			if (nums[i] % nums[prev] == 0 && dp[i] < 1 + dp[prev]) {
				dp[i] = max(dp[i], 1 + dp[prev]);
				track[i] = prev;
			}
		}
		if (dp[i] > maxLength) {
			maxLength = dp[i];
			lastIdx = i;
		}
	}
	vector<int> lis(maxLength);
	lis[maxLength - 1] = nums[lastIdx];
	if (maxLength < 2) return lis;
	for (int i = maxLength - 2; i >= 0; i--) {
		lis[i] = nums[track[lastIdx]];
		lastIdx = track[lastIdx];
	}
	return lis;
}

int main() {

	int n; cin >> n;
	vector<int> arr(n);
	for (int &i : arr) cin >> i;
	vector<int> res =  largestDivisibleSubset(arr);
	for (int i : res) cout << i << " ";
	return 0;

}
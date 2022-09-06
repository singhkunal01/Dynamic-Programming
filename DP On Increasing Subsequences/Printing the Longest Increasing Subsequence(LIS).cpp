/*


------------------------------- Link - https://bit.ly/3AVDO1H------------------------------- */

#include<bits/stdc++.h>
using namespace std;

/*1D dp solution for Finding the length of Longest Increasing Subsequence */
int lengthOfLIS(vector<int> &nums) {
	int n = nums.size();
	vector<int> dp(n, 1);
	int maxLength = 0;
	//now iterate over all indices with the prev from [0,i-1]
	for (int i =  0; i < n; i++) {
		for (int prev = 0; prev < i; prev++) {
			if (nums[i] > nums[prev])
				dp[i] = max(dp[i], 1 + dp[prev]);
		}
		maxLength = max(maxLength, dp[i]);
	}
	return maxLength;
}


/*now the above code is used for printing the LIS in O(N^2)
Basically we take a different hash array which keep track of changes in the dp array like whenever the
length is changed from prev then we keep the index because of which the value get changed
*/
vector<int> printLIS(vector<int> &nums) {
	int n = nums.size();
	vector<int> dp(n, 1), track(n);
	int lastIdx = -1, maxLength = 0;
	for (int i = 0 ; i < n; i++) track[i] = i;//fill it with the indices
	for (int i =  0; i < n; i++) {
		for (int prev = 0; prev < i; prev++) {
			if (nums[i] > nums[prev] && dp[i] < 1 + dp[prev]) {//another condition is for preventing it to change afterward if somewhere the value is same
				dp[i] = max(dp[i], 1 + dp[prev]);
				track[i] = prev;
			}
		}
		if (dp[i] > maxLength) {
			maxLength = dp[i];//it keeps the max length  of LIS in the dp array
			lastIdx = i;//it keeps the index where we go from the dp to the hash array
		}
	}
//find the maximum in the dp array then get the value at that index then move to same index in the hash array then move
//index of index in the hash array
	vector<int> lis(maxLength);
	lis[maxLength - 1] = nums[lastIdx]; //this is the last value of the LIS(i.e., greatest one)
	if (maxLength < 2) return lis;
	for (int i = maxLength - 2; i >= 0; i--) {
		lis[i] = nums[track[lastIdx]];
		lastIdx = track[lastIdx];
	}
	return lis;
}

int main() {
	int n; cin >> n;
	vector<int> nums(n);
	for (int &i : nums) cin >> i;
	// cout << lengthOfLIS(nums);
	vector<int> res = printLIS(nums);
	cout << "Longest Increasing Subsequence : ";
	for (int i : res) cout << i << " ";
	return 0;

}
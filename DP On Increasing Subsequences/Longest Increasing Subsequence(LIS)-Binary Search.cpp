#include<bits/stdc++.h>
using namespace std;

int lengthOfLISusingBinarySearch(vector<int> &nums) {
	vector<int> lis;
	int n = nums.size();
	lis.push_back(nums[0]);
	for (int i = 1; i < n; i++ ) {
		if (nums[i] > lis.back()) {
			lis.push_back(nums[i]);
		}
		else {
			int idx = lower_bound(lis.begin(), lis.end(), nums[i]) - lis.begin();
			lis[idx] = nums[i];
		}
	}
	return lis.size();
}

int main() {
	int n;
	cin >> n;
	vector<int>seq(n);
	for (int &i : seq) cin >> i;
	cout << "Length of LIS : " << lengthOfLISusingBinarySearch(seq);
	return 0;

}
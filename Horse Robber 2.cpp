#include<bits/stdc++.h>
using namespace std;


long long int maximumNonAdjacentSumSpaceOpt(vector<int> &nums) {
	int n = nums.size();
	long long int prev = nums[0], prev2 = 0, currI  = 0;
	for (int i = 1 ; i < n; i++) {
		long long int pick = nums[i];
		if (i > 1) pick += prev2;
		long long int notPick = prev;
		currI = max(pick, notPick);
		prev2 = prev;
		prev = currI;
	}
	return prev;
}

long long int houseRobber(vector<int>& valueInHouse)
{
	// Write your code here.
	int n  = valueInHouse.size();
	if (n == 1) return valueInHouse[0];
	vector<int> withoutFirst, withoutLast;
	for (int i = 0; i < n; i++) {
		if (i != 0) withoutFirst.push_back(valueInHouse[i]);
		if (i != n - 1) withoutLast.push_back(valueInHouse[i]);
	}
	int ansWithoutFirst = maximumNonAdjacentSumSpaceOpt(withoutFirst);
	int ansWithoutLast = maximumNonAdjacentSumSpaceOpt(withoutLast);
	return max(ansWithoutLast, ansWithoutFirst);

}

int main() {
	int n;
	cin >> n;
	vector<int> nums(n);
	for (int &i : nums) cin >> i;
	cout << houseRobber(nums) << endl;
}

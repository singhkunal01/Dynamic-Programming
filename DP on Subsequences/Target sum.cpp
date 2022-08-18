#include<bits/stdc++.h>
using namespace std;

//memoisation is the approach i am usign here , we can also use space optimised or tabulation here

/*this question is exact similar to the tutorial 18 i.e., Count partitions with the given difference . instead of putting signs we
have to just divide array in such a way so that the difference of both the subsets is equals to the target */

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



int targetSum(int n, int d, vector<int> &arr) {
	int target = 0;
	for (int i : arr) target += i;
	vector<vector<int>> memo(n , vector<int>(target + 1, -1));
	if (target - d < 0 or ((target - d) & 1)) return 0;
	/*
	lets say total sum will be Target now we know that for two subsets say s1,s2 -
	target = s1+s2 or s1 =target - s2, -------------- (1)
	on the therr hand in the question given that the difference of two required subsets will be D so,
	D= s1 - s2------------------(2)
	from eqn (1),
	D = target - s2 -s2 = target - 2s2
	hence s2 = (target - D)/2 so this will be our target  and from the last problem we can observe that if we find find one subset
	then automatically 2nd is in our hand
	*/
	return countPossibleSubsetsMemo(n - 1, arr, (target - d) / 2, memo);
}

int main() {

	int n; cin >> n;
	int diff; cin >> diff;
	vector<int> arr(n);
	for (int &i : arr) cin >> i;
	cout << "Number of Ways : " << targetSum(n, diff, arr) << endl;
	return 0;

}
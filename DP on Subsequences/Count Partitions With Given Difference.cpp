#include<bits/stdc++.h>
using namespace std;

//most optimal approach we can also use memoisation or tabulation here

const int mod = 1e9 + 7;

// space optimisation approach
int countPossibleSubsetsSpaceOpt(vector<int> &num, int target) {
	int n = num.size();
	vector<int> prev(target + 1), curr(target + 1);

	//base cases
	/*breaking down the first base case like this , suppose if the index is 0 and target is 0 which means we have to fill
	dp[0][0] by 2 but under the condition  if (num[0] == 0) for the other rest cases */

	prev[0] = (num[0] == 0) ?  2 : 1;

	/*    now for the seond base where the index is 0 but target can be equal to the num[ind] i.e., num[0] , but for that we have to take care of some
	conditions like if (num[0] != 0) because previously we have take care of when the num[0] == 0 and as similar to the SUBSET SUM EQUAL TO TARGET
	we have to add the other condition for the first index which we pick only when num[0] <= target;*/
	if (num[0] != 0 and num[0] <= target) prev[num[0]] = 1;

//for the rest stuff
	for (int ind = 1; ind < n; ind++) {
		for (int tar = 0; tar <= target; tar++) {
			int notPick = prev[tar] % mod;
			int pick = 0;
			if (num[ind] <= tar) pick = prev[tar - num[ind]] % mod;
			curr[tar] = (pick % mod + notPick % mod) % mod;
		}
		prev = curr;
	}
	return prev[target] % mod;
}


int countPartitions(int n, int d, vector<int> &arr) {
	// Write your code here.
	int target = 0;
	for (int i : arr) target += i;
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
	return countPossibleSubsetsSpaceOpt(arr, (target - d) / 2);
}

int main() {

	int n; cin >> n;
	int diff; cin >> diff;
	vector<int> arr(n);
	for (int &i : arr) cin >> i;
	cout << "Count : " << countPartitions(n, diff, arr) << endl;
	return 0;

}
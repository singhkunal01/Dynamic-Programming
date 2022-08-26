#include<bits/stdc++.h>
using namespace std;


/*recursive + memoization code*/
int findMinimumOperations(int i, int j, string &mainStr, string &target, vector<vector<int>> &dp) {
	//base cases are quite tricky like when we exhausted either of the string
	//if we exhausted the first string then wherever the jth pointer we have that much characters remaining to traverse so
	if (i == 0) return j;
	//if we exhausted the second string then wherever the ith pointer we have that much characters remaining to get converted so
	if (j == 0) return i;

	//memoization base case
	if (dp[i][j] != -1) return dp[i][j];
	//now if both the characters are matched then
	if (mainStr[i - 1] == target[j - 1]) return dp[i][j] = findMinimumOperations(i - 1, j - 1, mainStr, target, dp);
	//else we have to do three operations for insertion , for deletion & for replacement
	return dp[i][j] = min({1 + findMinimumOperations(i, j - 1, mainStr, target, dp),/*for insertion if we hypothetically insert the character to get matched
	then obviously our ith pointer remains same because we add the character at the last of mainStr and now hypothetically both the characters are
	matched so we gonna move out jth pointer*/
	                       1 + findMinimumOperations(i - 1, j, mainStr, target, dp), /*now for deletion means we don't want that character from mainStr so
	            just to skip that move our ith Pointer and stay on jth to compare it with upcoming character*/
	                       1 + findMinimumOperations(i - 1, j - 1, mainStr, target, dp)/*for replacement means we replaced the current ith Character hypothetically
	            and we gonna move further that is after replacement the characters got matched so move both pointers*/
	                      });

}

/*tabulation approach - Now we saw that we have the bases where pointer goes < 0 so we need to shift the indices
for that we have to check (mainStr[i-1] == target[j-1]) instead of (mainStr[i] == target[j]) like previous questions
*/
int findMinimumOperationsTabul(string &mainStr, string &target) {
	int n = mainStr.size(), m = target.size();
	vector<vector<int>> dp(n + 1, vector<int>(m + 1));

	//base cases
	for (int i = 0; i <= n; i++) dp[i][0] = i;
	for (int j = 0; j <= m; j++) dp[0][j] = j;

//we have set the bases for 0 so start from 1
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (mainStr[i - 1] == target[j - 1])
				dp[i][j] = dp[i - 1][j - 1];
			else dp[i][j] = min({1 + dp[i][j - 1], 1 + dp[i - 1][j], 1 + dp[i - 1][j - 1]});
		}
	}
	return dp[n][m];
}

/*space optimised approach */
int findMinimumOperationsSpaceOpt(string &mainStr, string &target) {
	int n = mainStr.size(), m = target.size();
	vector<int>prev(m + 1), curr(m + 1);

	//base cases
	for (int j = 0; j <= m; j++) prev[j] = j;

//we have set the bases for 0 so start from 1
	for (int i = 1; i <= n; i++) {
		curr[0] = i;//for every first element in every row the element should be equals to i
		for (int j = 1; j <= m; j++) {
			if (mainStr[i - 1] == target[j - 1])
				curr[j] = prev[j - 1];
			else curr[j] = min({1 + curr[j - 1], 1 + prev[j], 1 + prev[j - 1]});
		}
		prev = curr;
	}
	return prev[m];
}

int editDistance(string & mainStr, string & target) {
	int n = mainStr.size(), m = target.size();

	/*for memoization */
	// vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
	// int res =  findMinimumOperations(n, m, mainStr, target, dp);


	/*for tabulation*/
	// int res = findMinimumOperationsTabul(mainStr, target);

	/*for space optimised approach*/
	int res = findMinimumOperationsSpaceOpt(mainStr, target);
	return res;
}

int main() {

	string mainStr, target;
	cin >> mainStr >> target;
	cout << editDistance(mainStr, target);
	return 0;

}
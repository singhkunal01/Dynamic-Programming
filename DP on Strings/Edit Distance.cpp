#include<bits/stdc++.h>
using namespace std;


/*recursive + memoization code*/
int findMinimumOperations(int i, int j, string &mainStr, string &target, vector<vector<int>> &dp) {
	//base cases are quite tricky like when we exhausted either of the string
	//if we exhausted the first string then wherever the jth pointer we have that much characters remaining to traverse so
	if (i < 0) return j + 1;
	//if we exhausted the second string then wherever the ith pointer we have that much characters remaining to get converted so
	if (j < 0) return i + 1;

	//memoization base case
	if (dp[i][j] != -1) return dp[i][j];
	//now if both the characters are matched then
	if (mainStr[i] == target[j]) return dp[i][j] = findMinimumOperations(i - 1, j - 1, mainStr, target, dp);
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


int editDistance(string & mainStr, string & target) {
	int n = mainStr.size(), m = target.size();

	/*for memoization */
	vector<vector<int>> dp(n, vector<int>(m + 1, -1));
	int res =  findMinimumOperations(n - 1, m - 1, mainStr, target, dp);


	return res;
}

int main() {

	string mainStr, target;
	cin >> mainStr >> target;
	cout << editDistance(mainStr, target);
	return 0;

}
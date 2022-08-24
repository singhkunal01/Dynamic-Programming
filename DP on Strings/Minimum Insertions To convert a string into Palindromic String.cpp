#include<bits/stdc++.h>
using namespace std;

/* recrusion  + memoization code - We can also use Tabulation and Space optimised code for
More see it in the Anothe code i.e., LCS or LPS */

int findLPSMemo(int i, int j, string &mainStr, string &rev, vector<vector<int>> &dp) {
//base case
	if (i == 0 or j == 0) return 0;
	if (dp[i][j] != -1) return dp[i][j];
	if (mainStr[i - 1] == rev[j - 1])
		return dp[i][j] = 1 + findLPSMemo(i - 1, j - 1, mainStr, rev, dp);
	return dp[i][j] = max(findLPSMemo(i - 1, j, mainStr, rev, dp),
	                      findLPSMemo(i, j - 1, mainStr, rev, dp));
}


int minimumInserionsToMakePalindromicString(string &str) {
	int n = str.size();
	string rev = str;
	//for memoization
	reverse(rev.begin(), rev.end());

	vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));
	int lengthOfLPS = findLPSMemo(n, n, str, rev, dp);

	int minimumCharacersNeedToInsert = n - lengthOfLPS;

	return minimumCharacersNeedToInsert;
}

int main() {
	string s;
	cin >> s;
	cout << minimumInserionsToMakePalindromicString(s);
	return 0;

}
//@singhkunal01
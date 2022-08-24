#include<bits/stdc++.h>
using namespace std;


/*----------------tabulation approach , we can also use Memoization and Space optimization ----------------*/

int findLCSOfBothStrings(string &str1, string &str2) {
	int n = str1.size(), m = str2.size();
	vector<vector<int>> dp(n + 1, vector<int> (m + 1, -1));
	for (int i = 0 ; i <= n; i++)dp[i][0] = 0;//for the row
	for (int i = 0 ; i <= m; i++)dp[0][i] = 0;//for the column
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (str1[i - 1] == str2[j - 1]) dp[i][j] = 1 + dp[i - 1][j - 1];
			else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
		}
	}
	return dp[n][m];
}

int minimumInserionsDeletionsToMakeBothStringsEqual(string &s1, string &s2) {
	int n = s1.size(), m = s2.size();
	int lcsOfBoth = findLCSOfBothStrings(s1, s2);
	int minOperationsRequired = (n + m) - (2 * lcsOfBoth);
	return minOperationsRequired;
}

int main() {
	string s1, s2;
	cin >> s1 >> s2;
	cout << minimumInserionsDeletionsToMakeBothStringsEqual(s1, s2);
	return 0;

}
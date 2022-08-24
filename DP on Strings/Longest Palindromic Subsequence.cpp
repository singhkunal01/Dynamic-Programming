#include<bits/stdc++.h>
using namespace std;

//we can also use memoisation or space optimised approach but i used Tabulation here

/* ------------------------This is to print the length of longest palindromic subsequence------------------------ */

int longestPalindromicSubsequence(string &s) {
	int n = s.size();
	vector<vector<int>> dp(n + 1, vector<int> (n + 1));
	string rev = s;
	reverse(begin(rev), end(rev));
//base cases
	for (int i = 0; i <= n; i++) {
		dp[0][i] = 0;
		dp[i][0] = 0;
	}
//rest of the cases
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			//if both the characters are same then
			if (s[i - 1] == rev[j - 1]) {
				dp[i][j] = 1 + dp[i - 1][j - 1];
			}
			else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
		}
	}
	return dp[n][n];
}



/*----------------------------This is to print one of the longest Palindromic subsequence----------------------------*/

string printLongestPalindromicSubsequence(string &s) {
	int n = s.size();
	vector<vector<int>> dp(n + 1, vector<int> (n + 1));
	string rev = s;
	reverse(begin(rev), end(rev));
//base cases
	for (int i = 0; i <= n; i++) {
		dp[0][i] = 0;
		dp[i][0] = 0;
	}
//rest of the cases
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			//if both the characters are same then
			if (s[i - 1] == rev[j - 1]) {
				dp[i][j] = 1 + dp[i - 1][j - 1];
			}
			else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
		}
	}
	int row = n, col = n;
	string res;
	while (row > 0 and col > 0) {
		/*same as the recurrence we have two choices either the character is same or not
		if not then take the max and move accordingly */

		if (s[row - 1] == rev[col - 1]) {
			res = s[row - 1] + res;
			row--, col--;
		}
		else if (dp[row - 1][col] > dp[row][col - 1]) row--;
		else col--;
	}
	return res;
}

int main() {
	string s; cin >> s;
	cout << longestPalindromicSubsequence(s) << " ";
	cout << printLongestPalindromicSubsequence(s) ;
	return 0;

}
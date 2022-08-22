#include<bits/stdc++.h>
using namespace std;

/*Recursive + Memoisation code */
int lcs(int i, int j , string &str1, string &str2, vector<vector<int>> &dp) {
//base case
	if (i < 0 or j < 0) return 0;
	if (dp[i][j] != -1) return dp[i][j];
	//if the current both characters are same then
	if (str1[i] == str2[j])
		return dp[i][j] = 1 + lcs(i - 1, j - 1, str1, str2, dp);
	/*	else if both the ith and jth characters are different then there can be
		two possibilities one for the str1 and another for str2 to break*/
	return dp[i][j] = max(lcs(i - 1, j, str1, str2, dp), lcs(i, j - 1, str1, str2, dp));
}

int longestCommonSubsequence(string str1, string str2) {
	int n = str1.size(), m = str2.size();
	vector<vector<int>> dp(n + 1, vector<int> (m + 1, -1));
	return lcs(n - 1, m - 1, str1, str2, dp);

}

int main() {

	string str1, str2;
	cin >> str1 >> str2;
	cout << longestCommonSubsequence(str1, str2);
	return 0;

}
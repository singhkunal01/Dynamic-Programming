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



/*Recursive + Memoisation code after shifting the index */
int lcsAfterShifting(int i, int j , string &str1, string &str2, vector<vector<int>> &dp) {
//base case
	if (i == 0 or j == 0) return 0;
	if (dp[i][j] != -1) return dp[i][j];
	//if the current both characters are same then
	if (str1[i - 1] == str2[j - 1])
		return dp[i][j] = 1 + lcsAfterShifting(i - 1, j - 1, str1, str2, dp);
	/*	else if both the ith and jth characters are different then there can be
		two possibilities one for the str1 and another for str2 to break*/
	return dp[i][j] = max(lcsAfterShifting(i - 1, j, str1, str2, dp), lcsAfterShifting(i, j - 1, str1, str2, dp));
}


/*tabulation approach for the same */
int lcsTabul(string str1, string str2) {
	int n = str1.size(), m = str2.size();
	vector<vector<int>> dp(n + 1, vector<int> (m + 1, -1));

//if one state is less than zero then another can have no boundations
	for (int i = 0 ; i <= n; i++)dp[i][0] = 0;//for the row
	for (int i = 0 ; i <= m; i++)dp[0][i] = 0;//for the column

	/*Rest of all stuff */
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (str1[i - 1] == str2[j - 1]) dp[i][j] = 1 + dp[i - 1][j - 1];
			else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
		}
	}
	return dp[n][m];

}


/*tabulation approach for the same */
int lcsSpaceOpt(string str1, string str2) {
	int n = str1.size(), m = str2.size();
	vector<int> prev(m + 1), curr (m + 1);

//if one state is less than zero then another can have no boundations
	for (int i = 0 ; i <= m; i++)prev[i] = 0;//for the row

	/*Rest of all stuff */
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (str1[i - 1] == str2[j - 1]) curr[j] = 1 + prev[j - 1];
			else curr[j] = max(prev[j], curr[j - 1]);
		}
		prev = curr;
	}
	return prev[m];

}

int longestCommonSubsequence(string str1, string str2) {
	int n = str1.size(), m = str2.size();

	//for memoisation and recursion -
	// vector<vector<int>> dp(n, vector<int> (m, -1));
	// int res =  lcs(n - 1, m - 1, str1, str2, dp);

	//for memoisation after shifting
	// vector<vector<int>> dp(n + 1, vector<int> (m + 1, -1));
	// int res =  lcsAfterShifting(n, m, str1, str2, dp);

	//for tabulation
	// int res = lcsTabul(str1, str2);

	//for space optimisation one
	int res = lcsSpaceOpt(str1, str2);

	return res;
}

int main() {
// #if
	string str1, str2;
	cin >> str1 >> str2;
	cout << longestCommonSubsequence(str1, str2);
	return 0;

}
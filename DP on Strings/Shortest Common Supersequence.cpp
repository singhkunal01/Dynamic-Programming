#include<bits/stdc++.h>
using namespace std;

/*Tabulation approach to find the longest common subsequence because with the help of this
we can easily find the exact supersequence too - */


/*-------------------This is to the get the length of that supersequence-------------------*/

int findLCSTabul(string &str1, string &str2) {
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
	/*	for (auto i : dp) {
			for (auto j : i)
				cout << j << " ";
			cout << endl;
		}
	*/
	return dp[n][m];
}


/*-------------------This is to print that supersequence------------------- */
string printShortestCommonSupersequence(string &str1, string &str2) {
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
	int row = n, col = m;
	string res;
	while (row > 0 and col > 0) {
		/*same as the recurrence we have two choices either the character is same or not
		if not then take the max and move accordingly */
		if (str1[row - 1] == str2[col - 1]) {
			res = str1[row - 1] + res;
			row--, col--;
		}
		else if (dp[row - 1][col] > dp[row][col - 1]) {
			res = str1[row - 1] + res;
			row--;
		}
		else {
			res = str2[col - 1] + res;
			col--;
		}
	}
	//now if there is something remaining from str1 or str2 then for that we have to handle the cases
	while (row) res  = str1[row - 1] + res, row--;
	while (col) res  = str2[col - 1] + res, col--;
	return res;
}

int shortestCommonSupersequence(string &str1, string &str2) {
	int n = str1.size(), m = str2.size();
	int lengthOfLCS = findLCSTabul(str1, str2);
	//total length of required supersequence is n + m - lengthOfLCS
	int lengthOfSCS = n + m - lengthOfLCS;
	return lengthOfSCS;
}


int main() {

	string str1, str2; cin >> str1 >> str2;
	cout << shortestCommonSupersequence(str1, str2) << endl;
	cout << printShortestCommonSupersequence(str1, str2) << endl;
	return 0;

}
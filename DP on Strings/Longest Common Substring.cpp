#include<bits/stdc++.h>
using namespace std;

int longestCommonSubstringTabul(string &str1, string &str2) {
	int n = str1.size(), m = str2.size();
	vector<vector<int>> dp(n + 1, vector<int> (m + 1, -1));

//if one state is less than zero then another can have no boundations
	for (int i = 0 ; i <= n; i++)dp[i][0] = 0;//for the row
	for (int i = 0 ; i <= m; i++)dp[0][i] = 0;//for the column

	/*Rest of all stuff */
	int maxLength = INT_MIN;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (str1[i - 1] == str2[j - 1])
				dp[i][j] = 1 + dp[i - 1][j - 1], maxLength = max(maxLength, dp[i][j]);
			else dp[i][j] = 0;
		}
	}
	return maxLength;

}


/*tabulation approach for the same */
int lcsSpaceOpt(string str1, string str2) {
	int n = str1.size(), m = str2.size();
	vector<int> prev(m + 1), curr (m + 1);

//if one state is less than zero then another can have no boundations
	for (int i = 0 ; i <= m; i++)prev[i] = 0;//for the row
	int maxLength = INT_MIN;
	/*Rest of all stuff */
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (str1[i - 1] == str2[j - 1]) curr[j] = 1 + prev[j - 1], maxLength = max(maxLength, curr[j]);
			else curr[j] = 0;
		}
		prev = curr;
	}
	return maxLength;

}

int giveLongestCommonSubstring(string str1, string str2) {
	int n = str1.size(), m = str2.size();

	//for tabulation
	// int res = longestCommonSubstringTabul(str1, str2);

	//for space optimisation one
	int res = lcsSpaceOpt(str1, str2);

	return res;
}

int main() {
// #if
	string str1, str2;
	cin >> str1 >> str2;
	cout << giveLongestCommonSubstring(str1, str2);
	return 0;

}
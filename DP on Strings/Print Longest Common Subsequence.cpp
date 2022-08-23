#include<bits/stdc++.h>
using namespace std;

/*tabulation approach */
string printLCS(string str1, string str2) {
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
// till here we have the designed table for our answer with  the help of that we are going to find the string
	// for (int i = 0; i <= n; i++) {for (int j = 0; j <= m; j++) cout << dp[i][j] << " "; cout << endl; } return "";

	/*For the example - str1 = abcde , str2 = bdgek

	Table will look like -
	0 0 0 0 0 0
	0 0 0 0 0 0
	0 1 1 1 1 1
	0 1 1 1 1 1
	0 1 2 2 2 2
	0 1 2 2 3 [3] this is our answer by the help of this we find the required LCS

	For more explanation Go to Lecture of Striver bhaiya's LCS video
	*/
	int row = n, col = m;
	string res;
	while (row > 0 and col > 0) {
		/*same as the recurrence we have two choices either the character is same or not
		if not then take the max and move accordingly */

		if (str1[row - 1] == str2[col - 1]) {
			res = str1[row - 1] + res;
			row--, col--;
		}
		else if (dp[row - 1][col] > dp[row][col - 1]) row--;
		else col--;
	}
	return res;
}

int main() {
	string s, t; cin >> s >> t;
	cout << printLCS(s, t);
	return 0;

}
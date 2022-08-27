#include<bits/stdc++.h>
using namespace std;

bool wildcardMatch(int i, int j, string &s, string &t, vector<vector<int>>&dp) {

//base cases
//1 . if both the strings exhausted
	if (i < 0 and j < 0) return true;
// 2. If string first got exhausted and string 2 has some characters to be match
	if (i<0 and j >= 0) return false;
	/* 3.if string 2 got exhausted and some chars are remaining in the first string then there is observation
	like  according to codestudio problem first string has ? and * but according to leetcode 2 string has ? and *
	so whatever string has ? and * if string other than that is empty then there have to only *
	in the another string because only * will match empty characters so*/
	if (j<0 and i >= 0) {
		for (int k = 0; k <= i; k++ )if (s[k] != '*')
				return false;
		return true;
	}
	if (dp[i][j] != -1) return dp[i][j];
//now main logic
// if both the char matched or a single character is matched with ? then move both pointers
	if (s[i] == t[j] or s[i] == '?') return dp[i][j] = wildcardMatch(i - 1, j - 1, s, t, dp);
	if (s[i] == '*') return dp[i][j] = (wildcardMatch(i - 1, j, s, t, dp) | wildcardMatch(i, j - 1, s, t, dp));
	return dp[i][j] = false;

}

bool isMatch(string &s, string &t) {
	int n = s.size(), m = t.size();

	//for memoization
	vector<vector<int>> dp(n, vector<int>(m, -1));
	bool res = wildcardMatch(n - 1, m - 1, s, t, dp);
	return res;
}

int main() {
	string s, t;
	cin >> s >> t;
	cout << isMatch(s, t);
	return 0;

}
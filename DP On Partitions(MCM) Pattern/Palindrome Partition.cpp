#include<bits/stdc++.h>
using namespace std;

bool isPalindrome(string &str) {
	int n = str.size(), i = 0;
	while (i <= n / 2) {
		if (str[i] != str[n - i - 1])
			return false;
		i++;
	}
	return true;
}

// memoisation code
int doPartitions(int ind, string &s, vector<int>&dp) {
//base case
	if (ind == s.size()) return 0;
	if (dp[ind] != -1) return dp[ind];
	int minCost = INT_MAX;
	string substr;
	for (int j = ind; j < s.size(); j++) {
		substr += s[j];
		if (isPalindrome(substr)) {
			int cost = 1 + doPartitions(j + 1, s, dp);
			minCost = min(cost, minCost);
		}
	}
	return dp[ind] = minCost;;

}

// tabulation code
int doPartitionsTabul(string &s) {
	int n = s.size();
	vector<int> dp(n + 1 , 0);
	for (int ind = n - 1; ind >= 0; ind--) {
		int minCost = INT_MAX;
		string substr;
		for (int j = ind; j < s.size(); j++) {
			substr += s[j];
			if (isPalindrome(substr)) {
				int cost = 1 + dp[j + 1];
				minCost = min(cost, minCost);
			}
			dp[ind] = minCost;
		}
	}
	return dp[0] - 1;
}


//main function
int minCut(string s) {
	int n = s.size();
	/*for memoisation code */
	vector<int> dp(n, -1);
	// int res = doPartitions(0, s, dp) - 1;//as we are also adding the last partition which is at the end of string so for removing that do -1.
	/*for tabulation*/
	int res = doPartitionsTabul(s);
	return res;
}



int main() {

	string s;
	cin >> s;
	cout << minCut(s);
	return 0;

}
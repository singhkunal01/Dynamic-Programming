#include<bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

/*memoisationc code*/

long long findWays(int i, int j, int isTrue, string &exp, vector<vector<vector<long long>>>&dp) {
//base cases
	if (i > j) return 0;
	if (i == j) {
		if (isTrue) return exp[i] == 'T';
		else return exp[i] == 'F';
	}
	if (dp[i][j][isTrue] != -1) return dp[i][j][isTrue];
	//rest of the logic
	long long ways = 0;
	for (int ind = i + 1; ind <= j - 1; ind += 2) {
		int leftTrue = findWays(i, ind - 1, 1, exp, dp);
		int leftFalse = findWays(i, ind - 1, 0, exp, dp);
		int rightTrue = findWays(ind + 1, j, 1, exp, dp);
		int rightFalse = findWays(ind + 1, j, 0, exp, dp);
		//if the operator is &
		if (exp[ind] == '&') {
			if (isTrue) ways = (ways + (leftTrue * rightTrue) % mod) % mod;
			else ways = (ways + (leftTrue * rightFalse) % mod + (leftFalse * rightTrue) % mod + (leftFalse * rightFalse) % mod) % mod;
		}
		//if the operator is |
		if (exp[ind] == '|') {
			if (isTrue) ways = (ways + (leftTrue * rightTrue) % mod + (leftTrue * rightFalse) % mod + (leftFalse * rightTrue) % mod) % mod ;
			else ways = (ways + (leftFalse * rightFalse) % mod) % mod;
		}
		//if the operator is ^
		if (exp[ind] == '^') {
			if (isTrue) ways = (ways +  (leftTrue * rightFalse ) % mod + (leftFalse * rightTrue ) % mod) % mod;
			else ways = (ways + (leftTrue * rightTrue) % mod + (leftFalse * rightFalse) % mod) % mod;
		}
	}
	return dp[i][j][isTrue] = ways;
}


int countWays(int n, string exp) {
	vector<vector<vector<long long>>> dp(n , vector<vector<long long>>(n , vector<long long>(2, -1)));
	int  isTrue = 1;
	int res = findWays(0, n - 1, 1, exp, dp);
	return res;
}

int main() {
	string expression;
	cin >> expression;
	cout << countWays(expression.size(), expression);
	return 0;

}

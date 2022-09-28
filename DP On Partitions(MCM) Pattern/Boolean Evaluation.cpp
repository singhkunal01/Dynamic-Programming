#include<bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

/*memoisation code*/

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


/*tabulation code */
int findWaysTabul(int n, string &exp) {
	vector<vector<vector<long long>>> dp(n , vector<vector<long long>>(n , vector<long long>(2, -1)));
	for (int i = 0; i < n; i++) {
		dp[i][i][1] = exp[i] == 'T';
		dp[i][i][0] = exp[i] == 'F';
	}

//rest of all stuff
	for (int i = n - 1; i >= 0; i--) {
		for (int j = 0; j < n; j++) {
			for (int isTrue = 0; isTrue <= 1; isTrue++) {
				if (i == j) continue;
				if (i > j) dp[i][j][isTrue] = 0;
				long long ways = 0;
				for (int ind = i + 1; ind <= j - 1; ind += 2) {
					int leftTrue = dp[i][ind - 1][ 1];
					int leftFalse = dp[i][ ind - 1][ 0];
					int rightTrue = dp[ind + 1][ j][ 1];

					int rightFalse = dp[ind + 1][ j][ 0];
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
				dp[i][j][isTrue] = ways % mod;
			}
		}
	}
	return dp[0][n - 1][1];
}


int countWays(int n, string exp) {

	/*memoisation code*/
	vector<vector<vector<long long>>> dp(n , vector<vector<long long>>(n , vector<long long>(2, -1)));
	int  isTrue = 1;
	// int res = findWays(0, n - 1, 1, exp, dp);


	//tabulation code
	int res = findWaysTabul(n, exp);
	return res;
}

int main() {
	string expression;
	cin >> expression;
	cout << countWays(expression.size(), expression);
	return 0;

}

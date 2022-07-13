#include<bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

int nStairs(long long n, vector<long long int> &dp) {
	if (n == 0 || n == 1) return 1;
	dp[1] = 1, dp[2] = 2;
	for (int i = 3; i <= n; i++)dp[i] = ( dp[i - 1] % mod + dp[i - 2] % mod) % mod;
	return dp[n];
}


//main function which holds the answer

int main() {
	int num;
	for (int i = 1; i <= 9; i++ ) {
		cin >> num;
		vector<long long int> dp(num + 1, -1);
		cout << nStairs(num, dp) << " ";
	}
	return 0;
}


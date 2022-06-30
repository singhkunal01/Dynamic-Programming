#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
//first program using dp of fibonacci series to give the nth fibonacci number

int giveNthFibonacci(int n, vector<long long> &dp) {
	if (n <= 1) return n;// base case for the first two numbers which are fixed as 0 and 1.
	if (dp[n] != -1)return dp[n];
	return dp[n] = giveNthFibonacci(n - 1, dp) % mod + giveNthFibonacci(n - 2, dp) % mod;
}

//main function which holds the answer

int main() {
	int num;
	cin >> num;
	vector<long long> dp(num + 1, -1);
	for (int i = 0; i <= num; i++)
		cout << giveNthFibonacci(i, dp) << " ";
	return 0;
}


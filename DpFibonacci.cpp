#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

//program using dp of fibonacci series to give the nth fibonacci number using memoization

int giveNthFibonacciUsingMemoization(int n, vector<long long> &dp) {
	if (n <= 1) return n;// base case for the first two numbers which are fixed as 0 and 1.
	if (dp[n] != -1)return dp[n];
	return dp[n] = giveNthFibonacciUsingMemoization(n - 1, dp) + giveNthFibonacciUsingMemoization(n - 2, dp);
}

//program using tabulation
int giveNthFibonacciUsingTabulation(int n, vector<int> &dp) {
	dp[0] = 0, dp[1] = 1;
	for (int i = 2; i <= n; i++)dp[i] = dp[i - 1] + dp[i - 2];
	return dp[n];
}


//now the complexity of both the codes is (space and time ) O(N) in the below approach we are goiing to reduce the extra space
int giveNthFibonacci(int n) {
	int  first = 0, second = 1, third;
	while (n - 2 >= 0) {
		third = first + second;
		first = second;
		second = third;
		n--;
	}
	return second;
}

//main function which holds the answer

int main() {
	int num;
	cin >> num;
	vector<int> dp(num + 1, -1);
	// cout << giveNthFibonacciUsingMemoization(num, dp) << " ";
	// cout << giveNthFibonacciUsingTabulation(num, dp) << " ";
	cout << giveNthFibonacci(num) << " ";
	return 0;
}


#include <bits/stdc++.h>
using namespace std;

//first program using dp of fibonacci series to give the nth fibonacci number

int giveNthFibonacci(int n) {
	if (n <= 1) return n;// base case for the first two numbers which are fixed as 0 and 1.
	long dp[n + 1] = { -1}; //dp array which holds the overlappings
	if (dp[n] == -1)return dp[n];
	return dp[n] = giveNthFibonacci(n - 1) + giveNthFibonacci(n - 2);
}

//main function which holds the answer

int main() {
	int num;
	cin >> num;
	for (int i = 0; i <= num; i++)
		cout << giveNthFibonacci(i) << " ";
}


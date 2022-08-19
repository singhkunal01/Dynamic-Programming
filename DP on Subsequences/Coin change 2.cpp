#include<bits/stdc++.h>
using namespace std;

int findWays(int ind, int amount, vector<int> &coins, vector<vector<int>> &dp) {
//if we are on the 0th index then if the amount is the multiple of the current denomination then only we can pick it
	if (ind == 0) {
		if (amount % coins[ind] == 0) return 1;
		else return 0;
	}
	/*instead of the upper base case we can also use these two bases cases :

	if(amount == 0) return 0;
	if(ind < 0 || amount < 0) return 1e9;

	*/
	if (dp[ind][amount] != -1)return dp[ind][amount];

	int notTake = findWays(ind - 1, amount, coins, dp);
	int take = 0;
	if (coins[ind] <= amount) take = findWays(ind, amount - coins[ind], coins, dp);
	return dp[ind][amount] = (take + notTake);
}

int findWaysTabul(vector<int> &coins, int amount) {
	int n = coins.size();
	vector<vector<int>> dp(n, vector<int>(amount + 1, 0));
	for (int ind = 0; ind <= amount; ind++)if (ind % coins[0] == 0) dp[0][ind] = 1;
	for (int ind = 1; ind < n; ind++) {
		for (int tempAmount = 0; tempAmount <= amount; tempAmount++) {
			int notTake = dp[ind - 1][tempAmount];
			int take = 0;
			if (coins[ind] <= tempAmount) take = dp[ind][tempAmount - coins[ind]];
			dp[ind][tempAmount] = (take + notTake);
		}
	}
	int ans = dp[n - 1][amount];
	return ans < 1e8 ? ans : -1;
}


// space optimisation approach using 1d Dp
int findWaysSpaceOpt(vector<int> &coins, int amount) {
	int n = coins.size();
	vector<int> prev(amount + 1, 0), curr(amount + 1, 0);
	for (int ind = 0; ind <= amount; ind++)if (ind % coins[0] == 0) prev[ind] = 1;
	for (int ind = 1; ind < n; ind++) {
		for (int tempAmount = 0; tempAmount <= amount; tempAmount++) {
			int notTake = prev[tempAmount];
			int take = 0;
			if (coins[ind] <= tempAmount) take = curr[tempAmount - coins[ind]];
			curr[tempAmount] = (take + notTake);
		}
		prev = curr;
	}
	int ans = prev[amount];
	return ans < 1e9 ? ans : -1;
}


int coinChange(vector<int> &coins, int amount)
{
	// write your code here
	int n = coins.size();
	// vector<vector<int>> dp(n, vector<int>(amount + 1, -1));
	//for memoisation + recursion
	// int ans = findWays(n - 1, amount, coins, dp);
	//for tabulation
	// int ans = findWaysTabul(coins, amount);
	//space optimised
	int ans = findWaysSpaceOpt(coins, amount);
	return ans < 1e9 ? ans : -1;
}

int main() {
	int n;
	cin >> n;
	int amount; cin >> amount;
	vector<int> coins(n);
	for (int &i : coins)cin >> i;
	cout << coinChange(coins, amount);
	return 0;

}
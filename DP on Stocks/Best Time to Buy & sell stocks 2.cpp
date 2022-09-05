#include<bits/stdc++.h>
using namespace std;

//recursive
int findMaxProfit(int i, int n, vector<int> &profit, int buy, int prof) {
//base case
	if (i == n) return 0;
//if ww buy something, 1 is for active buy - means we can buy now  and 0 is for inactive like we cannot buy for the next
	if (buy)
		prof = max(-profit[i] + findMaxProfit(i + 1, n, profit, 0, prof), findMaxProfit(i + 1, n, profit, 1, prof));
	else
		prof = max(profit[i] + findMaxProfit(i + 1, n, profit, 1, prof), findMaxProfit(i + 1, n, profit, 0, prof));
	return prof;
}

// memoization using 2states ind, and buy
int findMaxProfitMemo(int i, int n, vector<int> &profit, int buy, int prof, vector<vector<int>> &dp) {
//base case
	if (i == n) return 0;
//if ww buy something, 1 is for active buy - means we can buy now  and 0 is for inactive like we cannot buy for the next
	if (dp[i][buy] != -1)return dp[i][buy];
	if (buy)
		prof = max(-profit[i] + findMaxProfitMemo(i + 1, n, profit, 0, prof, dp), findMaxProfitMemo(i + 1, n, profit, 1, prof, dp));
	else
		prof = max(profit[i] + findMaxProfitMemo(i + 1, n, profit, 1, prof, dp), findMaxProfitMemo(i + 1, n, profit, 0, prof, dp));

	return dp[i][buy] = prof;
}

/*tabulation using memoization */
int findMaxProfitTabul(vector<int> &profit) {
	int n = profit.size();
	vector<vector<int>> dp(n + 1, vector<int> (2, -1));
	dp[n][0] = dp[n][1] = 0;

//bottom up because in memoization we start from the  0 so here we do invert
	for (int i = n - 1; i >= 0; i--) {
		for (int buy  = 0; buy <= 1; buy++) {
			long long prof = 0;
			if (buy) {
				prof = max(-profit[i] + dp[i + 1][0], dp[i + 1][1]);
			}
			else {
				prof = max(profit[i] + dp[i + 1][1], dp[i + 1][0]);

			}
			dp[i][buy] = prof;
		}
	}
	return dp[0][1];

}


//space optimisation approach using 1d array

int findMaxProfitSpaceOpt(vector<int> &profit) {
	int n = profit.size();
	vector<int> prev (2), curr(2);//prev is the next column because we are moving from last to first
	prev[0] = prev[1] = 0;

//bottom up because in memoization we start from the  0 so here we do invert
	for (int i = n - 1; i >= 0; i--) {
		for (int buy  = 0; buy <= 1; buy++) {
			long long prof = 0;
			if (buy) {
				prof = max(-profit[i] + prev[0], prev[1]);
			}
			else {
				prof = max(profit[i] + prev[1], prev[0]);

			}
			curr[buy] = prof;
		}
		prev = curr;
	}
	return prev[1];

}

//  Use variables instead of these 2 arrays
int findMaxProfitUsingVariables(vector<int> &profit) {
	int n = profit.size();
	long long currNotBuy , currBuy, prevNotBuy , prevBuy;
	prevBuy = prevNotBuy = 0;

//bottom up because in memoization we start from the  0 so here we do inve rt
	for (int i = n - 1; i >= 0; i--) {
		currBuy = max(-profit[i] + prevNotBuy, prevBuy);
		currNotBuy = max(profit[i] + prevBuy, prevNotBuy);
		prevBuy = currBuy;
		prevNotBuy = currNotBuy;
	}
	return prevBuy;

}

int maxProfit(vector<int> &profit) {
	int n = profit.size();
	//for recursion
	// int res =  findMaxProfit(0, n, profit, 1, 0);
	//for memoization
	vector<vector<int>> dp(n, vector<int> (2, -1));
	int res = findMaxProfitMemo(0, n, profit, true, 0, dp);

	//for tabulation
	// int res = findMaxProfitTabul(profit);

	//for space optimisation
	// int res = findMaxProfitSpaceOpt(profit);

	//for most optimal solution - using variables
	// int res = findMaxProfitUsingVariables(profit);

	return res;

}

int main() {
	int n;
	cin >> n;
	vector<int> profit(n);
	for (int &i : profit) cin >> i;
	cout << maxProfit(profit);
	return 0;

}

/*Note :
- We can omit the inner buy loop because whenever the buy is 1 then only that buy function called else the sell
function called so by removing it just place the buy[0] for the buy and buy[1] for the sell.

*/
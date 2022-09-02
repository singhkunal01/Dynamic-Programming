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


int maxProfit(vector<int> &prices) {
	int n = prices.size();
	//for recursion
	// int res =  findMaxProfit(0, n, prices, true, 0);
	//for memoization
	vector<vector<int>> dp(n, vector<int> (2, -1));
	int res = findMaxProfitMemo(0, n, prices, true, 0, dp);

	return res;

}

int main() {
	int n;
	cin >> n;
	vector<int> prices(n);
	for (int &i : prices) cin >> i;
	cout << maxProfit(prices);
	return 0;

}
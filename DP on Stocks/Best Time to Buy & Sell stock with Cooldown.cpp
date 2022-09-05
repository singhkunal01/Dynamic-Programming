/*In this problem if we sell the item then we cannot buy on consecutive day so solution is remain similat to the
Buy and sell stock 2 just replace the i + 1 by i + 2 when we sell something and change the base case from i ==n to i>=n becuase
of two jumps somewhere the index goes beyond the n that's why .................*/

#include<bits/stdc++.h>
using namespace std;

// memoization using 2 states ind, and buy
int findMaxProfitCooldown(int i, int n, vector<int> &profit, int buy, int prof, vector<vector<int>> &dp) {
//base case
	if (i >= n) return 0;
//if ww buy something, 1 is for active buy - means we can buy now  and 0 is for inactive like we cannot buy for the next
	if (dp[i][buy] != -1)return dp[i][buy];
	if (buy)
		prof = max(-profit[i] + findMaxProfitCooldown(i + 1, n, profit, 0, prof, dp), findMaxProfitCooldown(i + 1, n, profit, 1, prof, dp));
	else
		prof = max(profit[i] + findMaxProfitCooldown(i + 2, n, profit, 1, prof, dp), findMaxProfitCooldown(i + 1, n, profit, 0, prof, dp));
	return dp[i][buy] = prof;
}

/*tabulation using memoization */
int findMaxProfitCooldownTabul(vector<int> &profit) {
	int n = profit.size();
	vector<vector<int>> dp(n + 2, vector<int> (2, 0));//2 because sometimes we gonna jump 2 times because of that sometimes we go beyond the n
	dp[n][0] = dp[n][1] = 0;

//bottom up because in memoization we start from the  0 so here we do invert
	for (int i = n - 1; i >= 0; i--) {
		for (int buy  = 0; buy <= 1; buy++) {
			long long prof = 0;
			if (buy) {
				dp[i][buy] = max(-profit[i] + dp[i + 1][0], dp[i + 1][1]);
			}
			else {
				dp[i][buy] = max(profit[i] + dp[i + 2][1], dp[i + 1][0]);

			}
		}
	}
	return dp[0][1];

}


/* space optimisation - We can space optimise it but because as we do i + 2 which means we also need prev of prev because of
that we have to maintain 3 arrays for getting the i + 2 so we don't optimise it .*/

int maxProfit(vector<int> &profit) {
	int n = profit.size();
//for memoization
// vector<vector<int>> dp(n, vector<int> (2, -1));
// int res = findMaxProfitCooldown(0, n, profit, 1, 0, dp);

//for tabulation
	int res = findMaxProfitCooldownTabul(profit);

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
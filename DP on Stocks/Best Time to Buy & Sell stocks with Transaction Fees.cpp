#include<bits/stdc++.h>
using namespace std;

/*This is the tabulation method only we can also use memoization and space optimisation For the same problem */

int findMaxProfitCooldownSpaceOpt(vector<int> &profit, int fees) {
	int n = profit.size();
	vector<vector<int>> dp(n + 1, vector<int> (2, 0));

	for (int i = n - 1; i >= 0; i--) {
		for (int buy  = 0; buy <= 1; buy++) {
			long long prof = 0;
			if (buy) {
				prof = max(-profit[i] + dp[i + 1][0], dp[i + 1][1]);
			}
			else {
				prof = max(profit[i] - fees + dp[i + 1][1], dp[i + 1][0]);
				//so when we sell something after buying which means we have done one transaction
				//so after getting total profit substract the fees from that

			}
			dp[i][buy] = prof;
		}
	}
	return dp[0][1];
}



int maxProfit(vector<int> &profit, int fees) {
	int n = profit.size();
	int res = findMaxProfitCooldownSpaceOpt(profit, fees);
	return res;

}


int main() {
	int n;
	cin >> n;
	vector<int> profit(n);
	for (int &i : profit) cin >> i;
	int fees; cin >> fees;
	cout << maxProfit(profit, fees);
	return 0;

}
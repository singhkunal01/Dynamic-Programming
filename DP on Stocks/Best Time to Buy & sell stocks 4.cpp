#include<bits/stdc++.h>
using namespace std;

/*---------First method using 3D Dp with all three approaches Memoization , tabulation and space optimisation--------- */

// memoization using 3 states ind, buy and total =2
int findMaxProfitIVMemo(int i, int n, vector<int> &profit, int buy, int prof, vector<vector<vector<int>>> &dp, int total) {
//base case
	if (total == 0 or i == n) return 0;
//if ww buy something, 1 is for active buy - means we can buy now  and 0 is for inactive like we cannot buy for the next
	if (dp[i][buy][total] != -1)return dp[i][buy][total];
	if (buy)
		prof = max(-profit[i] + findMaxProfitIVMemo(i + 1, n, profit, 0, prof, dp, total), findMaxProfitIVMemo(i + 1, n, profit, 1, prof, dp, total));
	else
		prof = max(profit[i] + findMaxProfitIVMemo(i + 1, n, profit, 1, prof, dp, total - 1), findMaxProfitIVMemo(i + 1, n, profit, 0, prof, dp, total));
	return dp[i][buy][total] = prof;
}


/*tabulation using memoization */
int findMaxProfitTabulIV(vector<int> &profit, int k) {
	int n = profit.size();
	vector<vector<vector<int>>> dp(n + 1, vector<vector<int>> (2, vector<int> (k + 1, 0)));

//bottom up because in memoization we start from the  0 so here we do invert
	for (int i = n - 1; i >= 0; i--) {
		for (int buy  = 0; buy <= 1; buy++) {
			//according to the base case for every total = 0 return 0
			for (int total = 1; total <= k; total++) {
				long long prof = 0;
				if (buy) {
					prof = max(-profit[i] + dp[i + 1][0][total], dp[i + 1][1][total]);
				}
				else
					prof = max(profit[i] + dp[i + 1][1][total - 1], dp[i + 1][0][total]);
				dp[i][buy][total] = prof;
			}
		}
	}
	return dp[0][1][k];

}


//space optimisation approach using 2d array from the 3d array

int findMaxProfitSpaceOptIV(vector<int> &profit, int k) {
	int n = profit.size();
	vector<vector<int>> prev(2, vector<int> (k + 1, 0)), curr(2, vector<int> (k + 1, 0));

	for (int i = n - 1; i >= 0; i--) {
		for (int buy  = 0; buy <= 1; buy++) {
			//according to the base case for every total = 0 return 0
			for (int total = 1; total <= k; total++) {
				long long prof = 0;
				if (buy) {
					prof = max(-profit[i] + prev[0][total], prev[1][total]);
				}
				else
					prof = max(profit[i] + prev[1][total - 1], prev[0][total]);
				curr[buy][total] = prof;
			}
		}
		prev = curr;
	}
	return prev[1][k];

}

/*-------------Most optimal approach with all three methods - Memoization ,Tabulation and Space optimization-------------*/

int giveMaxProfitIV(int i, int n, vector<int> &profit, int transactions , vector<vector<int>> &dp, int k) {
	if (i == n or transactions == 2 * k) return 0;
	if (dp[i][transactions] != -1) return dp[i][transactions];
	if (transactions % 2 == 0) {//even means we have can buy
		dp[i][transactions] = max(-profit[i] + giveMaxProfitIV(i + 1, n, profit, transactions + 1, dp, k),
		                          giveMaxProfitIV(i + 1, n, profit, transactions, dp, k));

	}
	else {
		dp[i][transactions] = max(profit[i] + giveMaxProfitIV(i + 1, n, profit, transactions + 1, dp, k),
		                          giveMaxProfitIV(i + 1, n, profit, transactions, dp, k));
	}
	return dp[i][transactions];
}

// for tabulation
int giveMaxProfitIVTabul(vector<int> &profit, int transactions) {
	int n = profit.size();
	vector<vector<int>> dp(n + 1, vector<int>(2 * transactions + 1, 0));
	//no need to check for base cases because already the values are 0
	for (int i = n - 1; i >= 0; i--) {
		for (int trans = 0; trans < 2 * transactions; trans++) {
			if (trans % 2 == 0) {//even means we have can buy
				dp[i][trans] = max(-profit[i] + dp[i + 1][trans + 1], dp[i + 1][trans]);
			}
			else {
				dp[i][trans] = max(profit[i] + dp[i + 1][trans + 1], dp[i + 1][trans]);
			}
		}
	}
	return dp[0][0];
}

//space optimisation for above approach
int giveMaxProfitIVSpaceOpt(vector<int> &profit, int transactions) {
	int n = profit.size();
	vector<int> prev (2 * transactions + 1, 0), curr(2 * transactions + 1, 0);
	//no need to check for base cases because already the values are 0
	for (int i = n - 1; i >= 0; i--) {
		for (int trans = 0; trans < 2 * transactions; trans++) {
			if (trans % 2 == 0) {//even means we have can buy
				curr[trans] = max(-profit[i] + prev[trans + 1], prev[trans]);
			}
			else {
				curr[trans] = max(profit[i] + prev[trans + 1], prev[trans]);
			}
		}
		prev = curr;
	}
	return prev[0];
}



int maxProfit(vector<int> &profit, int k) {
	int n = profit.size();

	/*-------------------------------For first method-------------------------------*/

	//for recursion
	// int res =  findMaxProfit(0, n, profit, 1, 0);

	//for memoization
	// vector<vector<vector<int>>> dp(n, vector<vector<int>> (2, vector<int> (k + 1, -1)));

	// int res = findMaxProfitIVMemo(0, n, profit, true, 0, dp, 2);

	//for tabulation
	// int res = findMaxProfitTabulIV(profit);

	//for space optimisation
	// int res = findMaxProfitSpaceOptIV(profit);

	/*-------------------------------For Second method-------------------------------*/
	//for memoization

	//total combinations are 2*k
	// vector<vector<int>> dp(n + 1, vector<int>(2 * k, -1));
	// int res = giveMaxProfitIV(0, n, profit, 0, dp, k);

	//for tabulation
	// int res = giveMaxProfitIVTabul(profit, k);

	//for space optimization
	int res = giveMaxProfitIVSpaceOpt(profit, k);

	return res;

}

int main() {
	int n;
	cin >> n;
	vector<int> profit(n);
	for (int &i : profit) cin >> i;
	int k; cin >> k;
	cout << maxProfit(profit, k);
	return 0;

}
#include<bits/stdc++.h>
using namespace std;

/*---------First method using 3D Dp with all three approaches Memoization , tabulation and space optimisation--------- */

// memoization using 3 states ind, buy and total =2
int findMaxProfitIIIMemo(int i, int n, vector<int> &profit, int buy, int prof, vector<vector<vector<int>>> &dp, int total) {
//base case
	if (total == 0 or i == n) return 0;
//if ww buy something, 1 is for active buy - means we can buy now  and 0 is for inactive like we cannot buy for the next
	if (dp[i][buy][total] != -1)return dp[i][buy][total];
	if (buy)
		prof = max(-profit[i] + findMaxProfitIIIMemo(i + 1, n, profit, 0, prof, dp, total), findMaxProfitIIIMemo(i + 1, n, profit, 1, prof, dp, total));
	else
		prof = max(profit[i] + findMaxProfitIIIMemo(i + 1, n, profit, 1, prof, dp, total - 1), findMaxProfitIIIMemo(i + 1, n, profit, 0, prof, dp, total));
	return dp[i][buy][total] = prof;
}


/*tabulation using memoization */
int findMaxProfitTabulIII(vector<int> &profit) {
	int n = profit.size();
	vector<vector<vector<int>>> dp(n + 1, vector<vector<int>> (2, vector<int> (3, 0)));

//bottom up because in memoization we start from the  0 so here we do invert
	for (int i = n - 1; i >= 0; i--) {
		for (int buy  = 0; buy <= 1; buy++) {
			//according to the base case for every total = 0 return 0
			for (int total = 1; total <= 2; total++) {
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
	return dp[0][1][2];

}


//space optimisation approach using 2d array from the 3d array

int findMaxProfitSpaceOptIII(vector<int> &profit) {
	int n = profit.size();
	vector<vector<int>> prev(2, vector<int> (3, 0)), curr(2, vector<int> (3, 0));

	for (int i = n - 1; i >= 0; i--) {
		for (int buy  = 0; buy <= 1; buy++) {
			//according to the base case for every total = 0 return 0
			for (int total = 1; total <= 2; total++) {
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
	return prev[1][2];

}


/*-------------Most optimal approach with all three methods - Memoization ,Tabulation and Space optimization-------------*/

int giveMaxProfit(int i, int n, vector<int> &profit, int transactions , vector<vector<int>> &dp) {
	if (i == n or transactions == 4) return 0;
	if (dp[i][transactions] != -1) return dp[i][transactions];
	if (transactions % 2 == 0) {//even means we have can buy
		dp[i][transactions] = max(-profit[i] + giveMaxProfit(i + 1, n, profit, transactions + 1, dp),
		                          giveMaxProfit(i + 1, n, profit, transactions, dp));

	}
	else {
		dp[i][transactions] = max(profit[i] + giveMaxProfit(i + 1, n, profit, transactions + 1, dp),
		                          giveMaxProfit(i + 1, n, profit, transactions, dp));
	}
	return dp[i][transactions];
}


int maxProfit(vector<int> &profit) {
	int n = profit.size();

	/*-------------------------------For first method-------------------------------*/

	//for recursion
	// int res =  findMaxProfit(0, n, profit, 1, 0);

	//for memoization
	// vector<vector<vector<int>>> dp(n, vector<vector<int>> (2, vector<int> (3, -1)));

	// int res = findMaxProfitIIIMemo(0, n, profit, true, 0, dp, 2);

	//for tabulation
	// int res = findMaxProfitTabulIII(profit);

	//for space optimisation
	// int res = findMaxProfitSpaceOptIII(profit);


	/*-------------------------------For Second method-------------------------------*/
	//for recursion
	vector<vector<int>> dp(n + 1, vector<int>(4, -1));
	/*Why 4 ? Since we have to buy at max 2 times which means we have 2 choices for each
	1 - B/S , 2 - B/S , total  = 4

	Now for more clarity,the perfect sequence for the transaction is: B S B S
	Because, neither we buy two adjacents nor we can sale and also we have to buy first thats'why
	So , if we observer then B's are on even index and S's are on odd so which means when transaction
	is even we have to buy them otherwise sell it.
	Thats It.

	*/
	//for memoization
	int res = giveMaxProfit(0, n, profit, 0, dp);

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
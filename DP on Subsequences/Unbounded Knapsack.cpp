#include<bits/stdc++.h>
using namespace std;

/* Recursive + Memoisation code

Recursive- TC -  >O(2^N) , SC - >O(N) , because there can be the more than 2 choices for each index if anywhere required
Memoisation - TC - O(N*maxWeight) , SC - O(N*maxWeight)+O(N)
*/
int giveMaxWeightMemo(int currHouse, vector<int> &weight, vector<int> &profit, int maxWeight, vector<vector<int>>&dp) {
	if (currHouse == 0) return (maxWeight / weight[0]) * profit[0];
	/* -> if we reach the first index then if target if not 0 then according to the profit at first index we take the
	maxWeight/weight[0] for each we get the profit[0] so multiply it number of times
	*/
	if (dp[currHouse][maxWeight] != -1) return dp[currHouse][maxWeight];
	int notPick = giveMaxWeightMemo(currHouse - 1, weight, profit, maxWeight, dp);
	int pick = -1e9;
	if (weight[currHouse] <= maxWeight)
		pick = profit[currHouse] + giveMaxWeightMemo(currHouse, weight, profit, maxWeight - weight[currHouse], dp);
	return dp[currHouse][maxWeight] = max(pick, notPick);
}

/*Tabulation approach*/
int giveMaxWeightTabu(vector<int> &weight, vector<int> &profit, int n, int &maxWeight) {
	// Write your code here
	vector<vector<int>> dp(n, vector<int>(maxWeight + 1));
	for (int fromWeight = 0; fromWeight <= maxWeight; fromWeight++)dp[0][fromWeight] = (fromWeight / weight[0]) * profit[0];
	for (int currHouse = 1; currHouse < n; currHouse++) {
		for (int fromWeight = 0; fromWeight <= maxWeight; fromWeight++) {
			int notPick = dp[currHouse - 1][fromWeight];
			int pick = -1e9;
			if (weight[currHouse] <= fromWeight)
				pick = profit[currHouse] + dp[currHouse][fromWeight - weight[currHouse]];
			dp[currHouse][fromWeight] = max(pick, notPick);
		}
	}
	return dp[n - 1][maxWeight];
}


int giveMaxWeightSpaceOpt(vector<int> &weight, vector<int> &profit, int n, int &maxWeight) {
	// Write your code here
	vector<int> prev(maxWeight + 1), curr(maxWeight + 1);
	for (int fromWeight = 0; fromWeight <= maxWeight; fromWeight++)prev[fromWeight] = (fromWeight / weight[0]) * profit[0];
	for (int currHouse = 1; currHouse < n; currHouse++) {
		for (int fromWeight = 0; fromWeight <= maxWeight; fromWeight++) {
			int notPick = prev[fromWeight];
			int pick = -1e9;
			if (weight[currHouse] <= fromWeight)
				pick = profit[currHouse] + curr[fromWeight - weight[currHouse]];
			curr[fromWeight] = max(pick, notPick);
		}
		prev = curr;
	}
	return prev[maxWeight];
}

/*...................Most optimal approach using single array optimisation...................*/
int mostOptimalResultant(vector<int> &weight, vector<int> &profit, int n, int &maxWeight) {
	// Write your code here
	vector<int> prev(maxWeight + 1);
	for (int fromWeight = 0; fromWeight <= maxWeight; fromWeight++)prev[fromWeight] = (fromWeight / weight[0]) * profit[0];
	for (int currHouse = 1; currHouse < n; currHouse++) {
		for (int fromWeight = 0; fromWeight <= maxWeight; fromWeight++) {
			int notPick = prev[fromWeight];
			int pick = -1e9;
			if (weight[currHouse] <= fromWeight)
				pick = profit[currHouse] + prev[fromWeight - weight[currHouse]];
			prev[fromWeight] = max(pick, notPick);
		}
	}
	return prev[maxWeight];
}



//main knapsack function
int knapsack(vector<int> &weight, vector<int> &profit, int n, int &maxWeight) {
	// Write your code here
	// vector<vector<int>> dp(n, vector<int>(maxWeight + 1, -1));
	//memoisation
	// int maxCost = giveMaxWeightMemo(n - 1, weight, profit, maxWeight, dp);
	//tabulation
	// int maxCost = giveMaxWeightTabu(weight, profit, n, maxWeight);
	//space optimisation
	// int maxCost = giveMaxWeightSpaceOpt(weight, profit, n, maxWeight);
	//most optimal result
	int maxCost = mostOptimalResultant(weight, profit, n, maxWeight);
	return maxCost;
}



int main() {
	int n; cin >> n;
	int maxWeight; cin >> maxWeight;
	vector<int>weight(n), profit(n);
	for (int &i : profit)cin >> i;
	for (int &i : weight)cin >> i;
	cout << "Max profit : " << knapsack(weight, profit, n, maxWeight) << endl;
	return 0;

}
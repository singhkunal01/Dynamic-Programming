#include<bits/stdc++.h>
using namespace std;

/* Recursive + Memoisation code

Recursive- TC - O(2^N) , SC -O(N)
Memoisation - TC - O(N*maxWeight) , SC - O(N*maxWeight)+O(N)
*/
int giveMaxWeightMemo(int currHouse, vector<int> &weight, vector<int> &value, int maxWeight, vector<vector<int>>&dp) {
	if (currHouse == 0) return  (weight[0] <= maxWeight) ? value[0] : 0;
	if (dp[currHouse][maxWeight] != -1) return dp[currHouse][maxWeight];
	int notPick = giveMaxWeightMemo(currHouse - 1, weight, value, maxWeight, dp);
	int pick = INT_MIN;
	if (weight[currHouse] <= maxWeight)
		pick = value[currHouse] + giveMaxWeightMemo(currHouse - 1, weight, value, maxWeight - weight[currHouse], dp);
	return dp[currHouse][maxWeight] = max(pick, notPick);
}

/*Tabulation approach*/
int giveMaxWeightTabu(vector<int> &weight, vector<int> &value, int n, int &maxWeight) {
	// Write your code here
	vector<vector<int>> dp(n, vector<int>(maxWeight + 1));
	for (int currHouse = weight[0]; currHouse <= maxWeight; currHouse++)dp[0][currHouse] = value[0];
	for (int currHouse = 1; currHouse < n; currHouse++) {
		for (int fromWeight = 0; fromWeight <= maxWeight; fromWeight++) {
			int notPick = dp[currHouse - 1][fromWeight];
			int pick = INT_MIN;
			if (weight[currHouse] <= fromWeight)
				pick = value[currHouse] + dp[currHouse - 1][fromWeight - weight[currHouse]];
			dp[currHouse][fromWeight] = max(pick, notPick);
		}
	}
	return dp[n - 1][maxWeight];
}


int giveMaxWeightSpaceOpt(vector<int> &weight, vector<int> &value, int n, int &maxWeight) {
	// Write your code here
	vector<int> prev(maxWeight + 1), curr(maxWeight + 1);
	for (int currHouse = weight[0]; currHouse <= maxWeight; currHouse++)prev[currHouse] = value[0];
	for (int currHouse = 1; currHouse < n; currHouse++) {
		for (int fromWeight = 0; fromWeight <= maxWeight; fromWeight++) {
			int notPick = prev[fromWeight];
			int pick = INT_MIN;
			if (weight[currHouse] <= fromWeight)
				pick = value[currHouse] + prev[fromWeight - weight[currHouse]];
			curr[fromWeight] = max(pick, notPick);
		}
		prev = curr;
	}
	return prev[maxWeight];
}


//main knapsack function
int knapsack(vector<int> &weight, vector<int> &value, int n, int &maxWeight) {
	// Write your code here
	// vector<vector<int>> dp(n, vector<int>(maxWeight + 1, -1));
	//memoisation
	// int maxCost = giveMaxWeightMemo(n - 1, weight, value, maxWeight, dp);
	//tabulation
	// int maxCost = giveMaxWeightTabu(weight, value, n, maxWeight);
	//space optimisation
	int maxCost = giveMaxWeightSpaceOpt(weight, value, n, maxWeight);
	return maxCost;
}



int main() {
	int n; cin >> n;
	vector<int>weight(n), value(n);
	for (int &i : weight)cin >> i;
	for (int &i : value)cin >> i;
	int maxWeight; cin >> maxWeight;
	cout << "Max Value : " << knapsack(weight, value, n, maxWeight) << endl;
	return 0;

}
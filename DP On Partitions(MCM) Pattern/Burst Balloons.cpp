#include<bits/stdc++.h>
using namespace std;

/*memoization approach */

int findMaxCoins(int i, int j, vector<int>&balloons, vector<vector<int>> &dp) {
	if (i > j) return 0;
	if (dp[i][j] != -1) return dp[i][j];
	int maxCoins = 0;
	for (int ind = i; ind <= j; ind++) {
		int cost = balloons[i - 1] * balloons[ind] * balloons[j + 1]
		           + findMaxCoins(i, ind - 1, balloons, dp)
		           + findMaxCoins(ind + 1, j, balloons, dp);
		maxCoins = max(cost, maxCoins);
	}
	return dp[i][j] = maxCoins;
}


/*Tabulation approach */
int findMaxCoinsTabul(vector<int>& balloons) {
	//it don't works if we start bursting because the cost depends on the other partitions as well so think in reverse like instead of finding the balloon which burst first think in the way which bursts at last because the last one do not depends on any one (1,1)
	int n = balloons.size();
	balloons.insert(balloons.begin(), 1);
	balloons.push_back(1);
	vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));
	for (int i = n; i > 0; i--) {
		for (int j = 1; j <= n; j++) {
			int maxCoins = 0;
			if (i > j) continue;
			for (int ind = i; ind <= j; ind++) {
				int cost = balloons[i - 1] * balloons[ind] * balloons[j + 1] + dp[i][ind - 1] + dp[ind + 1][j];
				maxCoins = max(maxCoins, cost);
			}
			dp[i][j] = maxCoins;
		}
	}
	return dp[1][n];
}

int maxCoins(vector<int>& balloons) {
	//it don't works if we start bursting because the cost depends on the other partitions as well so think in reverse like instead of finding the balloon which burst first think in the way which bursts at last because the last one do not depends on any one (1,1)
	int n = balloons.size();
	balloons.insert(balloons.begin(), 1);
	balloons.push_back(1);


	//for memoization approach
	// vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));
	// int res = findMaxCoins(1, n, balloons, dp);
	// for tabulation approach
	int res = findMaxCoinsTabul(balloons);
	return res;
}

int main() {
	int numberOfBalloons;
	cin >> numberOfBalloons;
	vector<int> balloons(numberOfBalloons);
	for (int &i : balloons) cin >> i;
	cout << maxCoins(balloons);
	return 0;

}

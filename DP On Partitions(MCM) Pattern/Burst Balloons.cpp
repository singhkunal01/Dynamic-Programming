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

int maxCoins(vector<int>& balloons) {
	//it don't works if we start bursting because the cost depends on the other partitions as well so think in reverse like instead of finding the balloon which burst first think in the way which bursts at last because the last one do not depends on any one (1,1)
	int n = balloons.size();
	balloons.insert(balloons.begin(), 1);
	balloons.push_back(1);
	vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));
	int res = findMaxCoins(1, n, balloons, dp);
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
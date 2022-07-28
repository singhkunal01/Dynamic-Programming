#include<bits/stdc++.h>
using namespace std;

//recursive code for the problem -Ninjas Training

int helperToFind(int idx, vector<vector<int>> &points, int lastDay) {
//base case
	if (idx == 0) {
		int maxi = 0 ;
		for (int i = 0; i < 3; i++)if (i != lastDay)maxi =  max(maxi, points[0][i]);
		return maxi;
	}
	int maxi = 0;
	for (int i = 0; i < 3; i++) {
		if (i != lastDay) {
			int activity = points[idx][i] + helperToFind(idx - 1 , points, i);
			maxi = max(maxi, activity);
		}
	}
	return maxi;
}


//memoisation code
int helperToFindMemo(int idx, vector<vector<int>> &points, int lastDay, vector<vector<int>> &dp) {
//base case
	if (dp[idx][lastDay] != -1) return dp[idx][lastDay];
	if (idx == 0) {
		int maxi = 0 ;
		for (int i = 0; i < 3; i++)if (i != lastDay)maxi =  max(maxi, points[0][i]);
		return dp[idx][lastDay] = maxi;
	}
	int maxi = 0;
	for (int i = 0; i < 3; i++) {
		if (i != lastDay) {
			int activity = points[idx][i] + helperToFindMemo(idx - 1 , points, i, dp);
			maxi = max(maxi, activity);
		}
	}
	return dp[idx][lastDay] = maxi;
}


int ninjaTraining(int n, vector<vector<int>> &points)
{
	int ans =  helperToFind(n - 1, points, 3);
	vector<vector<int>>dp(n, vector<int> (4, -1));
	ans = helperToFindMemo(n - 1, points, 3, dp);
	return ans;
}

int main() {
	int n;
	cin >> n;
	vector<vector<int>>points(n, vector<int>(3));
	for (int i = 0; i < n; i++)for (int j = 0; j < 3; j++) cin >> points[i][j];
	cout << ninjaTraining(n, points) << "\n";
	return 0;

}
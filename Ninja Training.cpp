#include<bits/stdc++.h>
using namespace std;

//recursive code for the problem -Ninjas Training
int helperToFind(int day, vector<vector<int>> &points, int lastDay) {
//base case
	if (day == 0) {
		int maxi = 0 ;
		for (int i = 0; i < 3; i++)if (i != lastDay)maxi =  max(maxi, points[0][i]);
		return maxi;
	}
	int maxi = 0;
	for (int i = 0; i < 3; i++) {
		if (i != lastDay) {
			int activity = points[day][i] + helperToFind(day - 1 , points, i);
			maxi = max(maxi, activity);
		}
	}
	return maxi;
}


//memoisation code
int helperToFindMemo(int day, vector<vector<int>> &points, int lastDay, vector<vector<int>> &dp) {
//base case
	if (dp[day][lastDay] != -1) return dp[day][lastDay];
	if (day == 0) {
		int maxi = 0 ;
		for (int i = 0; i < 3; i++)if (i != lastDay)maxi =  max(maxi, points[0][i]);
		return dp[day][lastDay] = maxi;
	}
	int maxi = 0;
	for (int task = 0; task < 3; task++) {
		if (task != lastDay) {
			int pointAcheive = points[day][task] + helperToFindMemo(day - 1 , points, task, dp);//here this i becomes the last task that was done
			maxi = max(maxi, pointAcheive);
		}
	}
	return dp[day][lastDay] = maxi;
}



int helperToFindTabulation(int n, vector<vector<int>> &points) {
	vector<vector<int>>dp(n, vector<int> (4, 0));//dp[day][last]
	//whatever the base cases fix them in the dp array
	dp[0][0] = max(points[0][1], points[0][2]);
	dp[0][1] = max(points[0][0], points[0][2]);
	dp[0][2] = max(points[0][0], points[0][1]);
	dp[0][3] = max({points[0][0], points[0][1], points[0][2]});

//now if we fix the base case then in total there will be loop from 1- n-1
	for (int day = 1; day < n; day++) {
//for the 4 possible cases i.e., last day task
		for (int last = 0; last < 4; last++) {
			dp[day][last] = 0;
//for the 3 tasks out of which we have to choose
			for (int task = 0; task < 3; task++) {
				if (task != last) {
					int pointAcheive = points[day][task] + dp[day - 1][task];
					dp[day][last] = max(dp[day][last], pointAcheive);
				}
			}
		}
	}
	return dp[n - 1][3];
}


//space optimisation
int mostOptimalResult(int n, vector<vector<int>> &points) {
	vector<int > prev(4); //dp[day][last]
	//whatever the base cases fix them in the dp array
	prev[0] = max(points[0][1], points[0][2]);
	prev[1] = max(points[0][0], points[0][2]);
	prev[2] = max(points[0][0], points[0][1]);
	prev[3] = max({points[0][0], points[0][1], points[0][2]});

//now if we fix the base case then in total there will be loop from 1- n-1
	for (int day = 1; day < n; day++) {
//for the 4 possible cases i.e., last day task
		vector<int> temp(4);
		for (int last = 0; last < 4; last++) {
			temp[last] = 0;
//for the 3 tasks out of which we have to choose
			for (int task = 0; task < 3; task++) {
				if (task != last) {
					int pointAcheive = points[day][task] + prev[task];
					temp[last] = max(temp[last], pointAcheive);
				}
			}
		}
		prev = temp;//placing
	}
	return prev[3];
}



int ninjaTraining(int n, vector<vector<int>> &points)
{
	// int ans =  helperToFind(n - 1, points, 3);//for recursion
	vector<vector<int>>dp(n, vector<int> (4, -1));
	// int ans = helperToFindMemo(n - 1, points, 3, dp);//for memoisation
	// int ans = helperToFindTabulation(n, points);
	int ans = mostOptimalResult(n, points);
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
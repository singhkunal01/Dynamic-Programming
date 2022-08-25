#include<bits/stdc++.h>
using namespace std;


/*Recursive + Memoization code */

int countDistinctNumberWays(int i, int j, string &mainStr, string &target, vector<vector<int>> &dp) {
//base cases
	//if we reached at the index below 0 for the target which means we have check full string i.e.,so
	if (j < 0) return 1;
	/*for shifting replace above line with j==0*/

	//if we reached at the index below 0 for the mainStr which means we haven't check full string i.e.,target so
	if (i < 0) return 0;
	/*for shifting replace above line with i==0*/

	if (dp[i][j] != -1) return dp[i][j];

	//now if the both characters are same then

	if (mainStr[i] == target[j]) {
		/*for shifting replace above line with mainStr[i-1] == target[j-1]*/

		/*there would be two cases if we want to add that character in our resultant sequence then or
		we want the same character at any different place (index) then -*/
		return dp[i][j] = countDistinctNumberWays(i - 1, j - 1, mainStr, target, dp) +
		                  countDistinctNumberWays(i - 1, j, mainStr, target, dp);/*this second one is for checking diff. index
		       for the same characeer .*/

	}
//if both the characters donot matched then stay on the same jth index and check the character in the mainStr
	return dp[i][j] = countDistinctNumberWays(i - 1, j, mainStr, target, dp);

}


/*Tabulation approach for the same */
int countDistinctNumberWaysTabul(string &mainStr, string &target) {
	int  n = mainStr.size(), m = target.size();
	vector<vector<unsigned int>> dp(n + 1, vector<unsigned int>(m + 1));

//because of < 0 of bases because of it we can't represent negatives in array so as like LCS we gonna shift
	for (int i = 0; i <= n; i++)dp[i][0] = 1;//for the first test case
	// for (int j = 1; j <= m; j++)dp[0][j] = 0; //we can ommit this because by default the values are 0 filled

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (mainStr[i - 1] == target[j - 1]) {
				dp[i][j] = dp[i - 1][ j - 1] + dp[i - 1][j];
			}
			else dp[i][j] = dp[i - 1][j];
		}
	}
	return (int)dp[n][m];
	/*for larger cases make sure to remove int and place double or unsigned int */
}

/*space optimisatio approach for the same - 2 ARRAYS*/
int countDistinctNumberWaysSpaceOptimised(string &mainStr, string &target) {
	int  n = mainStr.size(), m = target.size();
	vector<unsigned int> prev(m + 1), curr(m + 1);
	prev[0] = curr[0] = 1;//for the first test case
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (mainStr[i - 1] == target[j - 1]) {
				curr[j] = prev[j - 1] + prev[j];
			}
			else curr[j] = prev[j];
		}
		prev = curr;
	}
	return (int)prev[m];
}
/*space optimisatio approach for the same - 1 ARRAY*/
int countDistinctNumberWaysSpaceOptimised_SingleArray(string &mainStr, string &target) {
	int  n = mainStr.size(), m = target.size();
	vector<unsigned int> prev(m + 1);
	prev[0] = 1; //for the first test case
	for (int i = 1; i <= n; i++) {
		for (int j = m; j > 0; j--) {
			if (mainStr[i - 1] == target[j - 1]) {
				prev[j] = prev[j - 1] + prev[j];
			}
			else prev[j] = prev[j];
		}
	}
	return (int)prev[m];
}


int numDistinct(string &mainStr, string &target) {
	int  n = mainStr.size(), m = target.size();

	//for memoization
	// vector<vector<int>> dp(n, vector<int> (m, -1));
	/*for shifting replace above line with vector<vector<int>> dp(n+1, vector<int> (m+1, -1))*/
	// int totalWays = countDistinctNumberWays(n - 1, m - 1, mainStr, target, dp);


	// for tabulation
	// int totalWays = countDistinctNumberWaysTabul(mainStr, target);

	//for space optimised approach
	// int totalWays = countDistinctNumberWaysSpaceOptimised(mainStr, target);

	//for single array space optimisation
	int totalWays = countDistinctNumberWaysSpaceOptimised_SingleArray(mainStr, target);

	return totalWays;
}

int main() {
	string mainStr, target;
	cin >> mainStr >> target;
	cout << numDistinct(mainStr, target);
	return 0;

}
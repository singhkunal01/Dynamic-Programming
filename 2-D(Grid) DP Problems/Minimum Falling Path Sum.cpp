#include<bits/stdc++.h>
using namespace std;

#define INF 1e9




/*Recursive Approach */
int findMinimumPathFallingSum(vector<vector<int>> &mat, int ind, int exploreCols) {
//base case if the row is first then accordingly find the minimum
	if (exploreCols < 0 or exploreCols >= mat.size()) return INF;
	if (ind == 0) return mat[0][exploreCols];
//another base case if our index is move out of bound
	int upward = mat[ind][exploreCols] + findMinimumPathFallingSum(mat, ind - 1, exploreCols);
	int leftDiagonal = mat[ind][exploreCols] + findMinimumPathFallingSum(mat, ind - 1, exploreCols - 1);
	int rightDiagonal = mat[ind][exploreCols] + findMinimumPathFallingSum(mat, ind - 1, exploreCols + 1);
	return  min({leftDiagonal, upward, rightDiagonal});
}




/*Memoisation Approach */
int findMinimumPathFallingSumUsingMemo(vector<vector<int>> &mat, int ind, int exploreCols, vector<vector<int>> &memo) {
//base case if the row is first then accordingly find the minimum
	if (exploreCols < 0 or exploreCols >= mat.size()) return INF;
	if (ind == 0) return mat[0][exploreCols];
	if (memo[ind][exploreCols] != -1) return memo[ind][exploreCols];
//another base case if our index is move out of bound
	int upward = mat[ind][exploreCols] + findMinimumPathFallingSumUsingMemo(mat, ind - 1, exploreCols, memo);
	int leftDiagonal = mat[ind][exploreCols] + findMinimumPathFallingSumUsingMemo(mat, ind - 1, exploreCols - 1, memo);
	int rightDiagonal = mat[ind][exploreCols] + findMinimumPathFallingSumUsingMemo(mat, ind - 1, exploreCols + 1, memo);
	return  memo[ind][exploreCols] = min({leftDiagonal, upward, rightDiagonal});
}



int minFallingPathSum(vector<vector<int>>& matrix) {

// In this i start from the last row and move towards the first row
	int n = matrix.size();
	int minSum = INT_MAX;
	vector<vector<int>> memo(n, vector<int>(n, -1));
	for (int col = n - 1; col >= 0; col--) {
		// minSum = min(minSum, findMinimumPathFallingSum(matrix, n - 1, col));
		minSum = min(minSum, findMinimumPathFallingSumUsingMemo(matrix, n - 1, col, memo));
	}
	return minSum;
}




int main() {
//given the square matrix
	int n;
	cin >> n;
	vector<vector<int>> grid(n, vector<int> (n));
	for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> grid[i][j];
	cout << minFallingPathSum(grid) << endl;
	return 0;

}
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

/*Tabulation Approach*/
int findMinimumPathFallingSumUsingTabu(vector<vector<int>> &mat) {
	int n = mat.size();
	vector<vector<int>> memo(n, vector<int>(n, -1));
//base case , like for the first row the values are remain as same as in mat for the memo
	for (int col = 0; col < n; col++) memo[0][col] = mat[0][col];
// now for the n -1  rows and n cols
	for (int row = 1; row < n; row++) {
		for (int col = 0; col < n; col++) {

			int upward = mat[row][col] + memo[row - 1][col];

			int leftDiagonal = mat[row][col] ;
			if (col - 1 >= 0)leftDiagonal += memo[row - 1][col - 1];
			else leftDiagonal += (INF);

			int rightDiagonal = mat[row][col] ;
			if (col + 1 < n)rightDiagonal += memo[row - 1][col + 1];
			else rightDiagonal += (INF);

			memo[row][col] = min({leftDiagonal, upward, rightDiagonal});
		}
	}

	//now in the end we have the maximum sum at every cell in the last row so now we want  maximum among all of them for that
	int mini = *min_element(memo[n - 1].begin(), memo[n - 1].end());
	return mini;
}

/*Most optimal approach SPACE OPTIMISATION */
int mostOptimalMaxFallingPathSum(vector<vector<int>> &mat) {
	int n = mat.size();
	vector<int> prev(n);
//base case , like for the first row the values are remain as same as in mat for the memo
	for (int col = 0; col < n; col++) prev[col] = mat[0][col];
// now for the n -1  rows and n cols
	for (int row = 1; row < n; row++) {
		vector<int> curr(n);
		for (int col = 0; col < n; col++) {
			int upward = mat[row][col] + prev[col];

			int leftDiagonal = mat[row][col] ;
			if (col - 1 >= 0)leftDiagonal += prev[col - 1];
			else leftDiagonal += (INF);

			int rightDiagonal = mat[row][col] ;
			if (col + 1 < n)rightDiagonal += prev[col + 1];
			else rightDiagonal += (INF);

			curr[col] = min({leftDiagonal, upward, rightDiagonal});
		}
		prev = curr;
	}

	//now in the end we have the maximum sum at every cell in the last row so now we want  maximum among all of them for that
	int mini = *min_element(prev.begin(), prev.end());
	return mini;
}


int minFallingPathSum(vector<vector<int>>& matrix) {

// In this i start from the last row and move towards the first row
	int n = matrix.size();
	int minSum = INT_MAX;
	vector<vector<int>> memo(n, vector<int>(n, -1));
	//also we can start from 0 to n-1

	/*	for (int col = n - 1; col >= 0; col--) {
		//for recursive
			// minSum = min(minSum, findMinimumPathFallingSum(matrix, n - 1, col));

			//for memoisation
			// minSum = min(minSum, findMinimumPathFallingSumUsingMemo(matrix, n - 1, col, memo));
		}*/

	// for tabulation
	// minSum = min(minSum, findMinimumPathFallingSumUsingTabu(matrix));

	//for space optimisation
	minSum = min(minSum, mostOptimalMaxFallingPathSum(matrix));
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
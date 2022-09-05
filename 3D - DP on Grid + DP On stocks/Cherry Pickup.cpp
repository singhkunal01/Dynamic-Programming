#include<bits/stdc++.h>
using namespace std;

//recursive approach

int findMaximumChocolates(int currRow, int currColAlice, int currColBob, vector<vector<int>> &grid, int row, int col) {
//base case for the  out of boundaries, if both of these guys are moves out of boundaries then return the minimum possible value
	if (currColAlice<0 or currColAlice >= col or currColBob<0 or currColBob >= col) return -1e9;
	//base case for the destination
	if (currRow == row - 1) {
		//means they both reached the destination
		// if both are at same cell then count that cell at once
		if (currColAlice == currColBob) return grid[currRow][currColAlice];
		//else both the cells are counted as different
		else return grid[currRow][currColAlice] + grid[currRow][currColBob];
	}
	int maxPossibleChocolates = INT_MIN;
	//for every curr move of alice , bob has 3 possible moves so in total 3 * 3 moves = 9 moves
	for (int aliceMoves = -1 ; aliceMoves <= 1; aliceMoves++) {
		for (int bobMoves = -1 ; bobMoves <= 1; bobMoves++) {
//if in somewhere between they both are at the same cell then add it once only
			if (currColAlice == currColBob)
				maxPossibleChocolates = max(maxPossibleChocolates, grid[currRow][currColAlice] + findMaximumChocolates(currRow + 1, currColAlice + aliceMoves, currColBob + bobMoves, grid, row, col));
			else//add it separately for both , bob and alice
				maxPossibleChocolates = max(maxPossibleChocolates, grid[currRow][currColAlice] + grid[currRow][currColBob] + findMaximumChocolates(currRow + 1, currColAlice + aliceMoves, currColBob + bobMoves, grid, row, col));
		}
	}
	return maxPossibleChocolates;
}

//Memoisation approach

int findMaximumChocolatesMemo(int currRow, int currColAlice, int currColBob, vector<vector<int>> &grid, int row, int col, vector<vector<vector<int>>> &memo) {
//base case for the  out of boundaries, if both of these guys are moves out of boundaries then return the minimum possible value
	if (currColAlice<0 or currColAlice >= col or currColBob<0 or currColBob >= col) return -1e9;
	//memoisation code
	if (memo[currRow][currColAlice][currColBob] != -1) return memo[currRow][currColAlice][currColBob];
	//base case for the destination
	if (currRow == row - 1) {
		//means they both reached the destination
		// if both are at same cell then count that cell at once
		if (currColAlice == currColBob) return grid[currRow][currColAlice];
		//else both the cells are counted as different
		else return grid[currRow][currColAlice] + grid[currRow][currColBob];
	}
	int maxPossibleChocolates = INT_MIN;
	//for every curr move of alice , bob has 3 possible moves so in total 3 * 3 moves = 9 moves
	for (int aliceMoves = -1 ; aliceMoves <= 1; aliceMoves++) {
		for (int bobMoves = -1 ; bobMoves <= 1; bobMoves++) {
//if in somewhere between they both are at the same cell then add it once only
			if (currColAlice == currColBob)
				maxPossibleChocolates = max(maxPossibleChocolates, grid[currRow][currColAlice] + findMaximumChocolatesMemo(currRow + 1, currColAlice + aliceMoves, currColBob + bobMoves, grid, row, col, memo));
			else//add it separately for both , bob and alice
				maxPossibleChocolates = max(maxPossibleChocolates, grid[currRow][currColAlice] + grid[currRow][currColBob] + findMaximumChocolatesMemo(currRow + 1, currColAlice + aliceMoves, currColBob + bobMoves, grid, row, col, memo));
		}
	}
	return memo[currRow][currColAlice][currColBob] = maxPossibleChocolates;
}


/*Tabulation approach */
int findMaximumChocolatesTabu(int r, int c , vector<vector<int>> &grid) {
	//base case
	vector<vector<vector<int>>> memo(r, vector<vector<int>>(c, vector<int>(c, -1)));
	for (int alice = 0 ; alice < c; alice++) {
		for (int bob = 0; bob < c; bob++) {
			//if both are at the same cell in the end then
			if (alice == bob)memo[r - 1][alice][bob] = grid[r - 1][bob];
			else memo[r - 1][alice][bob] = grid[r - 1][alice] + grid[r - 1][bob];
		}
	}

	//now we set the values for the last row so for the rest of rows (n-2 to 0)
	for (int currRow = r - 2; currRow >= 0 ; currRow--) {
		for (int aliceCell = 0; aliceCell < c; aliceCell++) {
			for (int bobCell = 0; bobCell < c; bobCell++) {
				int maxPossibleChocolates = INT_MIN;
				//for 9 possibilities
				for (int aliceMoves = -1; aliceMoves <= 1; aliceMoves++) {
					for (int bobMoves = -1; bobMoves <= 1; bobMoves++) {
						int tempValue = 0;
						if (aliceCell == bobCell)tempValue = grid[currRow][aliceCell];
						else tempValue = grid[currRow][aliceCell] + grid[currRow][bobCell];
						//check for the overflow cases
						if (aliceMoves + aliceCell >= 0 and aliceCell + aliceMoves < c and bobCell + bobMoves >= 0 and bobCell + bobMoves < c) {
							tempValue += memo[currRow + 1][aliceCell + aliceMoves][bobCell + bobMoves];
						}
						else tempValue += (-1e9);
						maxPossibleChocolates = max(maxPossibleChocolates, tempValue);
					}
				}
				memo[currRow][aliceCell][bobCell] = maxPossibleChocolates;
			}
		}
	}
	return memo[0][0][c - 1];
}

/*Space optimise code using 2- 2D DP arrays instead of using 3D DP */
int mostOptimalResultUsingSpaceOptimisation(int r, int c, vector<vector<int>> &grid) {
	//base case
	vector<vector<int>> memo(c, vector<int>(c)), front(c, vector<int>(c));
	for (int alice = 0 ; alice < c; alice++) {
		for (int bob = 0; bob < c; bob++) {
			//if both are at the same cell in the end then
			if (alice == bob)front[alice][bob] = grid[r - 1][bob];
			else front[alice][bob] = grid[r - 1][alice] + grid[r - 1][bob];
		}
	}

	//now we set the values for the last row so for the rest of rows (n-2 to 0)
	for (int currRow = r - 2; currRow >= 0 ; currRow--) {
		for (int aliceCell = 0; aliceCell < c; aliceCell++) {
			for (int bobCell = 0; bobCell < c; bobCell++) {
				int maxPossibleChocolates = INT_MIN;
				//for 9 possibilities
				for (int aliceMoves = -1; aliceMoves <= 1; aliceMoves++) {
					for (int bobMoves = -1; bobMoves <= 1; bobMoves++) {
						int tempValue = 0;
						if (aliceCell == bobCell)tempValue = grid[currRow][aliceCell];
						else tempValue = grid[currRow][aliceCell] + grid[currRow][bobCell];
						//check for the overflow cases
						if (aliceMoves + aliceCell >= 0 and aliceCell + aliceMoves < c and bobCell + bobMoves >= 0 and bobCell + bobMoves < c) {
							tempValue += front[aliceCell + aliceMoves][bobCell + bobMoves];
						}
						else tempValue += (-1e9);
						maxPossibleChocolates = max(maxPossibleChocolates, tempValue);
					}
				}
				memo[aliceCell][bobCell] = maxPossibleChocolates;
			}
		}
		front = memo;
	}
	return front[0][c - 1];
}


int maximumChocolates(int r, int c, vector<vector<int>> &grid) {
	/*	alice is at (0, 0) and bob is at (0, col - 1) both are moving downward simultaneously , which means row remains same
	for every point but column will changes so for that we take row as common and columns for both variable so in short
	it will done in 3 states which means it will be done using 3-D DP */
	//for recursion
	// int ans = findMaximumChocolates(0, 0, c - 1, grid, r, c);

	// vector<vector<vector<int>>> memo(r, vector<vector<int>>(c, vector<int>(c, -1)));
	// int ans = findMaximumChocolatesMemo(0, 0, c - 1, grid, r, c, memo);

	//for tabulation
	// int ans = findMaximumChocolatesTabu(r, c, grid);

	//for space optimised approach

	int ans = mostOptimalResultUsingSpaceOptimisation(r, c, grid);
	return ans;

}

int main() {
	int row, col;
	cin >> row >> col;
	vector<vector<int>>grid(row, vector<int> (col));
	for (int i = 0; i < row; i++) for (int j = 0; j < col; j++) cin >> grid[i][j];
	cout << maximumChocolates(row, col, grid);
	return 0;

}
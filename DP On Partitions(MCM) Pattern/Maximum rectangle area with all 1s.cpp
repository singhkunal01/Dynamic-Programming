#include<bits/stdc++.h>
using namespace std;


//this is the code of finding the area of largest rectangle in the histogram in one pass
int giveMaxAreaInRectangle(vector<int> &bars) {
	int n = bars.size(), largestArea = INT_MIN;
	stack<int> st;
	for (int i = 0 ; i <= n; i++) {
		while (!st.empty() and (i == n or bars[st.top()] >= bars[i])) {
			int height = bars[st.top()], width = 1;
			st.pop();
			if (st.empty()) width = i;
			else width = i - 1 - st.top();
			height *= width;
			largestArea = max(largestArea, height);
		}
		st.push(i);
	}
	return largestArea;
}


//this is the main code which is used to find the maxarea of the binary matrix
int maximalRectangle(vector<vector<char>>& matrix) {
	int n = matrix.size(), m = matrix[0].size();
	vector<int> heights(m);
	int maxArea = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (matrix[i][j] == '1') heights[j]++;
			else heights[j] = 0;
		}
		//till now we have all possible histograms  of each cell
		int area = giveMaxAreaInRectangle(heights);
		maxArea = max(area, maxArea);
	}
	return maxArea;
}


int main() {
	int n, m;
	cin >> n >> m;
	vector<vector<char>> matrix(n, vector<char> (m));
	for (int i = 0; i < n; i ++)
		for (int j = 0; j < m; j++)
			cin >> matrix[i][j];
	cout << maximalRectangle(matrix);
	return 0;

}
#include<bits/stdc++.h>
using namespace std;

//recursive
int findMaxProfit(int i, int n, vector<int> &profit, bool buy, int prof) {
//base case
	if (i >= n) return 0;
//if ww buy something
	if (buy) {
		prof = max(-profit[i] + findMaxProfit(i + 1, n, profit, false, prof), findMaxProfit(i + 1, n, profit, true, prof));
	}
	else {
		prof = max(profit[i] + findMaxProfit(i + 1, n, profit, true, prof), findMaxProfit(i + 1, n, profit, false, prof));

	}
	return prof;
}


int maxProfit(vector<int> &prices) {
	int n = prices.size();
	return findMaxProfit(0, n, prices, true, 0);

}

int main() {
	int n;
	cin >> n;
	vector<int> prices(n);
	for (int &i : prices) cin >> i;
	cout << maxProfit(prices);
	return 0;

}
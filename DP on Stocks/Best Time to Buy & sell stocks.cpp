#include<bits/stdc++.h>
using namespace std;

int maxProfit(vector<int>& prices) {
	int n = prices.size();
	int buyAt = prices[0], profitOf = 0;
	for (int i = 1 ; i < n; i++) {
		int cost = prices[i] - buyAt; //total profit or loss
		profitOf = max(profitOf, cost);
		buyAt = min(buyAt, prices[i]);
	}
	return profitOf;
}

int main() {
	int days;
	cin >> days;
	vector<int> prices(days);
	for (int &pricePerDay : prices) cin >> pricePerDay;
	cout << maxProfit(prices);
	return 0;
}

//singhkunal01bu
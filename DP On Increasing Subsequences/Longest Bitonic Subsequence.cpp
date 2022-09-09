#include<bits/stdc++.h>
using namespace std;

int longestBitonicSequence(vector<int>& arr, int n) {
	vector<int> leftToRight(n, 1), rightToLeft(n, 1);
	int maxLength = 0;

	/*finding lis from left to right*/
	for (int i =  0; i < n; i++) {
		for (int prev = 0; prev < i; prev++) {
			if (arr[i] > arr[prev] && leftToRight[i] < 1 + leftToRight[prev]) {//another condition is for preventing it to change afterward if somewhere the value is same
				leftToRight[i] = max(leftToRight[i], 1 + leftToRight[prev]);
			}
		}
	}

	/*finding lis from right to left*/
	for (int i =  n - 1; i >= 0; i--) {
		for (int prev = n - 1; prev > i; prev--) {
			if (arr[i] > arr[prev] && rightToLeft[i] < 1 + rightToLeft[prev]) {//another condition is for preventing it to change afterward if somewhere the value is same
				rightToLeft[i] = max(rightToLeft[i], 1 + rightToLeft[prev]);
			}
		}
//now find the bitonic subsequence length using first and second and in both the index for
// which we are calculating is counted twice so for checking the Length of Bitonic LIS first reduce - 1
		maxLength = max(maxLength, leftToRight[i] + rightToLeft[i] - 1);

	}
	return maxLength;
}


int main() {

	int n; cin >> n;
	vector<int> arr(n);
	for (int &i : arr) cin >> i;
	cout << longestBitonicSequence(arr, n);
	return 0;

}
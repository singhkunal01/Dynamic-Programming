#include<bits/stdc++.h>
using namespace std;

/*We can also use Recursive , Memoisation ,Tabulation and Space optimised in it but for better complexity we use
most optimal which required only sum/2 space */

bool partitionChecker(int target,  vector<int> &arr, int n) {
	vector<bool> prev(target + 1, false), curr(target + 1, false);
	prev[0] = curr[0] = true;
	prev[arr[0]] = true;
	for (int index = 1; index < n; index++) {
		for (int givenTarget = 1; givenTarget <= target ; givenTarget++) {
			bool notPick = prev[givenTarget];
			bool pick = false;
			if (givenTarget >= arr[index]) pick = prev[givenTarget - arr[index]];
			curr[givenTarget] = (pick or notPick);
		}
		prev = curr;
	}
	return prev[target];
}


bool canPartition(vector<int> &arr, int n)
{
	// Write your code here.
	int totalSum = accumulate(arr.begin(), arr.end(), 0);
	if (totalSum & 1) return false;
	return partitionChecker(totalSum / 2, arr, n);
}

int main() {
	int n; cin >> n;
	vector<int> arr(n);
	for (int &i : arr) cin >> i;
	if (canPartition(arr, n)) cout << "Can Be partitioned" << endl;
	else cout << "Can not Be partitioned" << endl;
	return 0;

}
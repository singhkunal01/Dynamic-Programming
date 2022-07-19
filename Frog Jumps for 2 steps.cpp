#include<bits/stdc++.h>
using namespace std;


//most optimised code without using any extra space
int frogJump(int n, vector<int> &heights)
{
    // Write your code here.
    int fPrev = 0, sPrev = 0, currAns;
    for (int i = 1; i < n; i++) {
        int left = fPrev + abs(heights[i] - heights[i - 1]);
        int right = INT_MAX;
        if (i > 1) right = sPrev + abs(heights[i] - heights[i - 2]);
        //find the min of both
        currAns = min(left, right);
        sPrev = fPrev;
        fPrev = currAns;
    }
    return fPrev;
}




// ==> Tabulation approach reduced a extra stack space of the recursion
int frogJumpTab(int n, vector<int> &heights)
{
    // Write your code here.
    vector<int> dp(n, -1);
    dp[0] = 0; //somwhat type a base case
    for (int i = 1; i < n; i++) {
        int left = dp[i - 1] + abs(heights[i] - heights[i - 1]);
        int right = INT_MAX;

        if (i > 1) right = dp[i - 2] + abs(heights[i] - heights[i - 2]);
        //find the min of both
        dp[i] = min(left, right);
    }
    return dp[n - 1];
}




// ==>  Memoisation approach using Extra space with a recursion stack space
int frogJump(int i, vector<int> &heights, vector<int> &dp) {
    //we start moving from the last thats why the base is this
    if (i == 0)return 0;
    if (dp[i] != -1) return dp[i];
    int left = frogJump(i - 1, heights, dp) + abs(heights[i] - heights[i - 1]);
    int right = INT_MAX;
    if (i > 1) right = frogJump(i - 2, heights, dp) + abs(heights[i] - heights[i - 2]);
    return dp[i] = min(left, right);
}


int main() {
    int n;
    cin >> n;
    vector<int> heights(n);
    vector<int> dp(n + 1, -1);
    for (int &i : heights) cin >> i;
    // cout << frogJump(n, heights) << endl;
    cout << frogJumpTab(n, heights) << endl;
    // cout << frogJump(n, heights, dp) << endl;
}


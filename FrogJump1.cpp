#include<bits/stdc++.h>
using namespace std;

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

int main() {
    int n;
    cin >> n;
    vector<int> heights(n);
    for (int &i : heights) cin >> i;
    cout << frogJump(n, heights) << endl;
}
//simple recursive solution gives TLE so memoise it using dp

/*
==>  Memoisation approach using Extra space with a recursion stack space

int solveJumps(int i,vector<int> &h,vector<int> &dp){
    //we start moving from the last thats why the base is this
    if(i==0)return 0;
    if(dp[i]!=-1) return dp[i];
    int left = solveJumps(i-1,h,dp)+abs(h[i]-h[i-1]);
    int right = INT_MAX;
    if(i>1) right = solveJumps(i-2,h,dp)+abs(h[i]-h[i-2]);
    return dp[i]=min(left,right);
}

int frogJump(int n, vector<int> &heights)
{
    // Write your code here.
    vector<int> dp(n+1,-1);
    return solveJumps(n-1,heights,dp);
}

==> Tabulation approach reduced a extra stack space of the recursion
int frogJump(int n, vector<int> &heights)
{
    // Write your code here.
    vector<int> dp(n,-1);
    dp[0]=0;//somwhat type a base case
    for(int i = 1;i<n;i++){
        int left = dp[i-1]+abs(heights[i]-heights[i-1]);
        int right = INT_MAX;

        if(i>1) right = dp[i-2]+abs(heights[i]-heights[i-2]);
        //find the min of both
        dp[i]=min(left,right);
    }
    return dp[n-1];
}


*/
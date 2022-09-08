#include<bits/stdc++.h>
using namespace std;

bool lengthWise(string &s1, string &s2) {
	return s1.size() < s2.size();
}

bool checkPattern(string &currWord, string &prevWord) {
	//since for moving forward the size of prevWord has to be +1 equals to the currWord otherwise return false
	if (prevWord.size() + 1 != currWord.size()) return false;
	int currPtr = 0, prevPtr = 0;
	//since the currWord is greater
	while (currPtr < currWord.size()) {
		if (prevPtr < prevWord.size() and currWord[currPtr] == prevWord[prevPtr]) currPtr++, prevPtr++;
		else currPtr++;/* since currWord is the larger one so obviously it has greater number of
		characters so if somehow any character is not matched then we have to move the currPtr only*/
	}
//now if both the pointers are at the end then the chain pattern is correct otherwise not
	return (currPtr == currWord.size() and prevPtr == prevWord.size());
}

int longestStrChain(vector<string>& words) {
	int n = words.size();
	sort(words.begin(), words.end(), lengthWise);//sorting because we need the subset since some of the words are also occured previously which we need for further chain
	vector<int> dp(n, 1);
	int lastIdx = -1, maxLength = 0;
	for (int i =  0; i < n; i++) {
		for (int prev = 0; prev < i; prev++) {
			if (checkPattern(words[i], words[prev]) && dp[i] < 1 + dp[prev]) {//another condition is for preventing it to change afterward if somewhere the value is same
				dp[i] = max(dp[i], 1 + dp[prev]);
			}
		}
		maxLength = max(maxLength, dp[i]);
	}
	return maxLength;
}



int main() {
	int n;
	cin >> n;
	vector<string> words(n);
	for (string &i : words) cin >> i;
	cout << longestStrChain(words);
	return 0;

}

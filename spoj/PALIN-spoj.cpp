#include <iostream>
#include <bits/stdc++.h>
using namespace std;

string getReverse(string& str) {
	string revStr = str;
	
	int i = 0, j = str.length()-1;
	while (i < j) {
		char temp = revStr[i];
		revStr[i] = revStr[j];
		revStr[j] = temp;
		i++;
		j--;
	}
	
	return revStr;
}

bool checkAllNines(string& str) {
	for (char ch : str) {
		if (ch != '9') return false;
	}
	
	return true;
}

void incrementByOne(string& str) {
	int i = str.length()-1;
	while (str[i] == '9') {
		str[i] = '0';
		i--;
	}
	str[i] = (char)(str[i] + 1);
}

string getNextPalin(string& str) {
	int n = str.length();
	string center = "";
	if (n % 2 == 1) center += str[n/2];

	string left = "";
	for (int i = 0; i < str.length()/2; i++) {
		left += str[i];
	}
	
	string revLeft = getReverse(left);
	string newString1 = left + center + revLeft;
	// cout << "left: " << left << endl;
	// cout << "center: " << center << endl;
	// cout << "newString1: " << newString1 << endl;
	if (newString1 > str) return newString1;

	if (center.length() > 0) {
		if (center < "9") {
			center[0] = (char)(center[0] + 1);
			return (left + center + revLeft);
		}
		
		center = "0";
	}
	
	if (checkAllNines(left)) {
		string solution2 = "1";
		for (int i = 0; i < n-1; i++) solution2 += "0";
		solution2 += "1";
		return solution2;
	}
	
	incrementByOne(left);

	return (left + center + getReverse(left));
}

int main() {
	// your code goes here
	int T;
	cin >> T;
	while (T--) {
		string numStr;
		cin >> numStr;
		
		cout << getNextPalin(numStr) << endl;
	}
	
	return 0;
}
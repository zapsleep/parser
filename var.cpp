#include <iostream>
#include <ctype.h>
#include "var.h"

long Var::isVar(string s) {
	
	
	return s.length();
}

long Var::isWord(string s) {
	int i=0;
	char c;
	
	while ((c=s.at(i++))!=string::npos) {
		if (c==' ' || c=='\t' || c=='\n') continue;
		else if (isalpha(c)) break;
		else break;
	}
	
	while ((c=s.at(i++))!=string::npos) {
		if (isalnum(c)) continue;
		else {
			cout << "Var is valid: " << s.substr(0, i-1) << endl;
			return i-1;
		}
	}
	
	cout << "Var is non-valid: illegal starting symbol" << endl;
	return 0;
}

long Var::isFunc(string s) {
	int i=0;
	long termLength;
	char c;
	
	termLength = Var::isWord(s);
	if (!termLength) {
		cout << "Func is non-valid: no word" << endl;
		return 0;
	}
	
	i = termLength+1;
	while((c=s.at(i++))!=string::npos) {
		if (c==' ' || c=='\t' || c=='\n') continue;
		else if (c=='(') break;
		else {
			cout << "Func is invalid: no bracket" << endl;
			return 0;
		}
	}
	
	//check inside the brackets
	
	
	cout << "Func is invalid" << endl;
	return 0;
}

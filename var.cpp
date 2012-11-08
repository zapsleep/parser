#include <iostream>
#include <ctype.h>
#include "var.h"

long Var::isVar(string s) {
	long parseDepth;
	
	parseDepth = Var::isWord(s);
	if (parseDepth) {
		//cout << "var is word" << endl;
		return parseDepth;
	}
	
	parseDepth = Var::isNum(s);
	if (parseDepth) {
		//cout << "var is num: " << s.substr(0, parseDepth) << endl;
		return parseDepth;
	}
	
	//cout << "var failed" << endl;
	return 0;
}

long Var::isNum(string s) {
	char c;
	long pos=0;
	
	while ((c=s.at(pos++))!=string::npos) {
		if (c==' ' || c=='\t' || c=='\n') continue;
		else if (isdigit(c)) break;
		else {
			//cout << "varNum failed" << endl;
			return 0;
		}
	}
	
	while ((c=s.at(pos++))!=string::npos) {
		if (isdigit(c)) continue;
		else {
			//cout << "var is num" << endl;
			return pos-1;
		}
	}
	
	//cout << "varNum failed" << endl;
	return 0;
}

long Var::isWord(string s) {
	long pos=0;
	char c;
	
	while ((c=s.at(pos++))!=string::npos) {
		if (c==' ' || c=='\t' || c=='\n') continue;
		else if (isalpha(c)) break;
		else {
			//cout << "var failed: wrong first symbol" << endl;
			return 0;
		}
	}
	
	while ((c=s.at(pos++))!=string::npos) {
		if (isalnum(c)) continue;
		else {
			//cout << "var is valid: " << s.substr(0,pos-1) << endl;
			return pos-1;
		}
	}
	
	//cout << "var failed" << endl;
	return 0;
}

long Var::isFunc(string s) {
	return 0;
}

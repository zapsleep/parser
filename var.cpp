#include <iostream>
#include <ctype.h>
#include "var.h"

long Var::isVar(string s) {
	long parseDepth;
	
	parseDepth = Var::isFunc(s);
	if (parseDepth) {
		//cout << "var is func" << endl;
		return parseDepth;
	}
	
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
	long pos = 0;
	char c;
	long parseDepth;
	
	parseDepth = Var::isWord(s);
	if (!parseDepth) {
		//cout << "func failed" << endl;
		return 0;
	}
	
	pos = parseDepth;
	while((c=s.at(pos++))!=string::npos) {
		if (c==' ' || c=='\t' || c=='\n') continue;
		else if (c=='(') break;
		else {
			//cout << "func failed: bracket" << endl;
			return 0;
		}
	}
	
	while ((c=s.at(pos++))!=string::npos) {
		if (c==' ' || c=='\t' || c=='\n') continue;
		else if (c==')') {
			//cout << "func is valid" << endl;
			return pos;
		}
		else break;
	}
	
	parseDepth = Var::isVar(s.substr(--pos));
	if (!parseDepth) {
		//cout << "func argument failed: " << endl;
		return 0;
	}
	pos+=parseDepth;
	
	while ((c=s.at(pos++))!=string::npos) {
		if (c==' ' || c=='\t' || c=='\n') continue;
		else if (c==')') {
			//cout << "func is valid" << endl;
			return pos;
		}
		else {
			parseDepth = Var::isComma(s.substr(--pos));
			if (!parseDepth) {
				//cout << "func comma failed" << s.substr(0, pos) << endl;
				return 0;
			}
			pos+=parseDepth;
			parseDepth = Var::isVar(s.substr(pos));
			if (!parseDepth) {
				//cout << "func next argument failed" << endl;
				return 0;
			}
			pos+=parseDepth;
		}
	}
	
	//cout << "func failed" << endl;
	return 0;
}

long Var::isComma(string s) {
	long pos = 0;
	char c;
	
	while ((c=s.at(pos++))!=string::npos) {
		if (c==' ' || c=='\t' || c=='\n') continue;
		else if (c==',') {
			//cout << "comma is valid" << endl;
			return pos;
		}
		else break;
	}
	
	//cout << "comma failed" << endl;
	return 0;
}

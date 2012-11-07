#include "expr.h"
#include "var.h"
#include <iostream>

using namespace std;

long Expr::isMathExpr(string s) {
	char c;
	int i=0;
	long overall=0;
	
	long termLength = Var::isWord(s);
	if (!termLength) {
		cout << "Math expr is invalid: no var at start" << endl;
		return 0;
	}
	overall+=termLength;
	
	termLength = Expr::isMathOper(s.substr(overall));
	if (!termLength) {
		cout << "Math expr is invalid: no operator" << endl;
		return 0;
	}
	overall+=termLength;
	
	termLength = Var::isWord(s.substr(overall));
	if (!termLength) {
		cout << "Math expr is invalid: no var at end" << endl;
		return 0;
	}
	overall+=termLength;
	
	while ((c=s.at(overall++))!=string::npos) {
		if (c==' ' || c=='\t' || c=='\n') continue;
		else if (c==';') {
			cout << "Math expr is valid: " << s.substr(0, overall) << endl;
			return overall;
		}
		else break;
	}
		
	cout << "Expression is non-valid: no semicolon" << endl;
	return 0;
}

long Expr::isCondExpr(string s) {
	char c;
	long i=0;
	int brackets=0;
	
	//Searching for "("
	while ((c=s.at(i++))!=string::npos) {		
		if (c==' ' || c=='\t' || c=='\n') continue;
		else if (c=='(') {
			brackets++;
			break;
		}
	}
	
	if (!brackets) {
		cout << "Cond_expr is not valid: no opening bracket" << endl;
		return 0;
	}
	
	//Searching for other brackets
	while ((c=s.at(i++))!=string::npos) {
		if (c=='(') brackets++;
		else if (c=='{') {
			break;
		}
		else if (c==')') {
			brackets--;
			if (!brackets) {
				cout << "Conditional expr: ";
				cout << s.substr(0, i) << endl;
				return i;
			}
		}
		
		//TODO check for non-valid symbols
	}
	
	cout << "Cond_expr is not valid: no closing bracket" << endl;
	return 0;
}

long Expr::isBlock(string s) {
	int i=0;
	char c;
	long termLength = 0;
	long overall = 0;
	
	while ((c=s.at(i++))!=string::npos) {
		if (c==' ' || c=='\t' || c=='\n') continue;
		else if (c=='{') {
			termLength++;
			break;
		}
		else return Expr::isMathExpr(s.substr(i-1));
	}
	
	if (!termLength) {
		cout << "Block is not valid: no opening bracket" << endl;
		return 0;
	}
	
	overall = i-1+termLength;
	
	while ((c=s.at(i++))!=string::npos) {
		if (c==' ' || c=='\t' || c=='\n') {
			overall++;
			continue;
		}
		else if (c=='}') {
			overall++;
			cout << "Block is valid" << endl;
			return overall;
		}
		else {
			long sub = Expr::isMathExpr(s.substr(i-1));
			if (sub) {
				overall+=sub;
				i+=sub;
			}
		}
	}
	
	cout << "Block is not valid: no closing bracket" << endl;
	return 0;
}

long Expr::isMathOper(string s) {
	int i=0;
	char c;
	
	while ((c=s.at(i++))!=string::npos) {
		if (c==' ' || c=='\t' || c=='\n') continue;
		else if (c=='+' || c=='*' || c=='-' || c=='/' || c=='%' || c=='=') {
			cout << "Math operator is valid: " << s.at(i-1) << endl;
			return i;
		}
		else break;
	}
	
	cout << "Math operator not found" << endl;
	return 0;
}

#include "expr.h"
#include "var.h"
#include <iostream>

using namespace std;

long Expr::isMathExpr(string s) {
	char c;
	int i=0;
	
	while ((c=s.at(i++))!=string::npos) {
		if (c==' ' || c=='\t' || c=='\n') continue;
		else if (c==';') {
			cout << "Expression is valid" << endl;
			cout << s.substr(0, i) << endl;
			cout << "#end" << endl;
			return i;
		}
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
	long currentPosition = 0;
	
	while ((c=s.at(i++))!=string::npos) {
		if (c==' ' || c=='\t' || c=='\n') continue;
		else if (c=='{') {
			currentPosition++;
			break;
		}
		else return Expr::isMathExpr(s.substr(i-1));
	}
	
	if (!currentPosition) {
		cout << "Block is not valid: no opening bracket" << endl;
		return 0;
	}
	
	while ((c=s.at(i++))!=string::npos) {
		if (c==' ' || c=='\t' || c=='\n') {
			currentPosition++;
			continue;
		}
		else if (c=='}') {
			currentPosition++;
			cout << "Block is valid" << endl;
			return currentPosition;
		}
		else {
			long sub = Expr::isMathExpr(s.substr(i-1));
			if (sub) {
				currentPosition+=sub;
				i+=sub;
			}
		}
	}
	
	cout << "Block is not valid: no closing bracket" << endl;
	return 0;
}

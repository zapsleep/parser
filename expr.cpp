#include "expr.h"
#include "var.h"
#include <iostream>

using namespace std;

int nesting = 0;

long Expr::isMathExpr(string s) {
	//cout << "Parsing math_expr" << endl;
	char c;
	long parseLength;
	long pos=0;
	
	parseLength = Expr::isMathExprAdd(s);
	if (!parseLength) {
		//cout << "math_expr failed" << endl;
		return 0;
	}
	pos+=parseLength;
	
	while ((c=s.at(pos))!=string::npos) {
		parseLength = Expr::isMathExprAddOp(s.substr(pos));
		if (!parseLength) {
			cout << "math_expr is add: " << s.substr(0,pos) << endl;
			//cout << s.substr(0,pos) << endl;
			return pos;
		}
		long prePos = parseLength;
		parseLength = Expr::isMathExprAdd(s.substr(pos+parseLength));
		if (!parseLength) {
			cout << "math_exrp is add: " << s.substr(0,pos) << endl;
			//cout << s.substr(0,pos) << endl;
			return pos;
		}
		pos+=(prePos+parseLength);
	}
	
	cout << "math_expr: End of file is reached" << endl;
	return pos;
}

long Expr::isMathExprAdd(string s) {
	//cout << "Parsing add" << endl;
	char c;
	long parseLength;
	long pos=0;
	
	parseLength = Expr::isMathExprMult(s);
	if (!parseLength) {
		//cout << "add failed" << endl;
		return 0;
	}
	pos+=parseLength;
	
	while ((c=s.at(pos))!=string::npos) {
		parseLength = Expr::isMathExprMultOp(s.substr(pos));
		if (!parseLength) {
			cout << "add is mult: " << s.substr(0,pos) << endl;
			//cout << s.substr(0,pos);
			return pos;
		}
		long prePos = parseLength;
		parseLength = Expr::isMathExprMult(s.substr(pos+parseLength));
		if (!parseLength) {
			cout << "add is mult: " << s.substr(0,pos) << endl;
			//cout << s.substr(0,pos);
			return pos;
		}
		pos+=(prePos+parseLength);
	}
	
	cout << "add: End of file is reached" << endl;
	return pos;
}

long Expr::isMathExprMult(string s ) {
	//cout << "Parsing mult" << endl;
	char c;
	long parseLength;
	long pos=0;
	
	parseLength = Var::isVar(s);
	if (!parseLength) {
		while ((c=s.at(pos++))!=string::npos) {
			if (c==' ' || c=='\t' || c=='\n') continue;
			else if (c=='(') break;
			else {
				//cout << "Bracket mult failed" << endl;
				return 0;
			}
		}
		parseLength = Expr::isMathExpr(s.substr(pos));
		if (!parseLength) {
			//cout << "No math_expr inside brackets" << endl;
			return 0;
		}
		pos+=parseLength;
		while ((c=s.at(pos++))!=string::npos) {
			if (c==' ' || c=='\t' || c=='\n') continue;
			else if (c==')') {
				cout << "mult is valid expr: " << s.substr(0,pos) << endl;
				//cout << s.substr(0,pos);
				return pos;
			}
			else {
				//cout << "Bracket mult failed" << endl;
				return 0;
			}
		}
	}
	
	//cout << "mult is valid var: " << s.substr(0, parseLength) << endl;
	//cout << s.substr(0, parseLength) << endl;
	return parseLength;
}

long Expr::isMathExprAddOp(string s) {
	//cout << "Parsing add op" << endl;
	char c;
	long pos=0;
	
	while ((c=s.at(pos++))!=string::npos) {
		if (c==' ' || c=='\t' || c=='\n') continue;
		else if (c=='+' || c=='-' || c=='=') {
			cout << "add op valid: " << s.substr(0, pos) << endl;
			//cout << s.substr(0, pos);
			return pos;
		}
		else break;
	}
	
	//cout << "add op failed" << endl;
	return 0;
}

long Expr::isMathExprMultOp(string s) {
	//cout << "Parsing mult op" << endl;
	char c;
	long pos=0;
	
	while ((c=s.at(pos++))!=string::npos) {
		if (c==' ' || c=='\t' || c=='\n') continue;
		else if (c=='*' || c=='/' || c=='%') {
			cout << "mult op valid: " << s.substr(0,pos) << endl;
			//cout << s.substr(0,pos);
			return pos;
		}
		else break;
	}
	
	//cout << "mult op failed" << endl;
	return 0;
}

long Expr::isSemicolon(string s) {
	char c;
	long pos = 0;
	
	while ((c=s.at(pos++))!=string::npos) {
		if (c==' ' || c=='\t' || c=='\n') continue;
		else if (c==';') {
			//cout << "semicolon found" << endl;
			return pos;
		}
		else break;
	}
	
	//cout << "semicolon not found" << endl;
	return 0;
}

long Expr::isCondExpr(string s) {
	char c;
	int pos=0;
	int brackets=0;
	
	while ((c=s.at(pos++))!=string::npos) {
		if (c==' ' || c=='\t' || c=='\n') continue;
		else if (c=='(') brackets++;
		else break;
	}
	
	if (!brackets) {
		cout << "cond_expr failed: no opening bracket" << endl;
		return 0;
	}
	
	while ((c=s.at(pos++))!=string::npos) {
		if (c==')') brackets--;
		else if (c=='(') brackets++;
		if (!brackets) {
			//cout << "cond_expr valid: " << s.substr(0, pos) << endl;
			return pos;
		}
	}
	
	cout << "cond_expr failde: no closing bracket" << endl;
	return 0;
}

long Expr::isBlock(string s) {
	char c;
	int pos=0;
	long parseDepth=0;
	
	while ((c=s.at(pos++))!=string::npos) {
		if (c==' ' || c=='\t' || c=='\n') continue;
		else if (c=='{') break;
		else {
			parseDepth = Expr::isMathExpr(s);
			if (!parseDepth) {
				cout << "Block failed: no math_expr" << endl;
				return 0;
			}
			
			//cout << "Block is valid: one-line" << endl;
			return parseDepth;
		}
	}
	
	while ((c=s.at(pos++))!=string::npos) {
		if (c==' ' || c=='\t' || c=='\n') continue;
		else if (c=='}') {
			//cout << "Block is valid" << endl;
			return pos;
		}
		else {
			nesting = 0;
			parseDepth = Expr::isMathExpr(s.substr(--pos));
			if (!parseDepth) {
				cout << "Block failed: expression failed" << endl;
				return 0;
			}
			cout << "Expression: " << s.substr(pos,parseDepth) << endl
				<< endl;
			pos+=parseDepth;
			parseDepth = Expr::isSemicolon(s.substr(pos));
			if (!parseDepth) {
				cout << "Block failed: semicolon failed" << endl;
				return 0;
			}
			pos+=parseDepth;
		}
	}
	
	cout << "Block failed: no closing bracket" << endl;
	return 0;
}

void Expr::nest() {
	for (int i=0; i<nesting; ++i) cout << " ";
}

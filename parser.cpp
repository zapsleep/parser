#include <iostream>
#include "parser.h"
#include "expr.h"

using namespace std;

void Parser::parse(string s) {
	long ifPos = -1;
	long parseLength;
	char c;
	
	while((ifPos=s.find("if", ifPos+1))!=string::npos) 
	{
		cout << ifPos << endl;
		ifPos+=2;
		
		parseLength = Expr::isCondExpr(s.substr(ifPos));
		if (!parseLength) {
			cout << "IF-statement is not valid" << endl;
			continue;
		}
		
		ifPos += parseLength;
		
		parseLength = Expr::isBlock(s.substr(ifPos));
	}
}

bool Parser::isSpace(char c) {
	if (c==' ' || c=='\t' || c=='\n') return true;
	return false;
}

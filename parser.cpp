#include <iostream>
#include "parser.h"
#include "expr.h"

using namespace std;

void Parser::parse(string s) {
	long ifPos = -1;
	long parseDepth;
	
	//searching for if
	while ((ifPos=s.find("if", ifPos+1))!=string::npos) {
		cout << "IF-statement at " << ifPos << endl;
		
		//shift position by two symbols - 'if'
		ifPos+=2; 
		//now work with the rest of string
		//<cond_expr>
		parseDepth = Expr::isCondExpr(s.substr(ifPos));
		if (!parseDepth) {
			cout << "IF-statement failed: no cond_expr" << endl;
			continue;
		}
		ifPos+=parseDepth;

		//<op_block>
		parseDepth = Expr::isBlock(s.substr(ifPos));
		if (!parseDepth) {
			cout << "IF-statement failed: no block" << endl;
			continue;
		}
		ifPos+=parseDepth;

		char c;
		while ((c=s.at(ifPos++))!=string::npos) {
			if (c==' ' || c=='\t' || c=='\n') continue;
			else break;
		}
		
		if (s.substr(--ifPos).find("else")==0) {
			cout << "Found else statement" << endl;
			//Search for another block
			parseDepth = Expr::isBlock(s.substr(ifPos+4));
			if (!parseDepth) {
				cout << "Else statement failed: no block" << endl;
			}
			ifPos+=parseDepth;
		}
		
		cout << "IF-statement ended" << endl << endl;
	}
}

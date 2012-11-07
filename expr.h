#ifndef CONDEXPR_H_
#define CONDEXPR_H_

#include <string>

using namespace std;

class Expr {
	public:
	static long isMathExpr (string s);
	static long isCondExpr (string s);
	static long isBlock (string s);
	private:
	static long isMathOper (string s);
};

#endif

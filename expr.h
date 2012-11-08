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
	static long isMathExprAdd (string s);
	static long isMathExprMult (string s);
	static long isMathExprAddOp (string s);
	static long isMathExprMultOp (string s);
	static long isSemicolon (string s);
};

#endif

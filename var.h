#ifndef VAR_H_
#define VAR_H_

#include <string>

using namespace std;

class Var {
	public:
	static long isVar(string s);
	static long isWord(string s);
	static long isFunc(string s);
	static long isNum(string s);
	
	private:
	static long isComma(string s);
};

#endif

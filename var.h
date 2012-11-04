#ifndef VAR_H_
#define VAR_H_

#include <string>

using namespace std;

class Var {
	public:
	static long isVar(string s);
	
	private:
	static long isWord(string s);
	static long isFunc(string s);
};

#endif

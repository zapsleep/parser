#ifndef PARSER_H
#define PARSER_H

#include <string>

using namespace std;

class Parser {
	public:
	static void parse(string s);
	
	private:
	static bool isSpace(char c);
};

#endif

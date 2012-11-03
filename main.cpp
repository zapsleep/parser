#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <malloc.h>
#include "parser.h"

using namespace std;

int main(int argc, char** argv)
{
	if (argc < 2) {
		printf("Not enough arguments!\n");
		exit(0);
	}
	
	if (argc > 2) {
		printf("Too much arguments!\n");
		exit(0);
	}
	
	ifstream fin;
	fin.open(argv[1]);
	string s;
	char *buf = new char[1];
	while (fin) {
		fin.read(buf, 1);
		s.append(buf, 1);
	}
	Parser::parse(s);
	delete buf;
	fin.close();
	
	return 0;
}

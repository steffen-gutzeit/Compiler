/*
 * TestParser.cpp
 *
 *  Created on: 08.10.2016
 *      Author: compiler
 */

#include <iostream>
#include "../../../Scanner/src/Scanner.h"
#include "Parser.h"


int main(int argc, char* argv[], char* envp[])
{
	Scanner *s;
	Parser *p;

	// parse arguments
	if (argc <= 1)
	{
		std::cerr << "Syntax: " << argv[0]
		 << " Inputfile [Outputfile]" << std::endl;
		return 1;
	}
	else if (argc <= 2)
	{
		// std::cerr << "no output file given. Assuming \"out.txt\"." << std::endl;
		s = new Scanner(argv[1], (char *)"out2.txt");
	}
	else
	{
		s = new Scanner(argv[1], argv[2]);
	}

	p = new Parser(s);
	return p->processFile();

}

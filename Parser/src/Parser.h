/*
 * Parser.h
 *
 *  Created on: 07.10.2016
 *      Author: compiler
 */

#ifndef PARSER_SRC_PARSER_H_
#define PARSER_SRC_PARSER_H_


#include "Scanner.h"
#include "Token.h"
//#include "parserConst.h"
//#include "Node.h"
//#include "NodeInfo.h"
//#include "ParseTree.h"

class Parser {
public:
	Parser(Scanner *scanner);
	virtual ~Parser();

	int parseFile();

private:

	Scanner *scanner;
	//ParseTree *parseTree;

};




#endif /* PARSER_SRC_PARSER_H_ */

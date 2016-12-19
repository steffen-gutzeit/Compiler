#include "ParserConstant.h"

#include <iostream>

ParserConstant::ParserConstant() {
}
	
std::string ParserConstant::nodeTypeAsString(NodeType myNodeType)
{
	std::string myResult;
	switch(myNodeType)
	{
		case NODE_ROOT: myResult = "Root"; break;
		case NODE_ERROR: myResult = "Node Error"; break;
		case NODE_PROG: myResult = "PROG"; break;
		case NODE_DECLS: myResult = "DECLS"; break;
		case NODE_DECL: myResult = "DECL"; break;
		case NODE_ARRAY: myResult = "ARRAY"; break;
		case NODE_STATEMENTS: myResult = "STATEMENTS"; break;
		case NODE_STATEMENT: myResult = "STATEMENT"; break;
		case NODE_EXP: myResult = "EXP"; break;
		case NODE_EXP2: myResult = "EXP2"; break;
		case NODE_INDEX: myResult = "INDEX"; break;
		case NODE_OP_EXP: myResult = "OP_EXP"; break;
		case NODE_OP: myResult = "OP"; break;
		case NODE_KEYWORD: myResult = "Keyword"; break;
		case NODE_IDENTIFIER: myResult = "Identifier"; break;
		default: myResult = "unknown"; break;
	}
	return myResult;
}



std::string ParserConstant::typificationAsString(Typification typification)
{
	std::string myResult;
	switch(typification)
	{
		case noType			: myResult="none"; break;
		case errorType		: myResult="error"; break;
		case intType		: myResult="int"; break;
		case arrayType		: myResult="array"; break;
		case intArrayType	: myResult="int[]"; break;
		case opPlus			: myResult="+"; break;
		case opMinus		: myResult="-"; break;
		case opMult			: myResult="*"; break;
		case opDiv			: myResult=":"; break;
		case opLess	 		: myResult="<"; break;
		case opUnEqual		: myResult="!"; break;
		case opAnd			: myResult="&"; break;
		case opEqual		: myResult="="; break;

		default: myResult = "unknown"; break;
	}
	return myResult;
}

#pragma once

#include <sstream>
#include "../ParserConstant/ParserConstant.h"

#define PARSER

//Anzahl der maximalen Tokens im TokenArray des Parsers
static const int MAX_POSSIBLE_TOKENS		=	1000000;
//Maximale Anzahl von Kinderknoten beim Aufbau des Baums
static const int MAX_CHILD_NODES			=   100;


class ParserConstant {

public:

	enum NodeType {
		NODE_ROOT		=	0,


		NODE_ERROR		=	2,
		NODE_EMPTY		=	3,

		NODE_PROG		=	4,
		NODE_DECLS		=	5,
		NODE_DECL		=	6,
		NODE_ARRAY		=	7,
		NODE_STATEMENTS	=	8,
		NODE_STATEMENT	=	9,
		NODE_EXP		=	10,
		NODE_EXP2		=	11,
		NODE_INDEX		=	12,
		NODE_OP_EXP		=	13,
		NODE_OP			=	14,

		NODE_IDENTIFIER	=	15,
		NODE_KEYWORD	=	16
	};

	enum Typification {
		noType			= 	0,
		errorType		= 	1,

		intType			=	2,
		intArrayType	=	3,
		arrayType		=	4,

		opPlus			=	5,
		opMinus			=	6,
		opMult			=	7,
		opDiv			=	8,
		opLess			=	9,
		opGreater		=	10,
		opEqual			=	11,
		opUnEqual		=	12,
		opAnd			=	13,

		unknownType		= 14
	};
	
	ParserConstant();
	
	
	static std::string nodeTypeAsString(NodeType myNodeType);
	static std::string typificationAsString(Typification myTypification);
	
};

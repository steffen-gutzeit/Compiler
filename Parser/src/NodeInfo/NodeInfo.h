#pragma once

#include "../../../Token/src/Token.h"
#include <iostream>

#include "../ParserConstant/ParserConstant.h"


class NodeInfo
{
	
public:
	NodeInfo(ParserConstant::NodeType nodeType = ParserConstant::NODE_EMPTY,
			Token *token = NULL,
			ParserConstant::Typification typification = ParserConstant::noType);
	
	void setNodeType(ParserConstant::NodeType nodeType);
	void setToken(Token *token);
	void setTypification(ParserConstant::Typification typification);
	
	ParserConstant::NodeType getNodeType();
	Token *getToken();
	ParserConstant::Typification getTypification();
	char* getLexem();

private:
	ParserConstant::NodeType nodeType;
	Token *token;
	ParserConstant::Typification typification;
};

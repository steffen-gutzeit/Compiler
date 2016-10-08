/*
 *  NodeInfo.h
 *  sysprog
 *
 *  Created by Peter Schneider on 21.02.10.
 *  Copyright 2010 Schneider Medien Services. All rights reserved.
 *
 */
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
	uint16_t getLexemAsInteger();

private:
	ParserConstant::NodeType nodeType;
	Token *token;
	ParserConstant::Typification typification;
};

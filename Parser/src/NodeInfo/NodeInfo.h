/*
 *  NodeInfo.h
 *  sysprog
 *
 *  Created by Peter Schneider on 21.02.10.
 *  Copyright 2010 Schneider Medien Services. All rights reserved.
 *
 */
#pragma once

#include "../Constant/parserConst.h"
#include "../../../Token/src/Token.h"
#include <iostream>


class NodeInfo
{
	
public:
	NodeInfo(NodeType nodeType = NODE_EMPTY, Token *token = NULL, Typification typification = TYPIFICATION_NONE);
	
	void setNodeType(NodeType nodeType);
	void setToken(Token *token);
	void setTypification(Typification typification);
	
	NodeType getNodeType();
	Token *getToken();
	Typification getTypification();

private:
	NodeType nodeType;
	Token *token;
	Typification typification;
};

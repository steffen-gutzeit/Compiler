/*
 *  NodeInfo.cpp
 *  sysprog
 *
 *  Created by Peter Schneider on 21.02.10.
 *  Copyright 2010 Schneider Medien Services. All rights reserved.
 *
 */

#include "NodeInfo.h"


NodeInfo::NodeInfo(NodeType nodeType, Token *token, Typification typification)
{
	this->nodeType = nodeType;
	this->token = token;
	this->typification = typification;
}
	
void NodeInfo::setNodeType(NodeType nodeType) {
	this->nodeType = nodeType;
}

void NodeInfo::setToken(Token *token) {
	this->token = token;
}

void NodeInfo::setTypification(Typification typification) {
	this->typification = typification;
}

NodeType NodeInfo::getNodeType() {
	return this->nodeType;
}

Token *NodeInfo::getToken() {
	return this->token;
}

Typification NodeInfo::getTypification() {
	return this->typification;
}

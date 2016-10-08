/*
 *  NodeInfo.cpp
 *  sysprog
 *
 *  Created by Peter Schneider on 21.02.10.
 *  Copyright 2010 Schneider Medien Services. All rights reserved.
 *
 */

#include "NodeInfo.h"


NodeInfo::NodeInfo(ParserConstant::NodeType nodeType,
		Token *token, ParserConstant::Typification typification)
{
	this->nodeType = nodeType;
	this->token = token;
	this->typification = typification;
}
	
void NodeInfo::setNodeType(ParserConstant::NodeType nodeType) {
	this->nodeType = nodeType;
}

void NodeInfo::setToken(Token *token) {
	this->token = token;
}

void NodeInfo::setTypification(ParserConstant::Typification typification) {
	this->typification = typification;
}

ParserConstant::NodeType NodeInfo::getNodeType() {
	return this->nodeType;
}

Token *NodeInfo::getToken() {
	return this->token;
}

char *NodeInfo::getLexem(){

	return this->token->getLexem();
}

ParserConstant::Typification NodeInfo::getTypification() {
	return this->typification;
}

uint16_t NodeInfo::getLexemAsInteger() {
	//TODO
	return 4711;
}

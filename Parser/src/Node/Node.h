#pragma once
#include "../NodeInfo/NodeInfo.h"
#include <iostream>

#include "../ParserConstant/ParserConstant.h"

class Node
{
	
public:
	Node(NodeInfo *nodeInfo);

	NodeInfo *getNodeInfo();
	void setNodeInfo(NodeInfo *nodeInfo);

	uint16_t getChildrenCount();
	Node *addChild(Node* myChild);
	Node *getChild(int which);
	
	void print();
	
	bool isLeave();
	
private:
	NodeInfo *nodeInfo;

	uint16_t childrenCount;
	Node *childNodes[MAX_CHILD_NODES];
	
};

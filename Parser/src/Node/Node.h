#pragma once
#include "../Constant/parserConst.h"
#include "../NodeInfo/NodeInfo.h"
#include <iostream>

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

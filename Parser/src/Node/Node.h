#pragma once
#include "../Constant/parserConst.h"
#include "../NodeInfo/NodeInfo.h"
#include <iostream>

class Node
{
	
public:
	Node(NodeInfo *myInfo);

	NodeInfo *getInfo();
	void setInfo(NodeInfo *myInfo);

	uint16_t getChildrenCount();
	Node *addChild(Node* myChild);
	Node *getChild(int which);
	
	void print();
	
	bool isLeave();
	
private:
	NodeInfo *myInfo;

	uint16_t childrenCount;
	Node *childNodes[MAX_CHILD_NODES];
	
};

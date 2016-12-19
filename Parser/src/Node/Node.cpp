#include "Node.h"

/*
 * Konstruktor
 */
Node::Node(NodeInfo *nodeInfo)
{
	for(int x = 0; x < MAX_CHILD_NODES; x++){
		childNodes[x] = NULL;
	}
	this->nodeInfo = nodeInfo;
	this->childrenCount = 0;
}

/*
 * Destruktor
 */
Node::~Node(){
	delete nodeInfo;
}

/*
 * Gibt die aktuelle NodeInfo zurück
 */
NodeInfo *Node::getNodeInfo()
{
	return nodeInfo;
}

/*
 * Setzt die aktuelle NodeInfo
 */
void Node::setNodeInfo(NodeInfo *nodeInfo)
{
	this->nodeInfo = nodeInfo;
}

/*
 * Gibt die Anzahl der Kinderknoten zurück
 */
uint16_t Node::getChildrenCount()
{
	return childrenCount;
}

/*
 * Fügt einen Kinderknoten zum aktuellen Knoten
 */
Node *Node::addChild(Node* myChild)
{
	childNodes[childrenCount] = myChild;
	childrenCount++;
	return myChild;
}

/*
 * Gibt den Kinderknoten zurück
 */
Node *Node::getChild(int which)
{
	return childNodes[which];
}


/*
 * LinkedList_test.cpp
 *
 *  Created on: 27.10.2014
 *      Author: root0r
 */

#include "LinkedList.h"

 int main() {
	 LinkedList *l = new LinkedList();

	 l->createList("abc");
	 l->add("d");
	 l->add("e");

	 l->printListValues();
	 return 0;
 }

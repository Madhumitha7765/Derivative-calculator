/*
 * LinkedList.h
 *
 *  Created on: Nov 2, 2017
 *      Author: luiso
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include "Node.h"
#include <string>

using namespace std;


class LinkedList
{

private:
	Node *head;
	int size;


public:
	//default constructor
	LinkedList();

	//constructor with head created
	LinkedList(Node *&head);
	//returns the head pointer
	const Node* getHead();

	//print it recursively
	void print();

	//adds a node
	void addNode(Node *node);

	//adds a node by order
	void addNodeByOrder(Node *node);

	//delete node at a specified location
	void deleteNode(int index);

	//returns the node at a specified location
	Node* getNode(int index);

	//sets the head to a received node
	void setHead(Node *node);

	//destructor for the linkedlist
	//calls the deleteList function
	//which will delete the list recursively
	virtual ~LinkedList();

	void deleteList(Node *head);

	//returns the size of the list
	int getSize() { return size; }
};

#endif /* LINKEDLIST_H_ */

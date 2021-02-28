/*
 * LinkedList.cpp
 *
 *  Created on: Nov 2, 2017
 *      Author: luiso
 */
#include "Node.h"
#include "LinkedList.h"
#include <iostream>

using namespace std;

LinkedList::LinkedList()
{
	head = nullptr;
	size = 0;
}

LinkedList::LinkedList(Node *&h)
{
	head = h;
	size = 1;
}

//make it recursive, by using a different function
LinkedList::~LinkedList()
{
	//deleteList(head);
	Node *cur = head;
	while(cur)
	{
		Node *hold = cur;
		cur = cur->getNext();
		delete hold;

	}
	// TODO Auto-generated destructor stub
}

//recursively deletes the list
void LinkedList::deleteList(Node *node)
{
	//if the next node doesn't exist
	//aka if you're at the end
	/*if(!node->getNext())
	{
		delete node;
	}
	else
	{
		//if the next one exists
		//call the list to delete the next one
		deleteList(node->getNext());
	}*/
}

void LinkedList::addNode(Node *node)
{
	//if the head is null, set it to be head
	//otherwise add it to the end of the list
	if(!head)
	{
			head = node;
	}
	else
	{
		Node *hold = head;
		//continues until the next node is a nullptr
		while(hold->getNext())
		{
			hold = hold->getNext();
		}

		hold->setNext(node);
	}
}

//adds the node to the listby order
void LinkedList::addNodeByOrder(Node *node)
{
	//copy the received node
	//to a new one with a new address and memory location

	//if the head is null(the list is empty)
	if(!head)
	{
		head = node;
	}
	//if the node comes before head in priority
	//based on degree
	else if(head->getExponent()<node->getExponent())
	{
		node->setNext(head);
		head = node;
	}
	//if the node belongs somewhere after the head node
	else
	{
		Node *hold = head;

		//while the next node exist
		//continue moving the node to the next spot
		//when it stops the next value will be end of the list where
		//the node will be added
		while(hold->getNext())
		{
			hold = hold->getNext();
		}

		hold->setNext(node);
	}


	size++;
	//copy the new node to a new class
	//then add it to the list
}

//sets head to a received node
void LinkedList::setHead(Node *node)
{
	head = node;
}

//prints out the contents of the list
void LinkedList::print()
{
	Node* hold = head;

	while(hold)
	{
		//if the function is not at trig function
		if(hold->getTrig()=="none")
		{
			//if it's a constant
			if(hold->getExponent()==0)
			{
				cout<<hold->getCoefficient()<<" ";
			}
			//if it's a variable
			else if(hold->getExponent()==1)
			{
				cout<<hold->getCoefficient()<<"x ";
			}
			//if it's an exponential
			else
			{
				cout<<hold->getCoefficient()<<"x^"<<hold->getExponent()<<" ";
			}
		}
		//if it's a trig
		else
		{
			cout<<hold->getCoefficient()<<hold->getTrig()<<" ";
		}

		hold = hold->getNext();

	}
	cout<<endl<<endl;
}

//returns a constant form of  current head pointer
//so they can't change it outside the class
const Node* LinkedList::getHead()
{
	return head;
}

void LinkedList::deleteNode(int index)
{
	//the index is out of bounds
	if(index>=size||index<0)
	{
		return;
	}
	//otherwise find and delete the index

	//if the head is to be deleted
	if(index==0)
	{
		Node *hold = head;
		head = head->getNext();
		delete hold;
	}
	//if the node to delete is somwhere past the head
	else
	{
		Node *hold = head;
		int counter = 0;
		//continues until the next one is the one to be deleted
		while(hold->getNext()&&counter+1<index)
		{
			hold = hold->getNext();
			counter++;
		}
		Node *temp = hold->getNext();
		//sets the next one to the one after temp
		hold->setNext(temp->getNext());
		//deletes temp

		delete temp;
	}


	//by this point hold, contains the node to delete

}

Node* LinkedList::getNode(int index)
{
	if(index==0)
	{
		return head;
	}
	else
	{
		int counter = 0;
		Node* hold = head;

		while(counter<index)
		{
			counter++;
			hold = hold->getNext();

		}
		return hold;
	}


}

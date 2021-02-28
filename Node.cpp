/*
 * Node.cpp
 *
 *  Created on: Nov 2, 2017
 *      Author: luiso
 */

#include "Node.h"
#include <string>
#include <iostream>
#include <fstream>


using namespace std;

//default constructor
Node::Node()
{
	coefficient = 0;
	exponent = 0;

	trig = "none";
	angle = "none";

	angle_coefficient = 0;

	next = nullptr;
}
//constructor for constants
Node::Node(int c)
{
	coefficient = c;
	exponent = 0;

	trig = "none";
	angle = "none";

	angle_coefficient = 0;

	next = nullptr;
}
//constructor for linear x-variables
Node::Node(int c, int e)
{

	coefficient = c;
	exponent = e;

	trig = "none";
	angle = "none";

	angle_coefficient = 0;

	next = nullptr;

}
//constructor for trig functions
Node::Node(int c, string t, string a, int angle_c)
{
	coefficient = c;
	exponent = 0;

	trig = t;
	angle = a;

	angle_coefficient = angle_c;

	next = nullptr;
}
//destructor
Node::~Node()
{
	// TODO Auto-generated destructor stub
}

//accessors functions
int Node::getCoefficient()
{
	return coefficient;
}
int Node::getExponent()
{
	return exponent;
}
string Node::getTrig()
{
	return trig;
}
string Node::getAngle()
{
	return angle;
}
int Node::getAngleCoefficient()
{
	return angle_coefficient;
}

void Node::printNode(ofstream &output)
{

			if(trig=="none")
			{
				//if it's a constant
				if(exponent==0)
				{
					output<<coefficient;
				}
				//if it's a variable
				else if(exponent==1)
				{
					output<<coefficient<<"x";
				}
				//if it's an exponential
				else
				{
					output<<coefficient<<"x^"<<exponent;
				}
			}
			//if it's a trig
			else
			{
				output<<coefficient<<trig;
			}

}

//mutators
void Node::setCoefficient(int c)
{
	coefficient = c;
}
void Node::setExponent(int e)
{
	exponent = e;
}
void Node::setTrig(string t)
{
	trig = t;
}
void Node::setAngle(string a)
{
	angle = a;
}
void Node::setAngleCoefficient(int ac)
{
	angle_coefficient = ac;
}

Node* Node::getNext()
{
	return next;
}

void Node::setNext(Node *node)
{
	next = node;
}

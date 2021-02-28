/*
 * Node.h
 *
 *  Created on: Nov 2, 2017
 *      Author: luiso
 */

#ifndef NODE_H_
#define NODE_H_

#include <string>
#include <fstream>

using namespace std;


class Node
{

	private:
		float coefficient;
		int exponent;
		string trig;
		string angle;
		int angle_coefficient;
		Node *next;

	public:
		Node();
		Node(int coefficient);
		Node(int coefficient, int exponent);
		Node(int coefficient, string trig, string angle, int angle_coefficient);

		virtual ~Node();

		//accessors functions
		int getCoefficient();
		int getExponent();
		string getTrig();
		string getAngle();
		int getAngleCoefficient();
		Node* getNext();

		//mutators
		void setCoefficient(int coefficient);
		void setExponent(int exponent);
		void setTrig(string trig);
		void setAngle(string angle);
		void setAngleCoefficient(int angle_coe);
		void setNext(Node *node);
		void printNode(ofstream &op);
};

#endif /* NODE_H_ */

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <cctype>


//custom classes
#include "Node.h"
#include "LinkedList.h"


using namespace std;

//recieves an integer
//returns whether that integer is a negative
bool isNegative(int coef)
{
	if(coef<0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Receives a node
//Changes it's components to reflect it's derivative
void derive(Node *&node)
{

	if(node->getTrig()!="none")
	{
		//it's a trig equation
		//if the first character in the trig is 's'
		//the equation is a sin function
		if(node->getTrig()[0] == 's')
		{
			//derivative of sinx = cosx
			node->setCoefficient(node->getCoefficient()*node->getAngleCoefficient());
			node->setTrig("cos"+node->getAngle());
		}

		//if the first character in the trig is 'c'
		//the equation is a cosine function
		else if(node->getTrig()[0] == 'c')
		{
			//derivative of cosx = -sinx
			node->setCoefficient(node->getCoefficient()*node->getAngleCoefficient()*-1);
			node->setTrig("sin"+node->getAngle());
		}

		//if none of the above are true, then it's a tangent function
		else
		{
			//derivative of tanx = sec^2x
			node->setCoefficient(node->getCoefficient()*node->getAngleCoefficient());
			node->setTrig("sec^2 "+node->getAngle());
		}


	}
	else if(node->getExponent()!=0)
	{
		//it's a x variable
		//multiplies the coefficient by the exponent
		node->setCoefficient(node->getCoefficient()*node->getExponent());

		//substracts the exponent by 1
		node->setExponent(node->getExponent()-1);
	}
	else
	{
		//it's a constant
		node->setCoefficient(0);
		node->setExponent(0);
	}


}

//receives a line
//returns the number of variables in the line
int getVariables(string line)
{
	int variables = 0;
	int size = line.length();
	for(int x = 1; x<size;x++)
	{
		if((line[x]=='+'||line[x]=='-')&&(isdigit(line[x-1])||line[x-1]=='x'))
		{
			variables++;
		}
	}


	return variables+1;
}

//receives a line
//returns the line without any spaces
string removeSpaces(string line)
{
	//goes through each space in the line
	//if the character at location x is a space
	//delete it
	int size = line.length();
	for(int x =0;x<size;x++)
	{
		if(line[x] == ' ')
		{
			line.erase(x,1);
		}
	}

	return line;
}

//receives the address of the list
//derives each node in the list
void deriveList(LinkedList *&list)
{
	for(int x = 0;x<list->getSize();x++)
	{
		Node *node = list->getNode(x);
		derive(node);
	}
}

//It will receive the already derived functions and the filename to output the changes to
//it will append the list to the text file
void outputDerivative(LinkedList *list, string filename)
{
	//derives the list
	deriveList(list);
	//creates the output stream
	//with the given filename
	ofstream output;
	output.open(filename, ofstream::out | ofstream::app);
	if(output.fail())
	{
		cout<<"Fail in printing derivative."<<endl;
	}

	//goes through each node in the list; defaults to the plus sign, and checks coefficient for negatives
	for(int x = 0;x<list->getSize();x++)
	{
		//print out the derivative
		//Node a = list.getNode(x)
		Node *node = list->getNode(x);
		node->printNode(output);

		//if it's not the last node
		if(x+1<list->getSize())
		{
			//if the next coefficent is negative, remove the negative and simply add a - between them
			//otherwise add a +
			//grabs the next node
			Node *next = list->getNode(x+1);

			//if the next node is negative
			//then make the coefficient positive and put minus in between
			if(next->getCoefficient()<0)
			{
				output<<" - ";
				next->setCoefficient(next->getCoefficient()*-1);
			}

			else
			{
				output<<" + ";
			}

		}

	}

	output<<"\n";

	//

}
int main()
{
	//file streams
	ifstream input("functions.txt");
	string filename = "derive.txt";

	string line;
	getline(input,line);

	//while there's still a function to derive
	do
	{
		//dynamically makes the lists
		LinkedList *list = new LinkedList();

		//removes the spaces from the line and
		//gets the number of variables/constant in the function
	   line = removeSpaces(line);
	   int variables = getVariables(line);


	   // goes through each variable in the function
	   for(int x =0;x<variables;x++)
	   {
		   Node *newNode;

		   //gets the variable and it's componenets
		   int index = line.find_first_of("+-");
		   if(line[index-1]=='^'||line[0]=='-'||line[0]=='+')
		   {
			   index = line.find_first_of("+-",index+1);
		   }

		   string newline = line.substr(0,index);

		   //finds what type of variable it is
		   int innerIndex = newline.find_first_of("scxt");
		   //components of a Node
		   int coefficient = 0;
		   int exponent = 0;

		   //If the there's no variable, it means
		   //it's just a constant
		   if(innerIndex == -1)
		   {
			   coefficient = stoi(newline.substr(0,newline.length()));
			   exponent = 0;

			   newNode = new Node(coefficient, exponent);

			   //erases the part of the line that has already been processed.
			   line.erase(0,index+1);

			   //adds newNode to the linked list
			   list->addNodeByOrder(newNode);

			   continue;
		   }

		  //if there is an X variable
		   //if the variable is the first character, the coefficient is
		   //assumed to be 1
		   if(innerIndex==0)
		   {
			   coefficient = 1;
		   }
		   //if the first character is substraction
		   //and the second was the function
		   else if(newline[0]=='-'&&innerIndex==1)
		   {
			   coefficient = -1;
		   }
		   //if the first character is addition
		   //and the second was the function
		   else if(newline[0]=='+'&&innerIndex==1)
		   {
			   coefficient = 1;
		   }
		   //takes the full coefficient
		   else
		   {
			   coefficient = stoi(newline.substr(0,innerIndex));
		   }

		   //if the function at hand is part of a trig identity
		  if(newline[innerIndex]=='s'||newline[innerIndex]=='c'||newline[innerIndex] == 't')
		   {

			   //takes the trig identity an angle out of the newline
			   string trig = newline.substr(innerIndex,newline.length());
			   string angle = newline.substr(innerIndex+3,newline.length());

			   //takes the coefficient that affects the angle X
			   //defaults to 1
			   int angleIndex = angle.find_first_of("x");
			   int angle_coefficient = 1;

			   //if the angle has a coefficient
			   //then grab it
			   if(angleIndex!=0)
			   {
				  angle_coefficient = stoi(angle.substr(0,angleIndex));
			   }

			   //creates the Node with the aforementioned information and continues
			   //the loop to the next variable

			  newNode = new Node(coefficient,trig, angle, angle_coefficient);

		   }

		   //if the function is a regular X variable
		   else
		   {
			   //finds the index, if any, of the exponential mark
			   int exponentIndex = newline.find_first_of("^");

			   //if there's no exponent mark
			   //it means it's a basic X-variable
			   if(exponentIndex == -1)
			   {
				   exponent = 1;

				   newNode = new Node(coefficient, exponent);
			   }

			   //if it does find an exponent
			   else
			   {
				   //grabs the exponent from the function
				   exponent = stoi(newline.substr(exponentIndex+1,newline.length()));

				   //creates a node with the receieved exponent
				   newNode = new Node(coefficient, exponent);

			   }

		   }

		   //erases the part of the line that has already been processed.
		   line.erase(0,index);

		   //adds newNode to the linked list
		   list->addNodeByOrder(newNode);


	   }
	   //end of for loop

	   //by this point the list has been created
	   //output the derivative

	   //add a method to print the list
	  outputDerivative(list,filename);
	   //deletes the list, emptying out the functions
	   //to be recreated
	   delete list;
	   getline(input,line);

	}while(input);


	return 0;
}

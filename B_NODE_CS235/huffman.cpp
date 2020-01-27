/***********************************************************************
 * Module:
 *    Week 08, Huffman
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name>
 * Summary:
 *    This program will implement the huffman() function
 ************************************************************************/

#include <iostream>        // for CIN and COUT
#include <fstream>         // for IFSTREAM
#include <cassert>         // for ASSERT
#include <string>		   // for STRING: binary representation of codes
#include <sstream>
#include "bnode.h"         // for BINARY_NODE class definition
#include "vector.h"        // for VECTOR container
#include "pair.h"          // for PAIR container
#include "huffman.h"       // for HUFFMAN() prototype

using std::cout;
using std::cin;
using std::ifstream;
using std::endl;
using std::string;
using std::bad_alloc;
using namespace custom;

/*******************************************
 * HUFFMAN
 * Driver program to exercise the huffman generation code
 *******************************************/
void huffman(const string & fileName)
{
	std::ifstream in(fileName);
	//read the file and store all to a vector
	//vector= new vector<pair<double, string>>;//create a vector of pairs
	vector<pair<double, string>> myvector;
	std::string str;
	//
	if (in.is_open())
	{
		// Read the next line from File until it reaches the end.
		while (std::getline(in, str))
		{
			// Line contains string of length > 0 then save it in vector
			if (str.size() > 0)
			{
				string buf;// Have a buffer string
				std::stringstream ss(str); // Insert the string into a stream
				custom::vector<std::string> tokens; 
				while (ss >> buf)
				{
					tokens.push_back(buf);
				}
				double value=atof(tokens[1].c_str());
				pair<double, string> mypair(value, tokens[0]);
				myvector.push_back(mypair);
			}

		}
		in.close();
	}
	//put all the pairs in the vector to
	vector<BNode<pair<double, string>>> myNodeVector;
	for (int i = 0; i < myvector.size(); i++)
	{
		BNode < pair<double, string>> myNode(myvector[i]);
		myNodeVector.push_back(myNode);
	}
	
	
	//generate the codes
	vector<BNode<pair<double, string>>> tree = makeTrees(myNodeVector);
	BNode<pair<double, string>> *rootNode = &tree[0];
	vector<int> path;
	//string path = "";
	for (int i = 0; i < myvector.size(); i++)
	{
		printCodes(rootNode, path, myvector[i]);
	}
   return;
}
/*******************************************
 * MAKE TREES
 * makes a binary tree out of a container for huffman codes recursively
 * PARAM: takes a vector of huffman codes
 *        (frequency, value)
 * RETURN: returns a vector with the root for the tree
 *******************************************/
vector<BNode<pair<double,string>>> makeTrees(vector<BNode<pair<double,string>>> nodeVector) 
{
	// the vector that will be returned
	vector<BNode<pair<double, string>>> newNodeVector;
	
	if (nodeVector.size()>1)
	{
		//insertion sort the vector
		int i;
		BNode<pair<double, string>> key;
		int j;
		for (i = 1; i < nodeVector.size(); i++)
		{
			key = nodeVector[i];
			j = i - 1;
			while (j >= 0 && nodeVector[j].data > key.data)
			{
				nodeVector[j + 1] = nodeVector[j];
				j = j - 1;
			}
			nodeVector[j + 1] = key;

		}
		////debug vector
		//cout << std::endl;
		//cout << "sorted array ";
		//for (int i = 0; i < nodeVector.size(); i++)
		//{
		//	cout << nodeVector[i].data << ",";
		//}
		//cout << std::endl;
		////debug vector

		//try to make the nodes with the Alpha value become leafs
		//so we give them priority if they are equal to one of the 2 smallest nodes
		int k = 2;
		while (k < nodeVector.size() && nodeVector[0].data <= nodeVector[k].data)
		{
			
			if (nodeVector[0].data==nodeVector[k].data && nodeVector[k].data.second!="" && nodeVector[0].data.second == "")
			{
				BNode<pair<double, string>> temp(nodeVector[0]); 
				nodeVector[0].operator=(nodeVector[k]);
				nodeVector[k].operator=(temp);
				break;
			}
			k++;
		}
		int m = 2;
		while (m < nodeVector.size() && nodeVector[1].data <= nodeVector[m].data)
		{

			if (nodeVector[1].data == nodeVector[m].data && nodeVector[m].data.second != "" && nodeVector[1].data.second=="")
			{
				BNode<pair<double, string>> temp(nodeVector[1]);
				nodeVector[1].operator=(nodeVector[m]);
				nodeVector[m].operator=(temp);
				break;
			}
			m++;
		}
		
		
		////debug vector
		//cout << "sorted after changes array ";
		//for (int i = 0; i < nodeVector.size(); i++)
		//{
		//	cout << nodeVector[i].data << ",";
		//}
		//cout << std::endl;
		////debug vector

		//take the first 2 elements and combine
		BNode<pair<double, string>> *node=new BNode<pair<double, string>>(pair<double,string>(nodeVector[0].data.first + nodeVector[1].data.first , string("")));
		BNode<pair<double, string>> *firstNode = new BNode<pair<double, string>>(nodeVector[0]);
		BNode<pair<double, string>> *secondNode= new BNode<pair<double, string>>(nodeVector[1]);
		

		//determine weather to insert at the left or at the right
		if (nodeVector[0].data > nodeVector[1].data)
		{
			addRight(node, firstNode);
			addLeft(node,secondNode);
		}
		else if (nodeVector[0].data <= nodeVector[1].data)
		{
			addRight(node,secondNode);
			addLeft(node,firstNode);
		}
		
		//insert into a new vector
		BNode<pair<double, string>>tempNode;

		for (int i = 0; i < nodeVector.size(); i++)
		{
			if (i==0)
			{
				tempNode = *node;
				newNodeVector.push_back(tempNode);
				i++;
			}
			else
			{
				tempNode = nodeVector[i];
				newNodeVector.push_back(tempNode);
			}
		}
		////debug vector
		//cout << std::endl;
		//cout << "after inserting to the new vector ";
		//for (int i = 0; i < newNodeVector.size(); i++)
		//{
		//	cout << newNodeVector[i].data << ",";
		//}
		//cout << std::endl;
		////debug vector
	}
	else
	{
		return nodeVector;
	}
	
	
	//recursive call
	return makeTrees(newNodeVector);
	//return newNodeVector;
}
/*******************************************
 * PRINT CODES
 * prints a binary code for the parameters given
 * PARAM: takes the root of a tree, a empty vector 
 *        to store the path, the node we need the binary for
 * RETURN: void
 *******************************************/
void printCodes(BNode<pair<double, string>>* root, vector<int> path, pair<double, string> key)
{
	if (root->pLeft)
	{
		path.push_back(0);
		printCodes(root->pLeft, path, key);
		path[path.size() - 1] = 2;
		//cout << "see when this code is executed";
		
	}
	if (root->pRight)
	{
		path.push_back(1);
		printCodes(root->pRight, path, key);
		
	}
	if (!root->pLeft && !root->pRight)
	{
		if (root->data == key && root->data.second == key.second)
		{
			string result="";
			for (int i = 0; i < path.size(); i++)
			{
				if (path[i]!=2)
				{
					result += std::to_string(path[i]);
				}				

			}
			cout << root->data.second << " = " << result << std::endl;
			//return;
		}
	}
}

////debug vector
//for (int i = 0; i < myNodeVector.size(); i++)
//{
//	cout << myNodeVector[i];
//}
////debug vector
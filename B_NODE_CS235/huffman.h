/***********************************************************************
 * Module:
 *    Week 08, Huffman
 *    Brother Helfrich, CS 235
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This program will implement the huffman() function
 ************************************************************************/

#ifndef HUFFMAN_H
#define HUFFMAN_H
#include "vector.h"
#include "pair.h"
#include "bnode.h"
#include <string>
void huffman(const std::string & fileName);
custom::vector<BNode<custom::pair<double, std::string>>> makeTrees(custom::vector<BNode<custom::pair<double, std::string>>> nodeVector);
void printCodes(BNode<custom::pair<double, std::string>>* root,custom::vector<int> path,custom::pair<double, std::string> key);

#endif // HUFFMAN_h

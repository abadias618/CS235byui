###############################################################
# Program:
#     Assignment 08, Binary Tree
#     Brother kirby, CS235
# Author:
#     Abdias Baldiviezo & Kevin Hisel
# Summary:
#     displays a binary representation of the path to a node (huffman codes)
#	  uses the bnode class which is made to build binary trees
# Time:
#	  Pair programming 0hrs
#	  Abdias 20hours 
# Most difficult thing:
#     All the huffman codes part was very hard for me, 
#	  bulding the tree and figuring out the recursion for the binary codes specially
###############################################################

##############################################################
# The main rule
##############################################################
a.out: assignment08.o huffman.o 
	g++ -o a.out assignment08.o huffman.o -g
	tar -cf assignment08.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment08.o : the driver program
#      huffman.o      : the logic for the huffman code program
##############################################################
assignment08.o: bnode.h huffman.h assignment08.cpp
	g++ -c assignment08.cpp -g

huffman.o: bnode.h huffman.h huffman.cpp vector.h pair.h
	g++ -c huffman.cpp -g



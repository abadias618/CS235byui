###############################################################
# Program:
#     Assignment 09, Binary Search Tree
#     Brother kirby, CS235
# Author:
#     Abdias Baldiviezo & Kevin Hisel
# Summary:
#     There were 3 steps that were really hard, 
#	  First, getting all the nested classes to compile properly
#	  Second, the balancing aspect of the BST i found more cases than the ones on the 
#	  (don't know if its because i wasn't abstract enough to reduce it to only a few cases)
#	  Third, getting the insert and erase functions to work properly i found more cases than the book 
#	  (don't know if its because i wasn't abstract enough to reduce it to only a few cases)
#
# Time:
#     Abdias Baldiviezo -> 30 hours
###############################################################

##############################################################
# The main rule
##############################################################
a.out: assignment09.o
	g++ -o a.out assignment09.o -g
	tar -cf assignment09.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment09.o     : the driver program
##############################################################
assignment09.o: bst.h assignment09.cpp
	g++ -c assignment09.cpp -g


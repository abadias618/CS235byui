###############################################################
# Program:
#     Assignment 06, NODE
#     Brother Kirby, CS235
# Author:
#     Abdias Baldiviezo & Kevin Hisel
# Summary:
#     this program will implement the node structure in the 
#	  form of a doubly linked list
# Coding Time:
#     Pair programming: 0 hours
#	  Abdias: 15 hours
# The most difficult part:
#	  Abdias: getting the insertion sort to work
#             I didn't know that std::string < and > worked to compare
#             by lexicographical value, spent at least 10 hours on that
###############################################################

##############################################################
# The main rule
##############################################################
a.out: node.h assignment06.o 
	g++ -o a.out assignment06.o -g
	tar -cf assignment06.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment06.o      : the driver program
#      <anything else?>
##############################################################
assignment06.o: node.h assignment06.cpp sortInsertion.h
	g++ -c assignment06.cpp -g 

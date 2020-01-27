###############################################################
# Program:
#     Assignment 01, Vector
#     Brother Jon Kirby, CS235 Section 06
# Author:
#     Abdias Baldiviezo
# Summary:
#     implements the std::vector class through a template class,
#	  with an iterator as a nested class. And an array as the 
#     main container.
# Time:
#     20 hours
###############################################################

##############################################################
# The main rule
##############################################################
a.out: vector.h assignment01.o
	g++ -o a.out assignment01.o
	tar -cf assignment01.tar vector.h assignment01.cpp makefile

##############################################################
# The individual components
#      assignment01.o     : the driver program
##############################################################
assignment01.o: vector.h assignment01.cpp
	g++ -c assignment01.cpp


###############################################################
# Program:
#     Assignment 07, LIST
#     Brother kirby, CS235
# Author:
#     Abdias Baldiviezo & Kevin Hisel
# Summary:
#     imitating the std::list and an application with fibonacci numbers
# Hours: 20
# Hardest Part: 
#	Abdias: It was very hard to figure all the special cases
#			in the fibonacci numbers like repetead nodes in different
#			parts and knowing how to keep track of those.
#			Also getting all the classes in list.h to work correctly
###############################################################

##############################################################
# The main rule
##############################################################
a.out: list.h assignment07.o fibonacci.o wholeNumber.o
	g++ -o a.out assignment07.o fibonacci.o wholeNumber.o -g
	tar -cf assignment07.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment07.o : the driver program
#      fibonacci.o    : the logic for the fibonacci-generating function
#      
##############################################################
assignment07.o: list.h assignment07.cpp
	g++ -c assignment07.cpp -g

fibonacci.o: fibonacci.h fibonacci.cpp list.h
	g++ -c fibonacci.cpp -g

#wholeNumber.o: wholeNumber.h wholeNumber.cpp list.h
#	g++ -c wholeNumber.cpp -g


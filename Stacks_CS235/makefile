###############################################################
# Program:
#     Assignment 02, STACK
#     Brother kirby, CS235
# Author:
#     Abdias Baldiviezo & Kevin Hisel
# Summary:
#     Represents a stack and also an implementation of a stack
#     to convert infix to postfix and postfix to assembly
# Time:
#     30 hours
# Hardest Part:
#     Allocating the memory correctly for the stack container to work
#	  Also getting the assembly to work properly in all cases
###############################################################

##############################################################
# The main rule
##############################################################
a.out: stack.h assignment02.o infix.o 
	g++ -o a.out assignment02.o infix.o 
	tar -cf assignment02.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment02.o : the driver program
#      infix.o        : the logic for the infix --> postfix program
##############################################################
assignment02.o: stack.h infix.h assignment02.cpp
	g++ -c assignment02.cpp  

infix.o: stack.h infix.h infix.cpp
	g++ -c infix.cpp 


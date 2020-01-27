###############################################################
# Program:
#     Assignment 03, QUEUE
#     Brother kirby, CS235
# Author:
#     <Abdias Baldiviezo, Kevin Hisel>
# Summary:
#     holds a template class for a circular queue
# Time:
#     30 hours
# Most Difficult part:
#	  The resize function, getting it  to work properly.
###############################################################

##############################################################
# The main rule
##############################################################
a.out: queue.h assignment03.o dollars.o stock.o
	g++ -o a.out assignment03.o dollars.o stock.o 
	tar -cf assignment03.tar *.h *.cpp makefile 

dollarsTest: dollars.o dollarsTest.cpp
	g++ -o dollarsTest dollars.o dollarsTest.cpp 

##############################################################
# The individual components
#      assignment03.o : the driver program
#      dollars.o      : the Dollars class
#      stock.o        : the logic for the stock program
##############################################################
assignment03.o: queue.h assignment03.cpp
	g++ -c assignment03.cpp 

dollars.o: dollars.h dollars.cpp
	g++ -c dollars.cpp 

stock.o: stock.h stock.cpp queue.h
	g++ -c stock.cpp 

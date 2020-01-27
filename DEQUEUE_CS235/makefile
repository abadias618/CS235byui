###############################################################
# Program:
#     Assignment 04, DEQUE
#     Brother kirby, CS235
# Author:
#     Abdias Baldiviezo & Kevin Hisel
# Summary:
#     Contains the notion of a queue which can be accessed by either side
#	  , also conatins a program to implement the deque as a customer support
#	  ticketing service.
# Time:
#     15 hours
# Hardest thing:
#	  The hardest thing was to make sure that the wraping of the deque
#	  worked right;
###############################################################

##############################################################
# The main rule
##############################################################
a.out: deque.h assignment04.o nowServing.o
	g++ -o a.out assignment04.o nowServing.o 
	tar -cf assignment04.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment04.o : the driver program
#      nowServing.o   : the logic for the now serving program
##############################################################
assignment04.o: deque.h assignment04.cpp
	g++ -c assignment04.cpp

nowServing.o: nowServing.h nowServing.cpp deque.h
	g++ -c nowServing.cpp

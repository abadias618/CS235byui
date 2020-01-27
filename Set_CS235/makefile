###############################################################
# Program:
#     Assignment 05, SET
#     Brother kirby, CS235
# Author:
#     Abdias Baldiviezo & Kevin Hisel
# Summary:
#     Program containing a template for a class, 
#	  and an application to a goFish game. The hardest part for 
#	  this asignment was the iterators
# Time:
#     15 hours
###############################################################

##############################################################
# The main rule
##############################################################
a.out: assignment05.o goFish.o card.o
	g++ -o a.out assignment05.o goFish.o card.o
	tar -cf assignment05.tar *.h *.cpp makefile

##############################################################
# The individual components
#      assignment05.o : the driver program
#      goFish.o       : the logic for the goFish game
#      card.o         : a single playing card
##############################################################
assignment05.o: set.h goFish.h assignment05.cpp
	g++ -c assignment05.cpp

goFish.o: set.h goFish.h goFish.cpp card.h
	g++ -c goFish.cpp

card.o: card.h card.cpp
	g++ -c card.cpp

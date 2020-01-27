/***********************************************************************
 * Component:
 *    Assignment 13, Graph
 *    Brother Kirby, CS 235
 * Author:
 *    Josh Spendlove
 * Summary:
 *
 ************************************************************************/

#ifndef GRAPH_H
#define GRAPH_H

#include "vertex.h"
#include "set.h"
#include "list.h"
#include "vector.h"
    
using namespace custom;
    /********************************************************
     * Graph
     * A generic Vertex class serving as a base class
     *******************************************************/
    class Graph
    {
    public:
        Graph(int);
        Graph & operator =(Graph & rhs);
        bool empty() {return false;}
        int capacity();
        int size() const;
        void clear();
        void add(Vertex &, Vertex &);
        void add(Vertex &, set<Vertex> &);
        bool isEdge(Vertex &, Vertex &) const;
        set<Vertex> findEdges(Vertex &);
        vector<Vertex> findPath(Vertex &, Vertex &);
		void display();
    private:
        int numVertices;
        bool * matrix;
    };




#endif // GRAPH_H

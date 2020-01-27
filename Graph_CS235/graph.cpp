/***********************************************************************
 * Component:
 *    Assignment 12, Maze
 *    Brother Kirby, CS 235
 * Author:
 *    Josh Spendlove
 * Summary:
 *    Draw and solve a maze
 ************************************************************************/
#include "graph.h"
#include "vector.h"
//#include "set.h"
#include "list.h"
#include "deque.h"


using std::cout;
using std::endl;
using custom::set;
using custom::vector;
using custom::list;

Graph :: Graph(int numV)
{
    numVertices = numV;
    int numVerSqr = numVertices * numVertices;

    matrix = new bool[numVerSqr];
	clear();
}

Graph & Graph :: operator =(Graph & rhs)
{
    int numVerSqr = numVertices * numVertices;
    
    for(int i = 0; i < (numVerSqr); i++)
        matrix[i] = rhs.matrix[i];
    return *this;
}

int Graph :: capacity()
{
    return numVertices;
}

int Graph :: size() const
{
    return numVertices;
}

void Graph :: clear()
{
   for(int i = 0; i < (numVertices * numVertices); i++)
    matrix[i] = false;
}

void Graph :: add(Vertex & v1, Vertex & v2)
{
    matrix[(v1.index() * numVertices) + v2.index()] = true;
}

void Graph :: add(Vertex & v1, set<Vertex> & s)
{
    for(set<Vertex> :: iterator it = s.begin(); it != s.end(); it++)
        add(v1, *it);
}

bool Graph :: isEdge(Vertex & v1, Vertex & v2) const
{
    return matrix[(v1.index() * numVertices) + v2.index()];
}

set<Vertex> Graph :: findEdges(Vertex & v)
{
    set<Vertex> edges;
    for (int i = numVertices * v.index(); i < numVertices * (v.index() + 1); i++)
    {
        if(matrix[i])
        {
			Vertex v2(i % numVertices);
			edges.insert(v2);
        }
    }
    return edges;
}

vector<Vertex> Graph :: findPath(Vertex & v1, Vertex & v2)
{

	int distance = 0;

	vector<Vertex> predecessor = vector<Vertex>(size());

	list<Vertex> toVisit;

	toVisit.push_back(v1);

	vector<int> distances(size());

	for (int i = 0; i < size(); ++i)
	{
		distances[i]=-1;
	}

	//something is creating an infinite loop in this while
	
	int counter = 0;
	while (/*!toVisit.empty() && (distances[v2.index()] == -1)*/ counter<size()) 
	{
		Vertex v = toVisit.front();
		
		toVisit.pop_front();

		if (distances[v.index()] > distance)
		{
			distance++;
		}

		set<Vertex> s = findEdges(v);

		for (set<Vertex>::iterator it = s.begin(); it != s.end(); it++)

		{
			
			if (distances[(*it).index()] == -1)
			{	
				distances[(*it).index()] = distance + 1;

				predecessor[(*it).index()] = v;

				toVisit.push_back(*it);
			}
			distance++;

		}
		counter++;
	}

	vector<Vertex> path;

	if (distances[v2.index()] == -1)
	{
		return path;
	}
	path.push_back(CVertex(0, 0));
	path.push_back(v2);

	for (int i = 1; i < distance; ++i)
	{
		path.push_back(predecessor[path[i - 1].index()]);
	}
	
		

	return path;
}

void Graph::display()
{
	for (int i = 0; i < (numVertices * numVertices); i++)
	{
		if (i % numVertices == 0)
			std::cout << "\n";
		std::cout << " " << matrix[i];
	}
}



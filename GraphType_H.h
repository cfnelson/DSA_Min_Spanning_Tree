///////////////////////////////////////////////////////////////////////////////////
// Filename:		GraphType_H.h
// Author:			Charles Nelson - s2884951
// Date Modified:	25/03/2014 Created
//					31/04/2014 Updated 
// Description:		This is the template file for a custom GraphType Class, 
//					from TextBook & learnings from 2401ICT - Lectures Slides Week 12.
///////////////////////////////////////////////////////////////////////////////////
#ifndef H_graph
#define H_graph

#include <iostream>
#include <fstream>
#include <iomanip>
#include "LinkedList_H.h"
#include "linkedListGraph_H.h"

using namespace std;

const int infinity = 10000000;				//- Used for checking which link between the nodes has the lowest weight

template <class vType, int size> 
class graphType
{
private:
    void dft( vType v, bool visited[] );	// - Function to perform the depth first traversal of the graph at a particular node. 

public:
    bool isEmpty();							//- Function to determine whether the graph is empty. Postcondition: Returns true if the graph is empty; otherwise, returns false.
    void createGraph();						//- Function to create the graph using the adjacency list representation. Postcondition: The graph is created in the form of adjacenty lists.
    void clearGraph();						//- Function to deallocate the memory occupied by the linked lists and the array of pointers pointing to the linked lists.
    void printGraph() const;				//- Function to print the graph.

    void depthFirstTraversal();				//- Function to perform the depth first traversal of the entire graph.
    void dftAtVertex( vType vertex );		//- Function to perform the depth first traversal of the graph at a node specified by the parameter vertex.

    void breadthFirstTraversal();			//- Function to perform the breadth first traversal of the entire graph.

    graphType();							//- Default constructor. Postcondition: The graph size is set to 0, that is, gSize = 0; maxSize = size.

    ~graphType();							//- Destructor. Postcondition: The storage occupied by the graph is deallocated.

protected:
    int maxSize;							//- Maximum number of vertices
    int gSize;								//- Current number of vertices
    linkedListGraph <vType> graph[size];	//- Array of pointers to create the adjacency lists (linked lists)
};

//================================ PRIVATE FUNCTIONS ==========================================

template <class vType, int size>
void graphType <vType, size> :: dft( vType v, bool visited[] )
{
     vType w;

     vType *adjacencyList;											//- Array to retrieve the adjacent vertices
     adjacencyList = new vType[gSize];
 
     int alLength = 0;												//- The number of adjacent vertices

     visited[v] = true;
     cout<<" "<<v<<" ";												//- Visit the vertex

     graph[v].getAdjacentVertices(adjacencyList, alLength);			//- Retrieve the adjacent vertices into adjacencyList

     for ( int index = 0; index < alLength; index++ )				//- For each vertex adjacent to v 
     {                                 
         w = adjacencyList[index];
         if ( !visited[w] )
		 {
            dft( w, visited );
		 }															//- End if
     }																//- End for
     delete [] adjacencyList;
}																	//- End dft

//================================ PUBLIC FUNCTIONS ==========================================
template <class vType, int size> 
bool graphType <vType, size> :: isEmpty()
{
	return ( gSize == 0 );
}

template<class vType, int size> 
void graphType<vType, size> :: createGraph()
{
     ifstream infile;
     char fileName[50];

     vType vertex;
     vType adjacentVertex;

     if ( gSize != 0 )													//- If the graph is not empty, make it empty
	 {
        clearGraph();
	 }
     cout<<"Enter the input file name: ";
     cin>>fileName;
     cout<<endl;

     infile.open(fileName);

     if ( !infile )
     {
        cerr<<"Cannot open the input file."<<endl;
        return;
     }

     infile>>gSize;													//- Get the number of vertices

     for ( int index = 0; index < gSize; index++ )
     {
         infile>>vertex;
         infile>>adjacentVertex;

         while ( adjacentVertex != -999 )
         {
             graph[vertex].insertLast(adjacentVertex);
             infile>>adjacentVertex;
         }															//- End While Loop
     }																//- End For Loop

     infile.close();
}																	//- End createGraph

template <class vType, int size> 
void graphType <vType, size> :: clearGraph()
{
     int index;

     for ( index = 0; index < gSize; index++ )
	 {
         graph[index].destroyLinkedList();							//- Changed to use linked list from assignment 1
	 }
     gSize = 0;
}																	//- End clearGraph

template <class vType, int size> 
void graphType <vType, size> :: printGraph() const
{
     int index;

     for ( index = 0; index < gSize; index++ )
	 {
         cout<<index<<" "<<graph[index]<<endl;
	 }
     cout<<endl;
}																	//- End printGraph

template <class vType, int size> 
graphType <vType, size> :: graphType()								//- Default constructor
{
     maxSize = size;
     gSize = 0;
}																	//- End Constructor
    
template<class vType, int size>
graphType <vType, size> :: ~graphType()								//- Default Destructor
{
     clearGraph();
}																	//- End Destructor

template <class vType, int size>
void graphType <vType, size> :: depthFirstTraversal()
{
     bool *visited;													//- Array to keep track of the visited vertices
     visited = new bool[gSize];	
     int index;

     for ( index = 0; index < gSize; index++ ) 
	 {
	    visited[index] = false;   
	 }

     for ( index = 0; index < gSize; index++ )						// - For each vertex that is not visited, do a depth first traversal.
	 {
         if ( !visited[index] )
		 {
             dft( index,visited );      
		 }
	 }
     delete [] visited;
}																	//- End depthFirstTraversal

template <class vType, int size>
void graphType <vType, size> :: dftAtVertex( vType vertex )
{
     bool *visited;

     visited = new bool[gSize];

     for ( int index = 0; index < gSize; index++ )
	 {
         visited[index] = false;
	 }
     dft(vertex,visited);
 
     delete [] visited;

}																	//- End dftAtVertex

template <class vType, int size>
void graphType <vType, size>::breadthFirstTraversal()
{
   linkedQueueType <vType> queue;
   vType u;

   bool *visited;
   visited = new bool[gSize];
   for ( int ind = 0; ind < gSize; ind++ )
   {
       visited[ind] = false;										//- Initialize the array, Visited to false
   }	

   vType *adjacencyList;
   adjacencyList = new vType[gSize];
   int alLength = 0;
   for ( int index = 0; index < gSize; index++ )
   {
		if ( !visited[index] )
		{
			queue.addQueue(index);
			visited[index] = true;
			cout<<" "<<index<<" ";

			while ( !queue.isEmptyQueue() )
			{
				u = queue.front();
				queue.deleteQueue();
				graph[u].getAdjacentVertices(adjacencyList, alLength);
				for ( int w = 0; w < alLength; w++ )
				{
					if ( !visited[adjacencyList[w]] )
					{
						queue.addQueue(adjacencyList[w]);
						visited[adjacencyList[w]] = true;
						cout<<" "<<adjacencyList[w]<<" ";
					}											//- End IF:		!visited[adjacencyList[w]]
				}												//- End FOR:	w < alLength
			}													//- End WHILE:	!queue.isEmptyQueue()
		}														//- End IF		!visited[index]								
	}
	
   delete [] visited;
   delete [] adjacencyList;
}																	//- End breadthFirstTraversal
#endif
///////////////////////////////////////////////////////////////////////////////////
// END OF FILE
///////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
// Filename:		MinimalSpanTreeType_H.H
// Author:			Assignment Source Code & D.S Malik and Charles Nelson - s2884951
// Date Modified:	26/05/2014 Created
//					31/05/2014 Updated 
// Description:		This file contains the MinimalSpanTreeType Class Template.
////////////////////////////////////////////////////////////////////////////////////
#ifndef H_msTree
#define H_msTree

#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>     
#include <stdlib.h>
#include <time.h> 
#include <stdio.h>      
#include "GraphType_H.h"

using namespace std;

template <class vType, int size> 
class msTreeType: public graphType <vType, size>
{
public:

	void createSpanningGraph( int noOfNodes );															//- Function to create the graph and the weight matrix.
	void minimalSpanning( vType sVertex );																//- Function to create the edges of the minimal spanning tree. The weight of the edges is also saved in the array edgeWeights.
	void printTreeAndWeight();																			//- Function to output the edges and the weight of the minimal spanning tree.
	void prim2MST( vType sVertex );																		//- Input is a connected weighted graph G = (V,E) where V is set of Vertices(nodes) & E is set of Edges(links between nodes)
	int readNoOfNodesFromGraphFile();
	
protected:

	vType source;																						//- The input type
	double weights[size][size];																			//- Stores the matrix of graph in the form of the edgeweights between the nodes
	int edges[size];																					//- Stores the nodes that have edges in an array
	double edgeWeights[size];																			//- Stores the edgeweights of the nodes in an array

private:
																										//- Please note that all printed outputs below are printed out in the same Matrix format as the graph.txt file.
	void printGraphForCase1( int textBookGraph[][7] );													//- Prints the input graph for Case 1: Figure 12.16 from d.s malik c++ textbook is printed to console 
	void printGraphForCase2( int *tempArray );															//- Prints the input graph for Case 2: Graph for graph.txt file is printed to console 
	void printGraphForCase3( int **tempArray );															//- Prints the input graph for Case 3: The randomly generated graph is printed to console 
	
};

//================================ FUNCTIONS ==========================================

template <class vType, int size> 
int msTreeType <vType, size> :: readNoOfNodesFromGraphFile()
{
	int countSize = 0;																					//- Keeps count of the number of chars taken in fom the file
	
	ifstream myInputFile;																				//- Input stream created
	myInputFile.open( "graph.txt" );																	//- Open up the graph.txt file

	if ( !myInputFile )																					//- If cannot open file then return the user to the main function. 
	{
		cout << "Cannot open the input file." << endl;
		return -1;																						//- Returns an error value to the main so that the user can re-enter a valid file
	}
	while( !myInputFile.eof() )																			//- Loop until the end of the file is reached.
	{  
		int edgeWeightInputData;																		//- To store the edgeWeight from the file 
		myInputFile >> edgeWeightInputData;																//- Reading the edgeWeight from the file

		if ( myInputFile.fail() )																		//- Returns to the main if the file contains bad data e.g alpha char's instead of int's
		{
			cout << "Error bad input, please check the graph.txt file for invalid input" << endl;
			return -1;																					//- Returns an error value to the main so that the user can re-enter a valid file
		}
		countSize++;																					//- Incremenet the count up
	}
	myInputFile.close();
	int arraySize = sqrt( countSize );																	//- Setting the current number of vertices in the graph based from the input file.
	return arraySize;																					//- Returns the size of the array of the graph.txt file
}

template <class vType, int size> 
void msTreeType <vType, size> :: createSpanningGraph( int noOfNodes )
{
	if (noOfNodes == 0)																					//- Case 1: Create graph from figure 12.16 from d.s malik c++ textbook 
	{
		std::cout << "Input Graph is figure 12.16 from C++ textbook by D.S Malik" << std::endl;
		int noOfVertices = 7;																			//- Setting the noOf Vertices in the Graph
		gSize = noOfVertices;																			//- Setting the number of nodes in the graph to 7
		int textBookGraph[7][7] =																		//- Stores the Matrix from the textbook figure 12.16
		{								
			{ 0,6,5,2,0,0,0 },																			//- Row 0
			{ 6,0,0,0,2,0,4 },																			//- Row 1
			{ 5,0,0,0,0,7,5 },																			//- Row 2
			{ 2,0,0,0,8,0,0 },																			//- Row 3
			{ 0,2,0,8,0,10,0 },																			//- Row 4
			{ 0,0,7,0,10,0,0 },																			//- Row 5
			{ 0,4,5,0,0,0,0 }																			//- Row 6
		};																								//- Initialising the graph to the above matrix
		for ( int i = 0; i < noOfVertices; i++ )														//- Looping for Row
		{
			for ( int j = 0; j < noOfVertices; j++ )													//- Looping for Col
			{
				weights[i][j] = infinity;																//- Settting to the constant infinity. So we can compare edgeweight later on by using < 
				if ( textBookGraph[i][j] != 0 )															//- Check to see if there is a link. 0 means no link
				{
					graph[i].insertedgeWeightInputDataAtTail(j);										//- Creating the adjacentList of nodes
					weights[i][j] = textBookGraph[i][j];												//- Adding the weight of the matrix
				}
			}
		}	 
		printGraphForCase1( textBookGraph );															//- Printing out the input graph as a matrix
	}																									//- End of If - noOfNodes == 0
	
	else if ( noOfNodes < 0 )																			//- Case 2: Read from graph.txt
	{
		std::cout << "Input Graph is from the graph.txt file"<< "\n" << std::endl;
		int countSize = 0;																				//- Keeps count of the number of chars taken in fom the file
		int inputGraphArray[size];																		//- array to store edgeWeightInputData from the graph.txt

		ifstream myInputFile;																			//- Create input stream															
		myInputFile.open( "graph.txt" );

		if ( !myInputFile )																				//- If cannot open file then return the user to the main function. 
		{
			cout << "Cannot open the input file." << endl;
			return;																						//- Return to main.cpp if cannot open
		}
		while( !myInputFile.eof() ) 
		{  
			int edgeWeightInputData;																	//- To store the edgeWeight from the file 
			myInputFile >> edgeWeightInputData;															//- Reading the edgeWeight from the file
			
			if ( myInputFile.fail() )																	//- Returns to the main if the file contains bad data e.g alpha char's instead of int's
			{
				cout << "Error bad input, please check the graph.txt file for invalid input" << endl;
				return;
			}
			inputGraphArray[countSize] = edgeWeightInputData;											//- Storing the input edgeWeightInputData (edgeWeight)from the file into the Array. 
			//cout << edgeWeightInputData << endl;														//- Used for Testing Purposes
			countSize++;																				//- Incremenet the count up
		}
		myInputFile.close();																			//- Closing the input file and file stream
		gSize = sqrt( countSize );																		//- Setting the current number of vertices in the graph based from the input file.
	
		int k = 0;																						//- Keep count of single dim array element position
		
		for ( int i = 0; i < gSize; i++ )																//- Loop for Row
		{
			for ( int j = 0; j < gSize; j++ )															//- Loop for Col
			{
				weights[i][j] = infinity;																//- Settting to constant infinity. So we can compare edgeweight later on by using < 
				if ( inputGraphArray[i*gSize+j]!= 0 )													//- Check to see if there is a link. 0 means no link
				{
					graph[i].insertedgeWeightInputDataAtTail( k );										//- Creating the adjacentList of nodes
					weights[i][j] = inputGraphArray[k];													//- adding the weight of the matrix
				}
				k++;																					//- Iterating through the single dem array element position
			}	
		}

		printGraphForCase2(inputGraphArray);															//- Printing out the input graph as a matrix
	}																									//- End of Else If - noOfNodes < 0
	
	else if ( noOfNodes > 0 )																			//- Case 3: Randomly generate number of edges between nodes and their edgeweights. PLEASE NOTE: noOfNodes must be < maxSize
	{
		std::cout	<< "Input Graph will be generated randomly with " << noOfNodes 
					<< " Nodes." << "\n" << std::endl;
		srand ( ( unsigned ) time( NULL ) );															//- Initialize random seed
		gSize = noOfNodes;
		int maxNoOfEdges = ( ( noOfNodes*( noOfNodes - 1 ) )/2 );										//- Max edges formula is: n(n-1)/2
		
		if ( maxNoOfEdges == 0 )																		//- If 1 node is entered then there is a chance there will be no links
		{
			maxNoOfEdges = 1;															
		}
		
		int noOfEdges = rand() % maxNoOfEdges + 1;														//- generates random number of edges between (1 - maxNoOfEdges) for the graph
		while (noOfEdges < noOfNodes)																	//- ensure there are enough edges for there to be a link between each node
		{
			noOfEdges+=1;																				//- increasing size by 1
		}
		int* randEdgeWeightArray = new int [noOfEdges];													//- array containing random weights for the edges

		for ( int i = 0; i < noOfEdges; i++ )
		{
			randEdgeWeightArray[i] = rand() % maxNoOfEdges + 1;											//- Setting element values of the randEgeWeightArray
			//std::cout << "Random EdgeWeight is: "	<< randEdgeWeightArray[i] << std::endl; 
		}

		//std::cout << "The max number of Edges in this graph are: " << noOfEdges << std::endl;			//- Used for testing purposes
		
		int** tempArray = new int* [noOfNodes];															//- Creating 2d array with pointers
		for ( int i = 0; i < noOfNodes; i++ )
		{
			tempArray[i] = new int[noOfNodes];															//- Creating new row of ints
		}
																										//- Loop for initialising tempArray
		for ( int i = 0; i < noOfNodes; i++ )															//- Looping for Row
		{
			for ( int j = 0; j < noOfNodes; j++ )														//- Looping for Col
			{
				tempArray[i][j] = 0;																	//- Initialising to 0
			}
		}

		int counter = 0;																				//- Stores the count 
		for ( int i = 0; i < noOfNodes; i++ )															//- Looping for Row
		{
			int emptyCounter = 0;																		//- To check and make sure each node has one conection
			for ( int j = 0; j < noOfNodes; j++ )														//- Looping for Col
			{
				if ( i == j )																			//- Check for ensuring the diaganol is always 0. As nodes can not link to itself in this graph.
				{
					//emptyCounter++;																	//- Used for testing purposes
					//- Do nothing as 0 means no link between nodes.  
				}
				else
				{
					int randNo =( rand() % (501 - 499) ) + 499;											//- Used to randomly allocate the links between nodes with magic numbers
					//std::cout << "Random NO is: "	<< randNo << std::endl;								//- Used for testing purposes
					if ( randNo == 499 )
					{
						//emptyCounter++;																//- Used for testing purposes
						//- Do nothing as 0 means no link between nodes.
					}
					else if ( counter < noOfEdges )														//- Check to ensure that we do not add more edges then we have created
					{
						tempArray[i][j] = randEdgeWeightArray[counter];									//- Setting the element to the random edge weight
						//std::cout << "tempArray [" << i << "][" << j << "] is = " 
						//			<< randEdgeWeightArray[counter] << std::endl;						//- Used for testing purposes
						tempArray[j][i] = randEdgeWeightArray[counter];									//- Setting the element to the random edge weight and ensures that it is symetrical 
						//std::cout << "tempArray [" << j << "][" << i << "] is = " 
						//			<< randEdgeWeightArray[counter] << std::endl;						//- Used for testing purposes
						counter++;																		//- Iterating the count by 1
						emptyCounter++;																	//- Iterating the emptyCount by 1
					}
				}

				if ( j == ( noOfNodes-1 ) && emptyCounter == 0 )										//- Used to ensure that their is at least one link between nodes
				{
					counter = 0;																		//- Initialising the counter to 0
					emptyCounter = 0;																	//- Initialising the emptycounter to 0
					for ( int j = 0; j < noOfNodes; j++ )												//- Looping for Col
					{
						if ( emptyCounter != 0 )														//- Check to see if the node has at least one edge.
						{
							break;																		//- Break out of loop as the node has at least one edge.
						}
						if ( i == j )																	//- Check for ensuring the diaganol is always 0. As nodes can not link to itself in this graph.
						{
							//- Do nothing as 0 means no link between nodes.  
						}
						else
						{
							int randNo = ( rand() % ( 501 - 499) ) + 499;								//- Used to randomly allocate the links between nodes with magic numbers
							//std::cout << "Random NO is: "	<< randNo << std::endl;						//- Used for testing purposes
							if ( randNo == 499 )
							{
								//- Do nothing as 0 means no link between nodes.
							}
							else if ( counter < noOfEdges )												//- Check to ensure that we do not add more edges then we have created
							{
								tempArray[i][j] = randEdgeWeightArray[counter];							//- Setting the element to the random edge weight
								//std::cout << "tempArray [" << i << "][" << j << "] is = " 
								//			<< randEdgeWeightArray[counter] << std::endl;				//- Used for testing purposes
								tempArray[j][i] = randEdgeWeightArray[counter];							//- Setting the element to the random edge weight and ensures that it is symetrical 
								//std::cout << "tempArray [" << j << "][" << i << "] is = " 
								//			<< randEdgeWeightArray[counter] << std::endl;				//- Used for testing purposes
								counter++;																//- Iterating the count by 1
								emptyCounter++;															//- Iterating the emptyCount by 1
							}
						}
					}																					//- End If's For Loop from line 240
				}																						//- End If Statement for ensuring each Node has an edge attached to it
			}																							//- End 1st inner For Loop
		}																								//- End main For Loop
	
		printGraphForCase3( tempArray );																//- Printing out the input graph as a matrix
	
		for ( int i = 0; i < noOfNodes; i++ )															//- Loop for Row
		{
			for ( int j = 0; j < noOfNodes; j++ )														//- Loop for Col
			{
				weights[i][j] = infinity;																//- Settting to constant infinity. So we can compare edgeweight later on by using < 
				if ( tempArray[i][j] != 0 )																//- Check to see if there is a link. 0 means no link
				{	
					graph[i].insertedgeWeightInputDataAtTail( j );										//- Creating & Adding the adjacentList of nodes
					weights[i][j] = tempArray[i][j];													//- Adding the weight of the matrix
				}
			}
		} 

		for ( int i = 0; i < noOfNodes; i++ )															//- DESTROY MEMORY
		{
			delete[] tempArray[i]; 
		}
		delete[] tempArray;
	}																									//- End of Else - noOfNodes > 0
}																										//- End of createWeightedGraph

template <class vType, int size> 
void msTreeType <vType, size> :: printGraphForCase1( int tempArray[][7] )								//- Prints the input graph for Case 1: Figure 12.16 from d.s malik c++ textbook is printed to console 
{
	int noOfVertices = 7;																				//- Number of vertices to loop through
	for ( int i = 0; i < noOfVertices; i++ )															//- Loop for Row
	{
		for ( int j = 0; j < noOfVertices; j+=noOfVertices )											//- Loop through the row's coloumns at once by grouping all elements in the row together.
		{
			for ( int k = 0; k < noOfVertices; k++ )													//- Loop through every element in the row
			{
				std::cout <<setw(3) <<	tempArray[i][k]   <<",";										//- Printing out the element to the console.
			}
			std::cout<< std::endl;																		//- End the ouput line for the row of elements
		}
	}
}																										//- End printGraphForCase1

template <class vType, int size> 
void msTreeType <vType, size> :: printGraphForCase2( int *tempArray )									//- Prints the input graph for Case 2: Graph for graph.txt file is printed to console 
{
	for ( int i = 0; i < gSize; i++ )																	//- Loop for Row
	{
		for ( int j = 0; j < gSize; j+=gSize )															//- Loop through the row's coloumns at once by grouping all elements in the row together.
		{
			for ( int k = 0; k < gSize; k++ )															//- Loop through every element in the row
			{
				std::cout << setw( 3 ) << tempArray[i*gSize+k] << ",";									//- Printing out the element to the console.
			}
			std::cout << std::endl;																		//- End the ouput line for the row of elements
		}
	}
}																										//- End printGraphForCase2

template <class vType, int size> 
void msTreeType <vType, size> :: printGraphForCase3( int **tempArray )									//- Prints the input graph for Case 3: The randomly generated graph is printed to console
{
	for ( int i = 0; i < gSize; i++ )																	//- Loop for Row
	{
		for ( int j = 0; j < gSize; j+=gSize )															//- Loop through the row's coloumns at once by grouping all elements in the row together.
		{
			for ( int k = 0; k < gSize; k++ )															//- Loop through every element in the row
			{
				std::cout << setw( 3 ) << tempArray[i][k] << ",";										//- Printing out the element to the console.
			}
			std::cout << std::endl;																		//- End the ouput line for the row of elements
		}																								
	}
}																										//- End printGraphForCase3

template <class vType, int size> 
void msTreeType <vType, size> :: printTreeAndWeight()													//- Print Tree Function provided for Uni Assignment
{
	double treeWeight = 0;																				//- Stores the total weight of the tree

	cout << fixed << showpoint << setprecision(2);														//- Sets the formating for the output stream to the console

	cout <<"Source Vertex: " << source	<< endl;
	cout << "Edges    Weight"			<< endl;

	for ( int j = 0; j < gSize; j++ )
	{
		if ( edges[j] != j )
		{
			if ( edgeWeights[j] != infinity )															//- Added check to see if the edges have no link e.g if value equals infinity then there is no link
			{
				treeWeight = treeWeight + edgeWeights[j];												//- Adding the weight's together
				cout << "(" << edges[j] <<", "<< j <<")    " << edgeWeights[j] << endl;
			}
			else
			{
				cout << "(" << edges[j] <<", "<< j <<")    " << "infinity" << endl;						//- Changed line to print out infinity if there is no link between edges
			}
		}
	}
	cout << endl;
	cout << "Tree Weight: " << treeWeight << "\n" << endl;
}																										 //- End of printTreeAndWeight

template <class vType, int size> 
void msTreeType <vType, size> :: minimalSpanning( vType sVertex )
{
	int i,j,k;
    vType startVertex;
	vType endVertex;
    double minWeight;

    source = sVertex;

    bool mstv[size];

    for(j = 0; j < gSize; j++)
    {
        mstv[j] = false;
        edges[j] = source;
        edgeWeights[j] = weights[source][j];
    }

    mstv[source] = true;																				//- Minimal Spanning Tree Visited - stores an array of bool's to check if visited
    edgeWeights[source] = 0;

    for ( i = 0; i < gSize - 1; i++ )
    {
        minWeight = infinity;

        for ( j = 0; j < gSize; j++ )
		{
            if ( mstv[j] )
			{
               for ( k = 0; k < gSize; k++ )
			   {
                   if ( !mstv[k] && weights[j][k] < minWeight )
                   {
                      endVertex = k;
                      startVertex = j;
                      minWeight = weights[j][k];
                   }
			   }
			}
		}
        mstv[endVertex] = true;
        edges[endVertex] = startVertex;
        edgeWeights[endVertex] = minWeight;
    }																									//- End For Loop
}																										//- End minimalSpanning function

template<class vType, int size> 
void msTreeType <vType, size> :: prim2MST( vType sVertex )												//- Prim2 Minimal Spanning Tree function derived from the pseudocode on pg 728 of DS C++ D.S Malik Textbook
{
	double minWeight;																					//- Stores the current lowest edgeWeight for a link between nodes.
	bool visited[size];																					//- Array of bool's that store the visited 
	vType startVertex;																					//- Start Vertex initialised
	vType endVertex;																					//- End Vertex initialised
	source = sVertex;																					//- Source vertex is set from input
	
	for ( int j = 0; j < gSize; j++ )																	//- Looping through the first row of elements
	{
		edgeWeights[j] = weights[source][j];															//- Setting the edgeWeights from the weights matrix input[i][j]
		edges[j] = source;																				//- Edges[j] is set to the source value 
		visited[j] = false;																				//- Setting the visted value to false
	}																									//- End For Loop
	
	edgeWeights[source] = 0;																			//- Resetting to 0;
	visited[source] = true;																				//- Setting row to visited
	
	for ( int i = 0; i < gSize; i++ )																	//- Looping through the first row
	{
		minWeight = infinity;																			//- Setting the minWeight to inifity so we can find the lowest edgeWeight
		int k = -1;																						//- Setting k to value outside of range to be use for a check later on
		for ( int j = 0; j < gSize; j++ )																//- Looping throught the coloumns
		{
			if ( !visited[j] && edgeWeights[j] < minWeight )											//- Checking to see if it has been visited and edgeWeight is less then minWeight
			{
				k = j;																					//- Storing the element where the lower edgeWeight was found
				minWeight = edgeWeights[j];																//- Updating the minWeight of the edge 
			}
		}																								//- End first nested for loop
		if ( k != source && k != -1 )																	//- Checks to see if k does not equal itself and k has been updated to a lower value
		{
			visited[k] = true;																			//- Setting the element to have been visited
			for ( int j = 0; j < gSize; j++ )															//- Looping through every J elements to check if its not visited 
			{
				if ( !visited[j] )																		//- Check if this element has not been visited
				{
					if ( weights[k][j] < edgeWeights[j] )												//- Check to see if the stored edgeWeight in the weights matrix is lower the then current edgeWeights at j
					{
						edgeWeights[j] = weights[k][j];													//- Update the edgeWeights element
						edges[j] = k;																	//- Update the edges element
					}
				}
			}																							//- End 2nd nested for loop
		}
	}																									//- End for Loop
}																										//- End prim2MST
#endif
///////////////////////////////////////////////////////////////////////////////////
// END OF FILE
///////////////////////////////////////////////////////////////////////////////////
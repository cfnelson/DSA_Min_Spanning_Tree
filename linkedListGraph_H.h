///////////////////////////////////////////////////////////////////////////////////
// Filename:		linkedListGraph_H.h
// Author:			Charles Nelson - s2884951
// Date Modified:	26/05/2014 Created
//					31/05/2014 Updated 
// Description:		This is the template file for a custom linkedListGraph Class, based
//					from learnings from 2401ICT - Lectures Slides Week 12.
///////////////////////////////////////////////////////////////////////////////////
#ifndef linkedListGraph_H
#define linkedListGraph_H

#include <iostream>
#include "LinkedList_H.h"

using namespace std;

template<class vType>
class linkedListGraph: public linkedListType<vType>
{ 
public:
	void getAdjacentVertices( vType adjacencyList[],int& length );						//- Retrieve the vertices adjacent to given vertex. Postconditions: length is the number of adjacent vertices retrieved. Vertices are retrieved in the array adjacentList. 
}; 

template<class vType>
void linkedListGraph<vType>::getAdjacentVertices(vType adjacencyList[], int& length)
{
	nodeType<vType> *current = first;
	length = 0;

	while (current != NULL)
	{
		adjacencyList[length++] = current->info;
		current = current->link;
	}
}
#endif
///////////////////////////////////////////////////////////////////////////////////
// END OF FILE
///////////////////////////////////////////////////////////////////////////////////
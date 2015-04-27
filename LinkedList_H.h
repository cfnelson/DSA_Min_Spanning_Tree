///////////////////////////////////////////////////////////////////////////////////
// Filename:		LinkedList_H.h
// Author:			Charles Nelson - s2884951
// Date Modified:	25/03/2014 Created
//					31/05/2014 Updated 
// Description:		This is the template file for a custom Linked List Class, based
//					from learnings from 2401ICT - Lectures/Labs.
///////////////////////////////////////////////////////////////////////////////////
#ifndef LinkedList_H
#define LinkedList_H

#include <stdlib.h>
#include <cstdint>
#include <stdint.h>

using namespace std;

template <class T>
class linkedListType
{
	void copyLinkedList(const linkedListType<T>& otherList);									//- Makes a copy of the Linked List

protected:

	template <class T>
	struct dNodeType							
	{
		T			edgeWeightInputData;														//- edgeWeightInputData to be stored in the Node, must be the same type of class T
		struct dNodeType*	nextAddress;														//- Address to the next node in the Linked List
		//dNodeType<T>*	previousAddress;														//- Left here in order to implement a Doubley Linked List at a later date.
		friend ostream& operator<<(ostream& os, const dNodeType<T>& obj)						//- Allowing overloading of the ostream operator '<<' 
		{
			os << obj.edgeWeightInputData << "Next Address: " << obj.nextAddress;
			return os;
		}
	};																		

	int size;																					//- number of nodes in the Linked List
	dNodeType<T>* head;																			//- Pointer to the starting node of the Linked List
	dNodeType<T>* tail;																			//- Pointer to the ending node of the Linked List

private:	

	//- Currently left empty 

public:

	linkedListType();																			//- Default Constructor for Linked List
	linkedListType(const linkedListType<T>& otherList);											//- Creates a new Linked List from copyList
	~linkedListType();																			//- Destructor for Linked List  

	const linkedListType<T>& operator=(const linkedListType<T>&);								//- Overloading the "=" sign to provide a deep copy 
	void initialiseLinkedList();																//- Initialises the Linked List
	bool checkIfEmpty();																		//- Checks if the Linked List is empty. Returns True if empty, else False. 
	int sizeOfLinkedList();																		//- Returns the number of nodes in the Linked List
	bool searchLinkedList(const T& searchNodeedgeWeightInputData);								//- Searchs Linked List for a specific node

	void destroyLinkedList();																	//- Deletes all the nodes in the Linked List												
	void insertedgeWeightInputDataAtHead(const T& newedgeWeightInputData);						//- Inserts a node at the head of the Linked List
	void insertedgeWeightInputDataAtTail(const T& newedgeWeightInputData);						//- Inserts a node at the tail of the Linked List
	void insertedgeWeightInputDataAfter(int index, const T& newedgeWeightInputData);			//- Inserts edgeWeightInputData after specified point in the Linked List
	void deleteNodeType(const T& deleteNodeedgeWeightInputData);								//- Searches for the Node containg the specified edgeWeightInputData.	NOTE: edgeWeightInputDatatype must have a comparable/check equality operator for this function to work. 
	void deleteNodeAt(int index);																//- Deletes a Node at a specified location

	T getHead();																				//- Returns the first Node of the list	
	T getTail();																				//- Returns the Last Node of the List
	T getNodeAt(int index);																		//- Returns the nth node in the list as specified by the index	

	T& getNodeAt_Reference(int index);															//- Returns the node edgeWeightInputData via reference (the address). This is so we can edit T edgeWeightInputData directly
	T& operator[](int index);																	//- Overloading the [] to operate like an array index call

	void printLinkedList( )const;
};

//=============================== PUBLIC FUNCTIONS ========================================== 



/*********************************************************************************
* Description:		This function is the Default Constructor.
*
* Returns:			NIL
*
* Parameters:		NIL
*
* Preconditions:	NIL
*
* Postconditions:	A default Linked List  object  has been constructed
*********************************************************************************/
template <class T>
linkedListType<T>::linkedListType()															//- Default Constructor for Linked List
{
	head = NULL;
	tail = NULL;
	size = 0;
}


/*********************************************************************************
* Description:		This function is the Destructor for the Linked List
*
* Returns:			NIL
*
* Parameters:		NIL
*
* Preconditions:	NIL
*
* Postconditions:	All Memory freed
*********************************************************************************/
template <class T>
linkedListType<T>::~linkedListType()														//- Destructor for Linked List  
{
	destroyLinkedList();
}

/*********************************************************************************
* Description:		This function is a Constructor with a Linked List as a parameter. 
*
* Returns:			NIL
*
* Parameters:		const linkedListType<T>& otherList
*
* Preconditions:	NIL
*
* Postconditions:	A Linked List has been constructed from the parameter provided
*********************************************************************************/
template <class T>
linkedListType<T>::linkedListType(const linkedListType<T>& otherList)						//- Creates a new Linked List from copyList
{	
	head = NULL;
	copyLinkedList(otherList);																//- Calling the copyLinkedList Function. Copying linked list.
}

/*********************************************************************************
* Description:		This function completes a deep copy of the Linked List. 
*
* Returns:			NIL
*
* Parameters:		const linkedListType<T>& otherList; input List to be copied
*
* Preconditions:	NIL
*
* Postconditions:	List will be copied
*********************************************************************************/
template <class T>
void linkedListType<T>::copyLinkedList(const linkedListType<T>& otherList)					//- Makes a copy of the Linked List
{
	dNodeType<T>* newNode;																	//- Pointer for new node
	dNodeType<T>* p_currentNode;															//- Pointer to move along list and keep track

	if ( head != NULL )																		//- Check to see if the Linked List is empt. If it is not empty, empty it.
	{
		destroyLinkedList();
	}
	if ( otherList.head == NULL )															//- otherList is empty
	{
		head = tail;
		tail = NULL;
		size = 0;
	}
	else
	{
		p_currentNode = otherList.head;														//- Pointer to the list that is to be copied.
		size = otherList.size;
		head = new dNodeType<T>;															//- Create the node to be copied;
		//assert(head != NULL);
		head -> edgeWeightInputData = p_currentNode -> edgeWeightInputData;												//- Copy the edgeWeightInputData across to the Linked List
		head -> nextAddress = NULL;															//- Set nextAddress to NULL
		tail = head;
		p_currentNode = p_currentNode -> nextAddress;										//- Move to the next node to be copied
		while ( p_currentNode != NULL)														//- Copy the remaining Linked List
		{
			newNode = new dNodeType<T>;														//- Create a new node
			//assert(newNode != NULL);														//- Left commented out for this current implementation
			newNode -> edgeWeightInputData = p_currentNode -> edgeWeightInputData;										//- Copy the edgeWeightInputData across to the Linked List
			newNode -> nextAddress = NULL;
			tail -> nextAddress = newNode;													//- Attach the newNode
			tail = newNode;																	//- Update the tail node
			p_currentNode = p_currentNode -> nextAddress;									//- Move to the next node
		}
	}
}

/*********************************************************************************
* Description:		This function overloads the '=' operator and completes a deep copy
*					of the Linked List.
*
* Returns:			const linkedListType<T> &linkedListType<T>; 
*
* Parameters:		const linkedListType<T>& otherList; List to be copied
*
* Preconditions:	grades must not be NULL
*
* Postconditions:	NIL
*********************************************************************************/
template <class T> 
const linkedListType<T>& linkedListType<T>::operator=(const linkedListType<T>& otherList)	//- Overloads the '=' operator to do a deep copy. This is completed by calling the copyLinkedList() function
{
	if (this != &otherList) 
	{
		copyLinkedList(otherList);
	}
	return *this;
}

/*********************************************************************************
* Description:		This function initialises the Linked List to NULL by invoking 
*					the destroyLinkedList() function.
*
* Returns:			NIL
*
* Parameters:		NIL
*
* Preconditions:	NIL
*
* Postconditions:	Linked List will have been set to NULL
*********************************************************************************/
template <class T>	
void linkedListType<T>::initialiseLinkedList()												//- Initialises the Linked List
{
	destroyLinkedList();																	//- Setting the Linked List to NULL
}	

/*********************************************************************************
* Description:		This function checks if the Linked List is empty and returns
*					a bool value of True or False. 
*
* Returns:			Bool value; True if empty or False if not empty.
*
* Parameters:		NIL
*					
* Preconditions:	Linked List must be instantiated. 
*
* Postconditions:	NIL
*********************************************************************************/
template <class T>	
bool linkedListType<T>::checkIfEmpty()														//- Checks if the Linked List is empty. Returns True if empty, else False. 
{
	return (head == NULL);																	//- Returns TRUE if head == NULL. E.G - IF head == NULL, return TRUE, ELSE return FALSE. 
}

/*********************************************************************************
* Description:		This function examines the number of nodes in the Linked List
*					and returns it's size. E.G - The quantity of nodes in the List.
*
* Returns:			int size;
*
* Parameters:		NIL
*
* Preconditions:	Linked List must be instantiated. 
*
* Postconditions:	NIL
*********************************************************************************/
template <class T>	
int linkedListType<T>::sizeOfLinkedList()													//- Returns the number of nodes in the Linked List
{
	return size;																			//- Returns the number of nodes contained in the Linked List e.g the size of the Linked List.
}

/*********************************************************************************
* Description:		This function searchs the Linked List for the specified node 
*					edgeWeightInputData and returns True or False. Indicating if the node was 
*					found or not in the Linked List.
*					
* Returns:			bool foundNode; True if node found. Else False if not found.
*
* Parameters:		const T& searchNodeedgeWeightInputData; T edgeWeightInputData to search for.
*					
* Preconditions:	Linked List must be instantiated. 
*
* Postconditions:	NIL
*********************************************************************************/
template <class T>	
bool linkedListType<T>::searchLinkedList(const T& searchNodeedgeWeightInputData)			//- Searchs Linked List for a specific node
{
	bool foundNode = false;																	//- Setting foundNode to false
	dNodeType<T>* p_currentNode = head;														//- Pointer to move along list and keep track

	while ( p_currentNode != NULL && !foundNode )											//- Search through the list, looking for foundNode
	{
		if ( p_currentNode->edgeWeightInputData == searchNodeedgeWeightInputData )
		{
			foundNode = true;
		} 
		else
		{
			p_currentNode = p_currentNode -> nextAddress;									//- Moves and sets the p_currentNode to the next node address 
		}
	}
	return foundNode;																		//- Returns a bool stating if the item searched for was found.
}

/*********************************************************************************
* Description:		This function inserts a new node at the start of the Linked List.
*					
* Returns:			NIL
*
* Parameters:		const T& newedgeWeightInputData; T edgeWeightInputData to be inserted with the node
*					
* Preconditions:	Linked List must be instantiated. 
*
* Postconditions:	NIL
*********************************************************************************/
template <class T>	
void linkedListType<T>::insertedgeWeightInputDataAtHead(const T& newedgeWeightInputData)	//- Inserts a node into specified location
{
	dNodeType<T> *newNode;																	//- Pointer for the new Node
	newNode = new dNodeType<T>;																//- New Node is being created
	//assert( newNode != NULL );															//- Left out for current implementation. Abort program and print error, if unable to allocate memory
	newNode -> edgeWeightInputData = newedgeWeightInputData;																//- Store the new edgeWeightInputData in the new node
	newNode -> nextAddress = head;															//- Insert newNode before the First Node
	head = newNode;																			//- The head now points to the actual First Node
	size++;																					//- Increment the size of the Linked List

	if( tail == NULL )
	{
		tail = newNode;																		//- If list is empty, newNode is the last node
	}
}

/*********************************************************************************
* Description:		This function inserts a new node at the end of the Linked List.
*					
* Returns:			NIL
*
* Parameters:		const T& newedgeWeightInputData; T edgeWeightInputData to be inserted with the node
*					
* Preconditions:	Linked List must be instantiated. 
*
* Postconditions:	NIL
*********************************************************************************/
template <class T>	
void linkedListType<T>::insertedgeWeightInputDataAtTail(const T& newedgeWeightInputData)	//- Inserts a node into specified location
{
	dNodeType<T> *newNode;																	//- Pointer for the new Node
	newNode = new dNodeType<T>;																//- New Node is being created
	//assert(newNode != NULL);																//- Left out for current implementation. Abort program and print error, if unable to allocate memory
	newNode -> edgeWeightInputData = newedgeWeightInputData;																//- Store the new edgeWeightInputData in the new node
	newNode -> nextAddress = NULL;															//- Make nextAddress point to NULL. E.G it is the last node in the Linked List
	if ( head == NULL )
	{
		head = tail;
		tail = newNode;
		size++;																				//- Increment the size of the Linked List 
	}
	else
	{
		tail -> nextAddress = newNode;														//- Insert Node at the end of the Linked List
		tail = newNode;																		//- Update the pointer to the end of the Linked List
		size++;																				//- Increment the size of the Linked List 
	}
}

/*********************************************************************************
* Description:		This function searches for the specified node T edgeWeightInputData and
*					deletes it when found.
*
* Returns:			NIL
*
* Parameters:		const T &deleteNodeedgeWeightInputData; Node to delete, referenced by its T edgeWeightInputData
*					
* Preconditions:	NIL
*
* Postconditions:	NIL
*********************************************************************************/
template <class T>	
void linkedListType<T>::deleteNodeType(const T &deleteNodeedgeWeightInputData)				//- Deletes a node in a specified location
{
	bool foundNode;																			//- foundNode to show if found or not
	dNodeType<T>* p_currentNode;															//- Pointer to move along list and keep track
	dNodeType<T>* p_trailCurrentNode;														//- Pointer that follows behing current Pointer
	if ( head == NULL )																		//- Case 1
	{
		cerr<< "ERROR: You can not delete a node from an empty List\n";
	}
	else
	{
		if ( head -> edgeWeightInputData == deleteNodeedgeWeightInputData )					//- Case 2
		{
			p_currentNode = head;
			head = head -> nextAddress;
			size--;																			//- decrease the size of the Linked List

			if( head == NULL )																//- Check to see if Linked List only has one node
			{
				tail = NULL;					
				delete p_currentNode;														//- Delete the node from Linked List
			}
		}
		else																				//- Search the Linked List for the node to be deleted
		{
			foundNode = false;
			p_trailCurrentNode = head;														//- trail pointer points to the first node in the Linked List
			p_currentNode = head -> nextAddress;											//- current pointer points to the second node in the Linked List

			while ( p_currentNode != NULL && !foundNode )									//- Search through the list, looking for foundNode
			{
				if ( p_currentNode->edgeWeightInputData != deleteNodeedgeWeightInputData )
				{
					p_trailCurrentNode = p_currentNode;
					p_currentNode = p_currentNode -> nextAddress;
				} 
				else
				{
					foundNode = true;
				}
			}
			if ( foundNode )																//- Case 3: if the node to be deleted is found, delete the node
			{
				p_trailCurrentNode -> nextAddress = p_currentNode -> nextAddress;
				size--;																		//- decrease the size of the Linked List
				if ( tail == p_currentNode)
				{
					tail = p_trailCurrentNode;
					delete p_currentNode;													//- Delete the node from Linked List
				}
				else
				{
					cout<<"ERROR: The Node edgeWeightInputData to be deleted is not contained within the List."<<endl;
				}
			}
		}
	}
}

/*********************************************************************************
* Description:		This function destroys the Linked List and sets it to NULL. 
*				
* Returns:			NIL
*
* Parameters:		NIL
*					
* Preconditions:	NIL
*
* Postconditions:	Linked List will be destroyed and set to NULL
*********************************************************************************/
template <class T>	
void linkedListType<T>::destroyLinkedList()													//- Deletes all the nodes in the Linked List
{
	dNodeType<T>* temp;																		//- Pointer to the node to be deleted
	while (head != NULL)																	//- While the Linked List contains nodes, we will loop through and delete one at a time.
	{
		temp = head;																		//- Set the pointer to the head node(current node)
		head = temp->nextAddress;															//- Move pointer to the next node
		delete temp;																		//- deallocate memory occupied by temp
	}
	tail = NULL;																			//- Tail set to NULL, head is already set
	size = 0;
}

/*********************************************************************************
* Description:		This function returns head node of the Linked List.
*					
* Returns:			struct dNodeType;
*
* Parameters:		NIL
*					
* Preconditions:	NIL
*
* Postconditions:	NIL
*********************************************************************************/
template <class T>	
T linkedListType<T>::getHead()																//- Returns the first Node of the list		
{
	//assert(head);																			//- Left out for current implementation. Checks to see if head isnt NULL or real, otherwise aborts and prints an error message ?
	return head -> edgeWeightInputData;														//- Returns the T edgeWeightInputData struct 
}
/*********************************************************************************
* Description:		This function returns the node of the tail of the Linked List.
*					
* Returns:			struct dNodeType;
*
* Parameters:		NIL
*					
* Preconditions:	NIL
*
* Postconditions:	NIL
*********************************************************************************/
template <class T>	
T linkedListType<T>::getTail()																//- Returns the Last Node of the List
{
	//assert(tail);																			//- Left out for current implementation. Checks to see if tail isnt NULL or real, otherwise aborts and prints an error message 
	return tail -> edgeWeightInputData;														//- Returns the T edgeWeightInputData struct 
}

/*********************************************************************************
* Description:		This function returns the node from the specified index.
*					
* Returns:			struct dNodeType;
*
* Parameters:		int index; Index of the node to retrieve in the Linked List.
*					
* Preconditions:	NIL
*
* Postconditions:	NIL
*********************************************************************************/
template <class T>  
T linkedListType<T>::getNodeAt(int index)													//- Searchs Linked List for the nth node in the list as specified by the index
{

	dNodeType<T>* p_currentNode = head;														//- Pointer to move along list and keep track
	int count = 0;																			//- Creating a counter that starts at zero

	while ( p_currentNode != NULL )															//- Search through the list, looking for foundNode
	{
		if ( count == index )
		{
			return (p_currentNode -> edgeWeightInputData);									//- returns the edgeWeightInputData of the dNodeType struct if the count == index
		} 
		else
		{
			count++;																		//- Increment count by 1
			p_currentNode = p_currentNode -> nextAddress;									//- Set the node we are look at to the next address
		}
	}

	std::cout << "ERROR: The element requested does not exist." << std::endl;				//- If we come to this line then the user of the function has asked for an element not existing in our linked list
	//return 0;
}

/*********************************************************************************
* Description:		This function returns the specified node by reference. 
*					Returns the nodes &address at the specified index. 
*
* Returns:			struct dNodeType
*
* Parameters:		int index; Index of the node to retrieve in the Linked List.
*					
* Preconditions:	NIL
*
* Postconditions:	NIL
*********************************************************************************/
template <class T>  
T& linkedListType<T>::getNodeAt_Reference(int index)										//- Searchs Linked List for the nth node in the list as specified by the index
{
	dNodeType<T>* p_currentNode = head;														//- Pointer to move along list and keep track
	int count = 0;																			//- Creating a counter that starts at zero

	while ( p_currentNode != NULL )															//- Search through the list, looking for foundNode
	{
		if ( count == index )
		{
			return (p_currentNode -> edgeWeightInputData);									//- returns the edgeWeightInputData of the dNodeType struct if the count == index
		} 
		else
		{
			count++;																		//- Increment count by 1
			p_currentNode = p_currentNode -> nextAddress;									//- Set the node we are look at to the next address
		}
	}

	std::cout << "ERROR: The element requested does not exist." << std::endl;				//- If we come to this line then the user of the function has asked for an element not existing in our linked list
	//_NO_RETURN;
}
/*********************************************************************************
* Description:		This function inserts edgeWeightInputData immediately after the specified   
*					node in the Linked List. 
*
* Returns:			NIL
*
* Parameters:		int index; Index of where the edgeWeightInputData is to be inserted after.
*					const T& newedgeWeightInputData; The T edgeWeightInputData to be inserted.
*
* Preconditions:	NIL
*
* Postconditions:	Inserted the Node succesfully or failed whilst attempting to.
*********************************************************************************/
template <class T>	
void linkedListType<T>::insertedgeWeightInputDataAfter(int index, const T& newedgeWeightInputData)	//- Inserts edgeWeightInputData at specified point in the Linked List
{
	int count = 0;																			//- Creating a counter that starts at zero

	dNodeType<T>* p_currentNode = head;														//- Pointer to move along list and keep track

	dNodeType<T> *newNode;																	//- Pointer for the new Node

	newNode = new dNodeType<T>;																//- New Node is being created
	newNode -> edgeWeightInputData = newedgeWeightInputData;								//- Store the new edgeWeightInputData in the new node
	newNode -> nextAddress = NULL;															//- Make nextAddress point to NULL. E.G it is the last node in the Linked List

	while ( p_currentNode != NULL && count < index + 1)										//- Iterate through list until reaching the specified index.
	{
		if ( count == index )
		{
			newNode -> nextAddress = p_currentNode -> nextAddress;
			p_currentNode -> nextAddress = newNode;	
			size++;
			std::cout << "Node Successfully inserted" << std::endl;	
		} 
		else
		{
			count++;																		//- Increment count by 1
			p_currentNode = p_currentNode -> nextAddress;									//- Set the node we are look at to the next address
		}
	}
}
/*********************************************************************************
* Description:		This function overloads the operator[] of the Linked List. 
*					Returns the &address of the specified index. E.G list[i];
*
* Returns:			NIL
*
* Parameters:		int index; Index of the node to return.
*					
* Preconditions:	NIL
*
* Postconditions:	Returns the address of the node in the Linked List.
*********************************************************************************/
template <class T> 
T& linkedListType<T>::operator[](int index)													//- Overloading the [] for the linkedList Class, 
{
	return getNodeAt_Reference(index);														//- Will return the &address of the node at the specified index.
}

/*********************************************************************************
* Description:		This function deletes the node at the specified index in the 
*					Linked List.
*
* Returns:			NIL
*
* Parameters:		int index; index of the node to delete
*					
* Preconditions:	NIL
*
* Postconditions:	NIL
*********************************************************************************/
template <class T>  
void linkedListType<T>::deleteNodeAt(int index)											//- Searchs Linked List for the nth node in the list as specified by the index
{
	int count = 0;																		//- Creating a counter that starts at zero

	bool foundNode;																		//- FoundNode to show if found or not
	dNodeType<T>* p_currentNode;														//- Pointer to move along list and keep track
	dNodeType<T>* p_trailCurrentNode;													//- Pointer that follows behing current Pointer

	if ( head == NULL )																	//- Case 1
	{
		cerr<< "ERROR: You can not delete a node from an empty List\n";
	}
	else
	{
		if ( index < 1 )																//- Case 2
		{
			p_currentNode = head;
			head = head -> nextAddress;
			size--;																		//- Decrease the size of the Linked List
			count++;

			if( head == NULL )															//- Check to see if Linked List only has one node
			{
				tail = NULL;					
				delete p_currentNode;													//- Delete the node from Linked List
			}
		}
		else																			//- Search the Linked List for the node to be deleted
		{
			foundNode = false;
			p_trailCurrentNode = head;													//- Trail pointer points to the first node in the Linked List
			p_currentNode = head -> nextAddress;										//- Current pointer points to the second node in the Linked List

			while ( p_currentNode != NULL && !foundNode )								//- Search through the list, looking for foundNode
			{
				if ( count != index )
				{
					p_trailCurrentNode = p_currentNode;
					p_currentNode = p_currentNode -> nextAddress;
					count++;
				} 
				else
				{
					foundNode = true;
				}
			}
			if ( foundNode )															//- Case 3: If the node to be deleted is found, delete the node
			{
				p_trailCurrentNode -> nextAddress = p_currentNode -> nextAddress;
				size--;																	//- Decreasing the size of the Linked List by 1
				if ( tail == p_currentNode)
				{
					tail = p_trailCurrentNode;
					delete p_currentNode;												//- Delete the node from Linked List
				}
				else
				{
					cout<<"ERROR: The Node edgeWeightInputData to be deleted is not contained within the List."<<endl;
				}
			}
		}
	}
}	

/*********************************************************************************
* Description:		This function prints out the contents of the
*					Linked List.
*
* Returns:			NIL
*
* Parameters:		const linkedListType<T>& list;
*					
* Preconditions:	edgeWeightInputData must be capable of using ostream operator <<  
*
* Postconditions:	Printed out the T edgeWeightInputData succesfully or program has terminated. 
*********************************************************************************/
template <class T>
void linkedListType<T>::printLinkedList() const										//- Outputs the Linked List
{
	dNodeType<Type> *current;														//- Pointer that iterates through the list
	current = head;																	//- set current so that it points to the first node

	while(current != NULL)
	{
		cout << list[i] -> edgeWeightInputData << " ";
		cout << endl;
		current = current ->nextAddress;											//- moves to the next address
	}
}	//- End printLinkedList
#endif 
///////////////////////////////////////////////////////////////////////////////////
// END OF FILE
///////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
// Filename:		Main.cpp
// Author:			Charles Nelson - s2884951
// Date Modified:	26/05/2014 Created
//					31/05/2014 Updated 
// Description:		This file contains the main function
////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <stdio.h>      
#include <stdlib.h>     
#include <time.h>       
#include <iomanip>
#include <sstream>
#include <limits>
#include "MinimalSpanTreeType_H.h"

using namespace std;

//- PLEASE NOTE THAT THE MAX NUMBER OF NODES THIS TREE CAN HANDLE IS 150, IF A LARGER TREE IS REQUIRED THEN THIS VALUE WILL NEED TO BE MANUALLY CHANGED BEFORE RUNNING.

int main (void)
{	
	const int MAX_NO_NODES =  150;																								//- Max no. of nodes
	msTreeType<int, 150> spanTree;																								//- Declaring a msTreeType of int and size 100 spanTree 

	std::cout	<< "\n"																							
				<< "PLEASE NOTE MAX NO. OF NODES FOR A GRAPH IS CURRENTLY SET TO 150."			<< "\n"		<< "\n"		
				<< "Hello, I am a program for testing the prim1 & prim2 formula."				<< "\n"		<< "\n"
				<< "Please specifiy a positive number of Nodes that you want in your Graph."	<< "\n"		<< "\n"
				<< "If you enter a negative number I will provide my own input Graph -"			<< "\n"
				<< "from the supplied graph.txt file."											<< "\n"		<< "\n"			
				<< "If you enter in 0, I will use the input Graph -"							<< "\n" 
				<< "from figure 12.16 - Using C++ by D.S Malik."								<< "\n"		<< "\n"
				<< "If you wish to exit, enter \"q\" and press ENTER."							<< "\n"		<< "\n"
				<< "Otherwise, please enter in the number for calculation and press ENTER."		<< "\n"		<< std::endl;

	while ( true )																												//- The Loop only ends when an error occurs or user selects q || Q to quit the program.
	{
		int inputSize;																											//- Variable to store the number of nodes the user has specified
		cin >> inputSize;																										//- Grab the input entered by the user, if it is an Int then store it in inputSize variable
		if ( !cin )
		{
			cin.clear();																										//- Clear the error flags of cin
			string userInput =" ";
			getline( cin, userInput );
			if ( userInput[0] == 'q' || userInput[0] == 'Q' )
			{
				std::cout	<< "You have selected to quit the program." << "\n"
							<< "Quiting the program now...."			<< std::endl;
				system( "PAUSE" );
				return 0;																										//- Quit the program successfully as the user has entered q or Q.
			}																													//- End If
			else
			{
				cout << "Error please enter a numeric value"	<< std::endl;
				cin.clear();																									//- Clear the error flags of cin
				cin.ignore( numeric_limits <streamsize>::max(), '\n' );															//- Clear out the input buffer of cin
			}																													//- End Else
		}																														//- End If
		else
		{
			if ( inputSize < MAX_NO_NODES )																						//- Check user input size isnt larger then the Max number of nodes
			{
				spanTree.createSpanningGraph( inputSize );																		//- Create graph with the max size as specified by the user				
			
				if ( inputSize == 0 )																							//- Case 1: Figure 12.16 from d.s malik c++ textbook is printed to console 
				{
					inputSize = 7;
					for  ( int i = 0; i < inputSize; i++ )																		//- For showing the different MST's using different starting Nodes
					{
						cout << " Printing out the MST below - via Prim's Algorithm " << endl;	
			
						spanTree.minimalSpanning( i );																			//- Starting Vertex is specified default is 0 in this case. 
						spanTree.printTreeAndWeight();																			//- Prints the Tree's nodes and their edge weights wtih the total the Weight at the bottom.  

						cout << " Printing  out the MST below - via Prim2's Algorithm " << endl;	
			
						spanTree.prim2MST( i );																					//- Starting Vertex is specified default is 0 in this case. 
						spanTree.printTreeAndWeight();																			//- Prints the Tree's nodes and their edge weights wtih the total the Weight at the bottom.  
					}
				}
				else if ( inputSize < 0 )																						//-	Case 2: Graph for graph.txt file is printed to console 
				{
					bool stop = false;																							//- Value to check if user wants to stop entering new source vertex's
					while (!stop )																								//- Loop only ends if the user asks to return to the main program via entering f or F
					{																											//- For showing the different MST's using different starting Nodes
						int graphSize = spanTree.readNoOfNodesFromGraphFile();													//- Find out and Calculate the number of nodes in the graph.txt file
						if ( graphSize == -1 )
						{
							std::cout	<< "There seem's to be an error with your input file."				<< "\n"
										<< "Please check it and ensure that it is in the correct format."	<< "\n"
										<< "We are now returning you to the main program."					<< std::endl;
							break;																								//- Returns to the main program
						}
						std:: cout	<< "\n"	
									<< "Please input a number from 0 to "								<< graphSize-1 
									<< " that will be the source vertext(node) -"						<< "\n" 
									<<" for the minimalSpanning Tree."									<< "\n"
									<< "If you wish to return to the main program please enter f or F"	<< "\n" 
									<< " "																<< std::endl;			//- Informs user of their options
						
						int nodeToStartMinTreeFrom;																				//- Variable to store where to start the Minimal Spanning Tree from that the user has specified
						cin >> nodeToStartMinTreeFrom;																			//- Grab the input entered by the user, if it is an Int then store it in nodeToStartMinTreeFrom variable
					
						if ( !cin )																								//- Enter's here if the input is not an int value
						{
							cin.clear();																						//- Clear the error flags of cin
							string userInput =" ";
							getline( cin, userInput );
							if ( userInput[0] == 'f' || userInput[0] == 'f' )													//- Checks if user wants to return to the main program
							{
								std::cout	<< "You have selected to stop testing this matrix." << "\n"
											<< "Returning to the main program now...."			
											<< "\n"												<< std::endl;
								break;
							}
							cin.ignore( numeric_limits <streamsize>::max(), '\n' );												//- Clear out the input buffer of cin	
							std:: cout	<< "Please specifiy a source node from 0 to "					<< inputSize-1 
										<< " that you wish to start the minimalSpanning Tree from."		<< std::endl;			//- Informs user to enter correct value
						}											
																		
						if ( nodeToStartMinTreeFrom >= 0 && nodeToStartMinTreeFrom <= graphSize-1 )								//- For showing the different MST's using different starting Nodes. We check here to make sure user doesnt enter a node that doesn't exist in the Tree 
						{
								cout << " Printing out the MST below - via Prim's Algorithm " <<  "\n" << endl;	
			
								spanTree.minimalSpanning( nodeToStartMinTreeFrom );												//- Starting Vertex is specified default is 0 in this case. 
								spanTree.printTreeAndWeight();																	//- Prints the Tree's nodes and their edge weights wtih the total the Weight at the bottom.  

								cout << " Printing  out the MST below - via Prim2's Algorithm " << "\n" << endl;	
			
								spanTree.prim2MST( nodeToStartMinTreeFrom );													//- Starting Vertex is specified default is 0 in this case. 
								spanTree.printTreeAndWeight();																	//- Prints the Tree's nodes and their edge weights wtih the total the Weight at the bottom.  
						}
					}
				}
				else if ( inputSize > 0 )																						//- Case 3: The randomly generated graph is printed to console  
				{
					bool stop = false;																							//- Value to check if user wants to stop entering new source vertex's
					while (!stop )																								//- Loop only ends if the user asks to return to the main program via entering f or F
					{
						std:: cout	<< "\n"	
									<< "Please input a number from 0 to "								<< inputSize-1 
									<< " that will be the source vertext(node) -"						<< "\n" 
									<<" for the minimalSpanning Tree."									<< "\n"
									<< "If you wish to return to the main program please enter f or F"	<< "\n" 
									<< " "																<< std::endl;			//- Informs user of their options
						
						int nodeToStartMinTreeFrom;																				//- Variable to store where to start the Minimal Spanning Tree from that the user has specified
						cin >> nodeToStartMinTreeFrom;																			//- Grab the input entered by the user, if it is an Int then store it in nodeToStartMinTreeFrom variable
					
						if ( !cin )
						{
							cin.clear();																						//- Clear the error flags of cin
							string userInput =" ";
							getline( cin, userInput );
							if ( userInput[0] == 'f' || userInput[0] == 'f' )													//- Checks if user wants to return to the main program
							{
								std::cout	<< "You have selected to stop testing this matrix." << "\n"
											<< "Returning to the main program now...."			
											<< "\n"												<< std::endl;
								break;
							}
							cin.ignore( numeric_limits <streamsize>::max(), '\n' );												//- Clear out the input buffer of cin	
							std:: cout	<< "Please specifiy a source node from 0 to "					<< inputSize-1 
										<< " that you wish to start the minimalSpanning Tree from."		<< std::endl;			//- Informs user to enter correct value
						}																								
						else if ( nodeToStartMinTreeFrom >= 0 && nodeToStartMinTreeFrom <= inputSize-1 )						//- For showing the different MST's using different starting Nodes. We check here to make sure user doesnt enter a node that doesn't exist in the Tree 
						{
							cout << " Printing out the MST via Prim's Algorithm " << endl;	
			
							spanTree.minimalSpanning( nodeToStartMinTreeFrom );													//- Starting Vertex is specified default is 0 in this case. 
							spanTree.printTreeAndWeight();																		//- Prints the Tree's nodes and their edge weights wtih the total the Weight at the bottom.  

							cout << " Printing  out the MST via Prim2's Algorithm " << endl;	
			
							spanTree.prim2MST( nodeToStartMinTreeFrom );														//- Starting Vertex is specified default is 0 in this case. 
							spanTree.printTreeAndWeight();																		//- Prints the Tree's nodes and their edge weights wtih the total the Weight at the bottom.  
						}
					}
				}
			
				std::cout << "If you want to go again, please enter a new input and press ENTER."	<< "\n"	<< std::endl;
				std::cout << "Otherwise if you wish to exit, enter \"q\" and press ENTER."			<< "\n" << std::endl;
			}
			else 
			{
				std::cout << "Please re-enter a size that is less than 150 nodes."	<< std::endl;
				system( "PAUSE" );
			}
		}																														//- End Else 		
	}																															//- End While
	return 0;
}
///////////////////////////////////////////////////////////////////////////////////
// END OF FILE
///////////////////////////////////////////////////////////////////////////////////
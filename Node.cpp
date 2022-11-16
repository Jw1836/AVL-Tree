	#include "Node.h"
    #include<stdlib.h>
    
    Node :: Node(){
        data = 0;
        leftChild = NULL;
        rightChild = NULL;
        height = 0; 
    }
    Node :: Node(int _data){
        data = _data;
        leftChild = NULL;
        rightChild = NULL;
        height = 0; 
    }
	Node :: ~Node(){}

	/*
	* Returns the data stored in this node
	*
	* @return the data stored in this node.
	*/
	int Node :: getData() const{
        return data; 
    }

	/*
	* Returns the left child of this node or null if empty left child.
	*
	* @return the left child of this node or null if empty left child.
	*/
	NodeInterface * Node :: getLeftChild() const{
        return leftChild; 
    }

	/*
	* Returns the right child of this node or null if empty right child.
	*
	* @return the right child of this node or null if empty right child.
	*/
	NodeInterface * Node :: getRightChild() const{
        return rightChild; 
    }

	/*
	* Returns the height of this node. The height is the number of nodes
	* along the longest path from this node to a leaf.  While a conventional
	* interface only gives information on the functionality of a class and does
	* not comment on how a class should be implemented, this function has been
	* provided to point you in the right direction for your solution.  For an
	* example on height, see page 448 of the text book.
	*
	* @return the height of this tree with this node as the local root.
	*/
	int Node :: getHeight(){
        return height;
    }
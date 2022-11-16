
#pragma once

#include "NodeInterface.h"
#include "AVLInterface.h"
#include "Node.h"

using namespace std;

class AVL: public AVLInterface{
public:
	AVL();
	~AVL();

	//Please note that the class that implements this interface must be made
	//of objects which implement the NodeInterface

	/*
	* Returns the root node for this tree
	*
	* @return the root node for this tree.
	*/
	NodeInterface * getRootNode() const;

	/*
	* Attempts to add the given int to the AVL tree
	* Rebalances the tree if data is successfully added
	*
	* @return true if added
	* @return false if unsuccessful (i.e. the int is already in tree)
	*/
	bool add(int data);

	/*
	* Attempts to remove the given int from the AVL tree
	* Rebalances the tree if data is successfully removed
	*
	* @return true if successfully removed
	* @return false if remove is unsuccessful(i.e. the int is not in the tree)
	*/
	bool remove(int data);

	/*
	* Removes all nodes from the tree, resulting in an empty tree.
	*/
	void clear();
private:
	Node* root; 
	void clearHelper(Node* ptr);
	bool IsBalanced(Node* ptr); 
	void updateHeight(Node*& ptr);
	int getHeight(Node* ptr);
	bool addHelper(Node*& ptr, int data);
	bool removeHelper(Node*& ptr, int data);
	void rebalance(Node *&ptr);
	int difference(Node *&ptr);
	void rightRotate(Node*& ptr);
	void leftRotate(Node*& ptr);
	void rightleftRotate(Node*& ptr);
	void leftrightRotate(Node*& ptr);
	Node* GetInorder(Node*& ref);
	int calcHeight(Node*& ptr);


};


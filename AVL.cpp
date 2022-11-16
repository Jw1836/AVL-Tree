#include <stdlib.h>
#include <algorithm>
#include "AVL.h"
#include<iostream>

	AVL :: AVL(){root = NULL;}
	AVL :: ~AVL(){}

	NodeInterface* AVL :: getRootNode() const{
		return root;
	}
 	/*
	* Attempts to add the given int to the AVL tree
	* Rebalances the tree if data is successfully added
	*
	* @return true if added
	* @return false if unsuccessful (i.e. the int is already in tree)
	*/
	void AVL :: leftRotate(Node*& node){
		Node* newRoot = node->rightChild;
		node->rightChild = newRoot->leftChild;
		newRoot->leftChild = node; 
		node = newRoot;  
		updateHeight(newRoot->leftChild);
		updateHeight(newRoot);


	}
	void AVL :: rightleftRotate(Node*& ptr){
		rightRotate(ptr->rightChild);
		leftRotate(ptr);
		updateHeight(ptr->rightChild);
		updateHeight(ptr);
	}
	void AVL :: leftrightRotate(Node*& ptr){
		leftRotate(ptr->leftChild);
		rightRotate(ptr);
		updateHeight(ptr->leftChild);
		updateHeight(ptr);
	}
	void AVL :: rightRotate(Node*& ptr){
		Node* oldptr = ptr;
		Node* newptr = ptr->leftChild; 
		ptr = newptr; 
		oldptr->leftChild = newptr->rightChild;
		newptr->rightChild = oldptr;
		updateHeight(oldptr);
		updateHeight(newptr);
	}
	


	 bool AVL :: add(int data){
		return addHelper(root, data);
		
	 }
	 bool AVL :: addHelper(Node*& T, int data){
		if(T==NULL){
			T = new Node(data);
			return true;
		}
		if(T->data == data){
			return false;
		}
		else if(T->data > data){
			if(addHelper(T->leftChild, data) == true){
				updateHeight(T);
				rebalance(T);
				return true; 
			}
			else{
				return false; // did not insert
			}
		}
		else if(T->data < data){
			if(addHelper(T->rightChild, data) == true){
				updateHeight(T);
				rebalance(T); 
				return true; 
			}
		}
		return false; 
	 }
	Node* AVL :: GetInorder(Node*& ref){
		Node* ptr = ref->leftChild;
		while(ptr->rightChild != NULL){
			ptr = ptr->rightChild;
		}
		return ptr; 
	}

	bool AVL :: remove(int data){
		return removeHelper(root, data); 
	}
	bool AVL :: removeHelper(Node*& T, int data){
		
		if(T == NULL){
			// data is not in tree, do nothing
			return false;
		}
		if(T->data > data){
			bool isRemoved = removeHelper(T->leftChild, data); 
			if(isRemoved){
				updateHeight(T);
				rebalance(T); 
			}
			return isRemoved;
		}
		else if(T->data < data){
			bool isRemoved = removeHelper(T->rightChild, data); 
			if(isRemoved){
				updateHeight(T);
				rebalance(T); 
			}
			return isRemoved;
		}
		else if(T->data == data){
			if((T->leftChild != NULL) && (T->rightChild != NULL)){
				// we have two children
				Node* ptr = GetInorder(T);
				T->data = ptr->data;
				// updateHeight(T);
				// rebalance(T); 
				bool isRemoved = removeHelper(T->leftChild, ptr->data);
				if(isRemoved){
					updateHeight(T);
					rebalance(T);
				}
				return isRemoved;
			}
			else if(T->leftChild != NULL){
				Node* temp = T;
				T = T->leftChild;
				delete temp;
				temp = NULL;
				// updateHeight(T);
				// rebalance(T);
				return true; 
			}
			else if(T->rightChild != NULL){
				Node* temp = T;
				T = T->rightChild;
				delete temp;
				temp = NULL;
				// updateHeight(T);
				// rebalance(T);
				return true; 
			}
			else{
				// no children so we can safely delete this leaf node
				// updateHeight(T);
				// rebalance(T); 
				delete T; 
				T = NULL; 
				return true; 
			}
		}
	return true;
	}
	// four cases of imbalance
	//1. Right-right imbalance, left rotate
	//2. left-left imbalance, right rotate
	// 
	int AVL :: getHeight(Node* ptr){
		if(ptr == NULL){
			return -1;
		}
		else{
			return ptr->height; 
		}
	}
	void AVL :: updateHeight(Node*& ptr){
		int left = getHeight(ptr->leftChild);
		int right = getHeight(ptr->rightChild);

		ptr->height = max(left, right) + 1; 
	}


	/*
	* Removes all nodes from the tree, resulting in an empty tree.
	*/
	void AVL :: clearHelper(Node* ptr){
		if(ptr != NULL){
			clearHelper(ptr->leftChild);
			clearHelper(ptr->rightChild);
		}
		delete ptr; 
		ptr = NULL; 
	}
	void AVL :: clear(){
		clearHelper(root);
		root = NULL; 
	}
	bool AVL :: IsBalanced(Node* ptr){
		if(abs(ptr->leftChild->height - ptr->rightChild->height) <=1 ){
			return true;
		}
		else{
			return false; 
		}
	}
	int AVL :: difference(Node *&ptr){
		int leftHeight;
		int rightHeight;
		if(ptr->leftChild == NULL){
			leftHeight = -1;
		}
		else{ leftHeight = ptr->leftChild->height; }

		if(ptr->rightChild == NULL){
			rightHeight = -1;
		}
		else{ rightHeight = ptr->rightChild->height;}
		
		return leftHeight - rightHeight; 
	}
	int AVL :: calcHeight(Node*& ptr){
		if(ptr == NULL){
			return -1;
		}
		int leftHeight = calcHeight(ptr->leftChild);
		int rightHeight = calcHeight(ptr->rightChild);
		return max(leftHeight, rightHeight) + 1;
	}
	void AVL :: rebalance(Node *&ptr){
		// int leftHeight;
		// int rightHeight;
		// if(ptr->leftChild == NULL){
		// 	leftHeight = -1;
		// }
		// else{ leftHeight = ptr->leftChild->height; }

		// if(ptr->rightChild == NULL){
		// 	rightHeight = -1;
		// }
		// else{ rightHeight = ptr->rightChild->height;}
		int balance = difference(ptr); 
 
														
		// if left - right > 1 look at left subtree
		if(balance > 1){ // left imbalance
			if(difference(ptr->leftChild) >= 0){
				cout << "in right rotate" << ptr->data << endl; 
				rightRotate(ptr);
			}
			else{
				leftrightRotate(ptr);
			}
		}
		else if(balance < -1){ // right imbalance
			if((difference(ptr->rightChild) <= 0)){ // right right imbalance
				leftRotate(ptr); 
			}
			else{
				rightleftRotate(ptr);
			}
		}

	}
	

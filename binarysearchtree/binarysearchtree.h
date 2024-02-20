/*	Kendrick Hardy
	z1945923
	CSCI 340-2
	I certify that this is my own work and where appropriate an extension
	of the starter code provided for the assignment.
*/

#include <iostream>

#ifndef BINARYSEARCHTREE_H_
#define BINARYSEARCHTREE_H_

#include "btree.h"

template <typename T>
class BinarySearchTree : public BinaryTree<T>
{
public:
    void Insert(const T &x);       // inserts node with value x
    bool Search(const T &x) const; // searches leaf with value x
    bool Remove(const T &x);       // removes leaf with value x
private:
    void _Insert(Node<T> *&, const T &);      // private version of insert
    bool _Search(Node<T> *, const T &) const; // private version of search
    void _Remove(Node<T> *&, const T &);      // private version of remove
    bool _Leaf(Node<T> *node) const;          // checks if node is leaf
};

/**
 * Inserts node into a tree
 *
 * @param node A node in the tree
 * @param value The value to be inserted
 *
 * *******************************************************************************************/
template <typename T> void BinarySearchTree<T>::_Insert(Node<T> * &node, const T &value){
	if(node){
		if(value > node->data){
			_Insert(node->right, value);
		}
		else if(value < node->data){
			_Insert(node->left, value);
		}
		else{
		}
	}
	else if(node == NULL){
		node = new Node<T>(value);
	}
} //End of _Insert

/**
 * Search tree value
 *
 * @param node A node in the tree
 * @param value The value to search for
 *
 * @returns true if the value is found, false otherwise
 * **********************************************************************************************/
template <typename T> bool BinarySearchTree<T>::_Search(Node<T> * node, const T &value) const{
	if(node){
		if(value == node->data){
			return true;
		}
		else if(value > node->data){
			return (_Search(node->right, value));
		}
		else if(value < node->data){
			return(_Search(node->left, value));
		}
	}
	return false;
} //End of _Search

/**
 * checks if a node is a leaf
 *
 * @param node A node in the tree
 *
 * @returns true if the node is a lead, false otherwise
 * **********************************************************************************/
template <typename T> bool BinarySearchTree<T>::_Leaf(Node<T> * node) const{
	if((node->left) || (node->right)){
		return false;
	}
	else
		return true;
} //End of _Leaf

/**
 * Removes a node with a certain value in the tree
 *
 * @param node A node in the tree
 * @param value The value of the node to be removed
 * *******************************************************************************************/
template <typename T> void BinarySearchTree<T>::_Remove(Node<T> * &node, const T &value){
	if(node){
		if(value < node->data){
			_Remove(node->left, value);
		}
		else if(value > node->data){
			_Remove(node->right, value);
		}
		else{
			if(_Leaf(node)){
				delete node;
				node = NULL;
			}
		}
	}
} //End of _Remove

/**
 * Inserts a value into a tree
 *
 * @param value The value to insert
 * *********************************************************************************/
template <typename T> void BinarySearchTree<T>::Insert(const T &value){
	_Insert(this->root, value);
} //End of Insert

/**
 * Searches a tree for a value
 *
 * @param value The value to search for
 *
 * @returns true if value is found, false otherwise
 * ********************************************************************************************/
template <typename T> bool BinarySearchTree<T>::Search(const T &value) const{
	return _Search(this->root, value);
} //End of Search

/**
 * Removes a leaf with a certain value from a tree
 *
 * @param value The value of the leaf to be deleted
 *
 * @return true if the leaf is removed, false otherwise
 * **************************************************************************/
template <typename T> bool BinarySearchTree<T>::Remove(const T &value){
	if(_Search(this->root, value))
	{
		_Remove(this->root, value);
		return true;
	}
	return false;
} //End of Remove

#endif // End of BINARYSEARCHTREE_H_

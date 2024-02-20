#ifndef H_BTREE
#define H_BTREE

#include "node.h"

typedef enum {left_side, right_side } SIDE;

SIDE rnd(){ 
    return rand()%2 ? right_side : left_side;
}// End of rnd()

template <typename T> class BinaryTree{

public:
    BinaryTree();                                      // default constructor
    unsigned     getSize() const;                      // returns size of tree
    unsigned     getHeight() const;                    // returns height of tree
    virtual void Insert(const T&);                     // inserts node in tree
    void         Inorder(void (*)(const T&));          // inorder traversal of tree

protected:
    Node<T> *root;                                      // root of tree

private:
    unsigned _getSize(Node<T> *) const;                 // private version of getSize()
    unsigned _getHeight(Node<T> *) const;               // private version of getHeight()
    void     _Insert(Node<T> *&, const T&);             // private version of Insert()
    void     _Inorder(Node<T> *, void (*)(const T&));   // private version of Inorder()
};

/**
 * Default contructor of tree
 * ******************************************************/
template <typename T> BinaryTree<T>::BinaryTree(){
	root = NULL;
} //End of BinaryTree

/**
 * gets the size of a tree
 *
 * @param node A node in the tree
 *
 * @returns size of tree
 * **********************************************************/
template <typename T> unsigned BinaryTree<T>::_getSize(Node<T> *node) const{
	if(node == NULL){
		return 0;
	}

	unsigned leftSize = _getSize(node->left);
        unsigned rightSize = _getSize(node->right);

	return leftSize + rightSize + 1;
} //End of _getSize

/**
 * Gets the height of a tree
 *
 * @param node A node in the tree
 *
 * @returns The height of tree
 *
 * @note Uses max
 * ***********************************************************************************/
template <typename T> unsigned BinaryTree<T>::_getHeight(Node<T> *node) const{
	if(node == NULL){
		return 0;
	}

	unsigned leftHeight = _getHeight(node->left);
	unsigned rightHeight = _getHeight(node->right);

	return (max(leftHeight, rightHeight) + 1);
} //End of _getHeight

/**
 * Inserts node into tree
 *
 * @param node A node in the tree
 * @param value The value to be inserted
 *******************************************************************************************/
template <typename T> void BinaryTree<T>::_Insert(Node<T> *&node, const T&value){
	if(node == NULL){
		node = new Node<T>(value);
	}
	else if(rnd() == left_side){
		_Insert(node->left, value);
	}
	else{
		_Insert(node->right, value);
	}
} //End of _Insert

/**
 * Does inorder traversal of tree and performs a function on each element
 *
 * @param node A node in the tree
 * @param func A function performed on the data
 *
 * ************************************************************************************************/
template <typename T> void BinaryTree<T>::_Inorder(Node<T> *node, void (*func)(const T&)){
	if(node){
		_Inorder(node->left, func);
		func(node->data);
		_Inorder(node->right, func);
	}
} //End of _Inorder

/**
 * Gets of size of tree
 *
 * @returns the size of tree
 *
 * @note Uses _getSize
 * *********************************************************************/
template <typename T> unsigned BinaryTree<T>::getSize() const{
	return _getSize(root);
} //End of getSize

/**
 * Gets the height of tree
 *
 * @returns the height of a tree
 *
 * @note Uses _getHeight
 * *********************************************************************/
template <typename T> unsigned BinaryTree<T>::getHeight() const{
	return _getHeight(root);
} //End of getHeight

/**
 * Insert an element into a tree
 *
 * @param value The value to be inserted
 *
 * @note Uses _Insert
 * *****************************************************************/
template <typename T> void BinaryTree<T>::Insert(const T&value){
	_Insert(root, value);
} //End of Insert

/**
 * Does Inorder traversal on a tree and performs a function on each element
 *
 * @param func A function performed on the data
 *
 * @note Uses _Inorder
 * **********************************************************************************/
template <typename T> void BinaryTree<T>::Inorder(void (*func)(const T&)){
	_Inorder(root, func);
} //End of Inorder

#endif // End of H_BTREE

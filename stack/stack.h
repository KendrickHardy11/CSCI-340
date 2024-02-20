/*	Kendrick Hardy
	z1945923
	CSCI 340-2

	I certify that this is my own work and where appropriate an extension
	of the starter code provided for the assignment
*/

#ifndef STACK_H
#define STACK_H
#include <queue>

template<typename T>
class Stack
{
private:
    std::queue<T> q1;	// These queues are where the stack's elements 
    std::queue<T> q2;	// are to be saved.

public:
    bool empty() const;
    int size() const;
    const T& top();
    void push(const T &val);
    void pop();
};


// Note that the members of a template go into a .h file since 
// they are not compiled directly into a .o file like the members 
// of regular/non-template classes.


/**
 * Checks if a stack has elements in it.
 *
 * @return true if the stack is empty and false if not.
 *
 * @note this uses the empty member function.
 * *********************************************************************/
template <typename T> bool Stack<T>::empty() const{
	if(q1.empty()){
		return true;
	}
	else{
		return false;
	}
} //End of empty()

/**
 * Gives size of a stack.
 *
 * @return the size of the stack.
 *
 * @note uses the size member function.
 * *********************************************************/
template <typename T> int Stack<T>::size() const{
	return q1.size();
} //End of size()

/**
 * Gives a refernce to the newest element.
 *
 * @return the last element in the stack.
 *
 * @note uses the back memeber function.
 * *********************************************************/
template <typename T> const T& Stack<T>::top(){
	return q1.back();
} //End of top()

/**
 * Adds an element to the stack.
 *
 * @param val The value that will be added to the stack.
 *
 * @note uses the push() member function.
 * *****************************************************************/
template <typename T> void Stack<T>::push(const T &val){
	q1.push(val);
} //End of push()

/**
 * removes the newest element.
 *
 * @note uses the swap() member function.
 * ******************************************************/
template <typename T> void Stack<T>::pop(){
	while(q1.size() > 1){
		q2.push(q1.front());
		q1.pop();
	}

	q1.pop();

	std::swap(q1, q2);
} //End of pop()






#endif // STACK_H

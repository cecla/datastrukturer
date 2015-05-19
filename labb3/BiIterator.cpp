/**********************************************
* File: BiIterator.cpp                        *
* Author: Aida Nordman                        *
* Course: TND004, Lab 2                       *
* Date: VT2, 2014                             *
* Description: class biIterator               *
* Represents bidirectional iterators          *
***********************************************/


#include "BiIterator.h"


#ifndef DOXYGEN_SHOULD_SKIP_THIS


// Constructor
BiIterator::BiIterator(Node *ptr)
 : current(ptr)
 {
     
 }


//Dereferencing operator
//ELEMENT& BiIterator::operator*() const
//{
    //ADD CODE
//}


//Member access operator
ELEMENT* BiIterator::operator->() const
{
    //ADD CODE
   cout << "in operator(): " << current->value.first << endl;
    return &current->value;
}


//Equality comparison operator
bool BiIterator::operator==(const BiIterator &it) const
{
    //ADD CODE
    // check if current node is the same as the node of the iterator it
    if (it.current == current)
    {
        return true;
    }
    return false;
}


//Inequality comparison operator
bool BiIterator::operator!=(const BiIterator &it) const
{
   //ADD CODE
    if (it.current != current)
    {
        return true;
    }
    return false;
}


//Pre increment operator
BiIterator& BiIterator::operator++()
{
   //ADD CODE
    BiIterator it = current;

    if (!it.current->l_thread)
    {
        cout << "!current->l_thread" << endl;
        it.current = it.current->left;
        return *this;
    }
    it.current = it.current->right;
    cout << "jag gjorde aldrig if" << endl;
    
    return *this;
}



//Pos increment operator: see page 277 and 278 of C++ direkt
BiIterator BiIterator::operator++(int)
{
   //ADD CODE
    if (!current->l_thread)
    {
        cout << "!current->l_thread" << endl;
        current = current->left;
        return *this;
    }
    cout << "jag gjorde aldrig if" << endl;
    
    return *this;
}

//Pre decrement operator
BiIterator& BiIterator::operator--()
{
   //ADD CODE
    return *this;
}

//Pos decrement operator
BiIterator BiIterator::operator--(int)
{
   //ADD CODE
    return *this;
}

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

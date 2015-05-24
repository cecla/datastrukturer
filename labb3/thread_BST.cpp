/********************************************************
* File: threaded_BST.cpp                                *
* Author: Aida Nordman                                  *
* Course: TND004, Lab 3                                 *
* Date: VT2, 2014                                       *
* Description: class BST_threaded representing          *
*              a threaded binary search tree            *
*********************************************************/

#include "threaded_BST.h"

#ifndef DOXYGEN_SHOULD_SKIP_THIS

using namespace std;


//Default Constructor: create an empty tree
//Empty tree has a dummy node as root
//The real tree is stored as left child of the dummy root
BST_threaded::BST_threaded()
 : counter(0)
{
    ELEMENT e("",0);
    root = new Node(e, nullptr,nullptr);

}


//destructor
BST_threaded::~BST_threaded()
{
  delete root;
}


//Test if the tree is empty
bool BST_threaded::empty() const
{
    //ADD CODE
    // check if the root has any subtrees, if not, the tree is empty
    if(counter == 0)
    {
        return true;
    }
    return false;
}

//Return mumber of keys (elements) stored in the tree
int BST_threaded::size() const
{
    return counter;
}


//Insert v in the tree
void BST_threaded::insert(ELEMENT v)
{
    if (empty())
    {
        //Insert first node of the BST has a left child of the BST
        root->left = new Node(v, root, root);
        root->left->l_thread = root->left->r_thread = true;

        root->l_thread = false;
        counter = 1;
    }
    else
        counter += root->left->insert(v); //call NODE::insert()
}


//Remove node with key from the tree
void BST_threaded::remove(string key)
{
   //ADD CODE
   bool isRemoved = false;
   // check if key is in the tree
   if(find(key) == nullptr) // check if the key is in the tree, if not return false
    {
        isRemoved = false;
    }
    else
    {
        // call remove with the first node as 'this', and since it is a left child to root, pass isRight = false
        isRemoved = root->left->remove(key, root, false);
        counter --;
    }
}

//If key matches the key of an element in the container,
//then return a reference to the ELEMENT with the key
//If key does not match the key of any element in the container,
//then an ELEMENT (key,0) is inserted and a reference to it is returned
ELEMENT& BST_threaded::operator[](string key)
{
    if(empty())
        insert(make_pair(key, 0));
    // use method find in node.cpp
    Node* temp = root->left->find(key);
    if(!temp)
    {
        // if found, return the element where key is found
        insert(make_pair(key,0));
        return root->left->find(key)->value;
    }
    else
    {
        // if not found, insert the element and return new element e
        return root->left->find(key)->value;
    }
}


//Find the node in the BST storing key
//Return a BiIterator referring to the node storing the key, if the key is found.
//Otherwise, return this->end().
BiIterator BST_threaded::find(string key) const
{
    // Use find-method in node.cpp
    if(empty())
    {
        return BiIterator(root);
    }
    if(root->left->find(key))
    {
        // if key is found, return the iterator referring to the node of the key
        return BiIterator(root->left->find(key));
    }
    else
    {
        // if not found, return the iterator pointing to the root, end()
        return end();
    }
}


//Return an iterator referring to the first node in the inorder traversal of the BST
BiIterator BST_threaded::begin() const
{
    if(empty())
        return BiIterator(root);

    Node* firstNode = root->left->findMin();
    BiIterator it(firstNode);
    return it;
}


 //Return a BiIterator referring to the past-the-end element in the BST
BiIterator BST_threaded::end() const
{
    BiIterator it(root);

    return it;
}


//Display all keys increasingly
//To be used for debugging -- ONLY
void BST_threaded::display() const
{
    if (!empty())
        root->left->display();
     else
        cout << "The container is empty!!" << endl;

}


#endif /* DOXYGEN_SHOULD_SKIP_THIS */

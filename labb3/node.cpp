/**********************************************
* File: node.cpp                              *
* Author: Aida Nordman                        *
* Course: TND004, Lab 3                       *
* Date: VT2, 2014                             *
* Description: class Node                     *
***********************************************/

#include "node.h"

#ifndef DOXYGEN_SHOULD_SKIP_THIS

using namespace std;

Node::Node(ELEMENT v, Node *l, Node *r)
 : value(v), left(l), right(r)
{
    //l_thread = r_thread = false;
}


//Destructor
//recursively deletes the nodes in the left_subtree and right-subtree
Node::~Node()
{
    //ADD CODE
}


//Insert v in the tree having as root this node
//Return true, if v was inserted
//Otherwise, return false --v already exists in the tree
bool Node::insert(ELEMENT v)
{
    //ADD CODE
    // checks if the already exsists
    if(find(v.first))
        return false;
    
    Node *temp = this;
    
    if(temp->value.first > v.first)
    {
        cout << "EMMMMA JAG FATTTAR INTTTTTEEEEEEE, " << v.first << "< " << temp->value.first << endl;
    }
    
    // check if we have somehow returned to the root, which should never have a
    // right pointer, in that case return nullptr
    while(temp->right != nullptr)
    {
        // if key is smaller, go left
        if(temp->value.first > v.first)
        {
            cout << "vad händer: " << v.first << " " << temp->value.first << endl;
            // check if there is a left child. If not, insert the node there
            if (temp->l_thread)
            {
                temp->left = new Node(v, temp->left, temp);
                temp->left->l_thread = temp->left->r_thread = true;
                temp->l_thread = false;
                
                return true;
            }
            // if it has a child, go there
            else
            {
                temp = temp->left;
            }
        }
        else
        {
            // same as with left above
            if(temp->r_thread)
            {
                temp->right = new Node(v, temp, temp->right);
                temp->right->l_thread = temp->right->r_thread = true;
                temp->r_thread = false;

                return true;
            }
            else
            {
                temp = temp->right;
            }
        }
    }
    return true;
}



//Remove the key from the tree having as root this node
//Return true, if a node storing key was found and deleted
//Otherwise, return false -- there is no node storing key
//isRight==false: this node is left child of parent
//isRight==true: this node is right child of parent
bool Node::remove(string key, Node* parent, bool isRight)
{
    //ADD CODE
    return false;
}



//Remove this node -- this node has at most one child
//isRight==false: this node is left child of parent
//isRight==true: this node is right child of parent
//Remove has 6 cases
//1a: a left child with only a right child
//1b: a left child with only a left child
//1c: a left child with no children
//2a: a right child with only a right child
//2b: a right child with only a left child
//2c: a right child with no children
void Node::removeMe(Node* parent, bool isRight)
{
   //ADD CODE
}



//Return a pointer to the Node storing key
//key is possibly stored in one of the sub-trees of this node
//If there is no node storing key then return nullptr
Node* Node::find(string key)
{
    //ADD CODE
    // save instance of this as temp
    // to be able to traverse without changing the tree
    Node *temp = this;
    
    // check if we have somehow returned to the root, which should never have a
    // right pointer, in that case return nullptr
    while (temp->right != nullptr)
    {
        // if the value is found, return that node
        if (temp->value.first == key)
        {
            return temp;
        }
        // if the key is smaller and the current node has a left child, go to it
        else if(key < temp->value.first && temp->l_thread == false)
        {
            temp = temp->left;
        }
        // same as with smaller key but larger
        else if(key > temp->value.first && temp->r_thread == false)
        {
            temp = temp->right;
        }
        // if node has l_thread and r_thread true it has no children and
        // the key does not exist in the tree
        else
            return nullptr;
    }
    return nullptr;
}


//Return a pointer to the node storing the smalest value
//of the tree whose root is this node
Node* Node::findMin()
{
    //ADD CODE
    return nullptr;
}


//Return a pointer to the node storing the largest value
//of the tree whose root is this node
Node* Node::findMax()
{
    //ADD CODE
    return nullptr;
}



//Display in inorder all keys
//stored in the tree whose root is this node
//recursive function
//Used for debugging -- ONLY
void Node::display() const
{
    if ( !l_thread ) //display left sub-tree
        left->display();

    cout << value.first << " "; //display key stored in the node

    if ( !r_thread ) //display right sub-tree
        right->display();
}


#endif /* DOXYGEN_SHOULD_SKIP_THIS */
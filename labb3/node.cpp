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
    // lite oklart hur vi ska g�ra h�r, t�nker att den kallas rekursivt nu men
    // den tas aldrig bort s�ger testet.
    if(!l_thread)
    {
        delete left;
    }
    if(!r_thread)
    {
        delete right;
    }
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

    // check if we have somehow returned to the root, which should never have a
    // right pointer, in that case return nullptr
    // TODO: might be while(true)
    while(temp->right)
    {
        // if key is smaller, go left
        if(v.first < temp->value.first)
        {
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
    if(key < value.first)
    {
        // the key is in the left subtree
        // boolean isRight is false
        return left->remove(key, this, false);
    }
    else if(key > value.first)
    {
        // the key is in the right subtree
        // boolean isRight is true
        return right->remove(key, this, true);
    }
    else // key == value.first
    {
        // the key is found and should be erased!
        // now check for children
        if(!l_thread && !r_thread)
        {
            // if two children, replace the value with the largest value in the left subtree
            // then recursivly call remove in the left subtree
            // ALTERNATIVE: replace it with the smallest value in the right subtree
   //         cout << "6. node has 2 kids, swap with " << val->value.first << endl;
            value = right->findMin()->value;
            return right->remove(value.first, this, true);
        }
        else // the node has at most one child
        {
            // the node is checked with the 6 cases and removed!
            // boolean isRight will be set before
            removeMe(parent, isRight);
            return true;
        }
    }
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
   // DRAW THE SIX CASES TO GET CLEAR PICTURE!
   // if remove is a left child with only a right child
   if(!isRight && l_thread && !r_thread)
   {
        // peka parent->left till this->right och this->right->left till this->left
        parent->left = right;
  //      right->left = left;
        this->right->findMin()->left = this->left;
        l_thread = r_thread = true;
        delete this;
   }
    // if remove is a left child with only a left child
   else if(!isRight && !l_thread && r_thread)
   {
        // peka parent->left till this->left och this->left->right till this->right
        parent->left = left;
        left->findMax()->right = right;
        l_thread = r_thread = true;
        delete this;
   }
   // if remove is a left child with no children (r_thread = l_thread = true)
    else if(!isRight && l_thread && r_thread)
    {
        // g�r parent->l_thread till true och parent->left = left;
        parent->l_thread = true;
        parent->left = left;
        l_thread = r_thread = true;
        delete this;
    }

   // if remove is a right child with only a right child
   else if(isRight && l_thread && !r_thread)
   {
       // peka parent->right till this->right och this->right->left till this->left
       parent->right = right;
       //right->left = left;
       this->right->findMin()->left = this->left;
       l_thread = r_thread = true;
       delete this;

   }
   // if remove is a right child with only a left child
   else if(isRight && !l_thread && r_thread)
   {
       // peka parent->right till this->left och this->left->right till this->right
       parent->right = left;
     //  left->right = right;
        this->left->findMax()->right = this->right;
       l_thread = r_thread = true;
       delete this;

   }
   // if remove is a right child with no children
   else if(isRight && l_thread && r_thread)
   {
       // g�r parent->r_thread till true och parent->right = right;
       parent->right = right;
       parent->r_thread = true;
       l_thread = r_thread = true;
       delete this;

   }
   else
        cout << "Something went wrong in removeMe!" << endl;

}



//Return a pointer to the Node storing key
//key is possibly stored in one of the sub-trees of this node
//If there is no node storing key then return nullptr
Node* Node::find(string key)
{
    //ADD CODE
    // make copy of this to change the value without editing the tree
        Node* temp(this);
    // If key smaller and elements in left tree exists, go to the left subtree
    if(key < temp->value.first){

        if(l_thread) // if there is no left subtree, key is not in the tree
            return nullptr;

        else
            return temp->left->find(key);

    }
    // If key larger and elements in right tree exists, go to the right subtree
    else if(key > temp->value.first){

        if(r_thread) // if there is no right subtree, key is not in the tree
            return nullptr;

        else
            return temp->right->find(key);

    }

    // Else the elements is the same => FOUND!
    else if(key == temp->value.first)
        return temp;

    // Not found
    return nullptr;
}


//Return a pointer to the node storing the smallest value
//of the tree whose root is this node
Node* Node::findMin()
{
    if(!l_thread)
        return this->left->findMin();

    return this;
}


//Return a pointer to the node storing the largest value
//of the tree whose root is this node
Node* Node::findMax()
{
    //ADD CODE
    if(!r_thread)
        return right->findMax();

    return this;
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

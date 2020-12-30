#include "BSTree.h"

#include <iostream>

using namespace std;

///////////////////////////////////
// Already Implemented Functions //
///////////////////////////////////

// These functions are already implemented for you. Scroll below to
// see the functions that you have to implement 


// constructors
BSTree::BSTree() : size(0), root(nullptr) {}

// input / output operators
ostream& operator<<(ostream& out, BSTree& tree)
{
    tree.print_level_by_level(out);
    return out;
}

ostream& operator<<(ostream& out, Node& node)
{
    return out << node.value << "[" << node.search_time << "]";
}

istream& operator>>(istream& in, BSTree& tree)
{
    /*
      take input from the in stream, and build your tree
      input will look like
      4 
      2 
      6 
      1 
      3 
      5 
      7
    */
    int next;
    while(in >> next) {
        tree.insert(next);
    }
    return in;
}

// Example recursive function
void BSTree::copy_helper(Node*& newNode, const Node* sourceNode) {
    //Don't copy if the node is nullptr
    if(sourceNode == nullptr)
        return;

    //Change the new node to a copy of sourceNode
    newNode = new Node(sourceNode->value);
    //Copy over the search cost
    newNode->search_time = sourceNode->search_time;

    //Copy left subtree
    if (sourceNode->left != nullptr)
        copy_helper(newNode->left, sourceNode->left);
    //Copy right subtree
    if(sourceNode->right != nullptr)
        copy_helper(newNode->right, sourceNode->right);
}

// recursive function
int BSTree::get_total_search_time(Node* node)
{
  if (node != nullptr) {
    return node->search_time + get_total_search_time(node->left) + get_total_search_time(node->right);
  }
  return 0;
}

// implemented
float BSTree::get_average_search_time()
{
  int total_search_time = get_total_search_time(root);
  if(total_search_time == 0)
    return -1;
	
  return ((float)total_search_time)/size;
}


///////////////////////////////////
//     Functions to Implement    //
///////////////////////////////////

// These are the functions you should implement
// Feel free to call the functions above or create new helper functions

// void BSTree::copy_helper(const Node* otherptr, Node * ptr){
//   cout << endl;
// }

void BSTree::erase(Node *ptr){

  if (ptr == nullptr)
    return;

  erase(ptr->left);
  erase(ptr->right);
  delete ptr; 
}

// copy constructor
BSTree::BSTree(const BSTree& other)
{

  copy_helper(root, other.root);
  size = other.size;

}

// move constructor
BSTree::BSTree(BSTree&& other)
{
  root = other.root;
  size = other.size;
  other.root = nullptr;
  other.size = 0;
}

//copy assignment
BSTree& BSTree::operator=(const BSTree& other)
{
  if (this != &other){
    if (root != nullptr){
      erase(root);
      root = nullptr;
    }
    copy_helper(root, other.root);
    size = other.size;
    return *this;
  }
  return *this;
}

// move assignment
BSTree& BSTree::operator=(BSTree&& other)
{
    if (this != &other){
    if (root != nullptr){
      erase(root);
      root = nullptr;
    }
    // root = other.root;
    // other.root = nullptr;
    root = other.root;
    size = other.size;
    other.root = nullptr;
    other.size = 0;
    return *this;
  }
  return *this;

}

// destructor
BSTree::~BSTree()
{
    // Make sure to call delete on every node of the tree
    // You can use a recursive helper function to do this
  erase(root);
}

Node* BSTree::insert(int obj)
{
    /* insert a node into the tree
    first find where the node should go
    then modify pointers to connect your new node */

    size++;

    if (root == nullptr){
      root = new Node(obj);
      root->search_time = 1;
      return root;
    }
    else {

      Node* currptr = root;
      Node* prevptr = currptr;

      while (currptr != nullptr){
        prevptr = currptr;
        if (currptr->value > obj)
          currptr = currptr->left;
        else
          currptr = currptr->right;
      }

      if (prevptr->value > obj){
        prevptr->left = new Node(obj);
        prevptr->left->search_time = prevptr->search_time + 1;
        return prevptr->left;
      }
      else {
        prevptr->right = new Node(obj);
        prevptr->right->search_time = prevptr->search_time + 1;
        prevptr->right;
      }

      //delete currptr;
      //delete prevptr;

    }


}


Node* BSTree::search(int obj)
{
    /* recursively search down the tree to find the node that contains obj
    if you don't find anything return nullptr */

  Node* currptr = root;
  while (currptr != nullptr){
    if (currptr->value == obj)
      return currptr;
    else if (currptr-> value > obj)
      currptr = currptr->left;
    else 
      currptr = currptr->right;
  }

  return nullptr;
}

void BSTree::update_search_time_helper(Node* ptr, int val){

  if (ptr == nullptr)
    return;

  ptr->search_time = val;

  update_search_time_helper(ptr->left, ptr->search_time + 1);
  update_search_time_helper(ptr->right, ptr->search_time + 1);

}

void BSTree::update_search_times()
{
    /* do a BFS or DFS of your tree and update the search times of all nodes at once
      The root has a search time of 1, and each child is 1 more than its parent */

    update_search_time_helper(root, 1);
}

void BSTree::inorder_helper(ostream& out, Node* ptr){

  if (ptr == nullptr)
    return;

  inorder_helper(out, ptr->left);
  out << ptr->value << "[" << ptr->search_time << "] ";
  inorder_helper(out, ptr->right);

}

void BSTree::inorder(ostream& out)
{
    /* print your nodes in infix order
    If our tree looks like this:

       4
     2   6
    1 3 5 7

    It should output:
    1[3] 2[2] 3[3] 4[1] 5[3] 6[2] 7[3]
    You can use the << operator to print the nodes in the format shown */

  inorder_helper(out, root);
  out << endl;
}

void BSTree::print_lbl_helper(std::ostream& out, std::vector<Node*> v){

  std::vector<Node*> v1;

  bool nullCheck = false;
  for (Node* temp : v){
    if (temp != nullptr)
      nullCheck = true;
  }
  if (nullCheck == false)
    return; 


  for (Node* temp : v){
    if (temp != nullptr)
      out << temp->value << "[" << temp->search_time << "] ";
    else
      out << "X ";

    if (temp != nullptr){
      v1.push_back(temp->left);
      v1.push_back(temp->right);
    }
    else {
      v1.push_back(nullptr);
      v1.push_back(nullptr);
    }

  }

  out << endl;

  print_lbl_helper(out, v1);

}



void BSTree::print_level_by_level(ostream& out)
{
    /* Print the tree using a BFS so that each level contains the values for a level of the tree.
    Use X to mark empty positions. 
    
      if our tree looks like this:

       4
     2   6
    1   5 7
           9

    it should output:

    4[1]
    2[2] 6[2]
    1[3] X 5[3] 7[3]
    X X X X X X X 9[4]

    it might be helpful to do this part with the std::queue data structure.
    Hint: the Nth level contains 2^(N-1) nodes (with a value or with an X). Watch out
    for nodes like the left child of 6 above, and print the descendents of an empty
    node as also empty
    You can use the << operator to print nodes in the format shown */

    //cout << "A Call here" << endl;

    std::vector<Node*> v;
    v.push_back(root);
    print_lbl_helper(out, v);
}

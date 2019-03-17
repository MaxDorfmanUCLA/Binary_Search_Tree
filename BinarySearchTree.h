//
//  Header.h
//  HW710B
//
//  Created by Max Dorfman on 3/7/17.
//  Copyright © 2017 Max Dorfman. All rights reserved.
// I Max Dorfman affirm that this code is my own and was not copied. I collaborated with Malaya Du

#ifndef Header_h
#define Header_h

#include <iostream>

namespace bst {
    // NEED: copy/move assignment operator
    class node;
    class iterator;
    class Tree {
        friend iterator; // iterators need access to private data
        private:
            node *root; // the root of the tree
            void deleteTree(node*); // to recursively delete the tree
            void traverseInsert(const node* n); //
            int sz;

        public:
            Tree(); // default constructor for empty tree
            ~Tree(); // destructor
            Tree(const Tree&); // copy constructor
            Tree(Tree&&); // move constructor
            Tree& operator=(const Tree&); // copy assignment
            Tree& operator=(Tree &&); // move assignment
            void insert(const double&); // to add a value to the tree
            void erase(iterator); // to erase a value from the tree
            int& size();
            iterator begin() const; // iterator to begin position
            iterator end() const; // iterator to past-the-end position
            iterator find(const double&) const; // check if contains a double
        
    };

    class node {
        friend Tree; // tree member functions may search through nodes
        friend iterator; //to be able to advance by checking node values
        private:
            node(const double&); // constructor
            node *left, *right; // children
            node *parent;
            double val; // data value stored
            void insertNode(node*); // member function for inserting node
    };

    class iterator {
        friend Tree; // to allow iterator modifications by Tree operations
        private:
            iterator(node*, const Tree*); // constructor
            node *curr;// current position
            const Tree *container; // holding container
        public:
            iterator &operator++(); // prefix ++
            iterator operator++(int); // postfix ++
            const double& operator*() const; // dereference operator
            const double* operator->() const; // arrow operator
            bool operator==(const iterator&) const; // comparison
            
    };
            bool operator!=(const iterator&, const iterator&); // opposite of ==

   

//Tree Tree Tree Tree Tree

/* default constructor
 
 root and size set to 0 initially
 */
Tree::Tree(): root(nullptr), sz(0){}

/* destructor
     
tree deleted by deleting root
*/
Tree::~Tree(){
    deleteTree(root);
}

/* tree copy constructor
    
@param rhs tree to copy. root and size assigned
*/
Tree::Tree(const Tree& rhs): root(nullptr), sz(rhs.sz){
    traverseInsert(rhs.root);
}

/* move constructor
     
@param t tree to take address of
*/
Tree::Tree(Tree&& t){
    root=t.root;
    sz = t.sz;
    t.root=nullptr;
}

/* implementation of tree begin
*/
iterator Tree::begin() const {
    if (root == nullptr) { // if root is null then tree empty
        return iterator(nullptr, this); // return iterator that is null
    }
    node *n = root;
    while (n->left != nullptr) { // while we can still go left (to lower value)
        n = n->left; // go left
    }
    return iterator(n, this); // return iterator for node of smallest value
}

/* implementation of tree end
*/
iterator Tree::end() const{
    return iterator(nullptr, this);
}

/* tree copy assignment operator
     
@param rhs tree to copy. root and size assigned
*/
Tree& Tree::operator=(const Tree& rhs){
    Tree copy(rhs);
    std::swap(root, copy.root);
    std::swap(sz, copy.sz);
    return *this;
}

/* tree move assignment operator
     
@param rhs tree to take address of. root and size assigned
*/
Tree& Tree::operator=(Tree&& rhs){
    std::swap(root, rhs.root);
    std::swap(sz, rhs.sz);
    return *this;
}

/* find function to find value in tree
     
@param val value to find
*/
iterator Tree::find(const double& val) const{
    for(auto it = begin(); it != end(); ++it){
        if(it.curr->val == val)
            return it;
    }
    return end();
}

/* tree erase function
     
@param itr to move through the tree and erase
*/
void Tree::erase(iterator itr) {
    node* n = itr.curr;
    std::swap(n,(++itr).curr);
    if (n==root && n->right==nullptr){
        n->left = root;
        n = nullptr;
        delete n;
        
    }
    if (n==root && n->right==nullptr && n->left==nullptr){
        n = nullptr;
        delete n;
    }
    if (n==root && n->left==nullptr){
        n->right = root;
        n = nullptr;
        delete n;
    }
    else{
        root = n->right;
        ++itr;
        n->left->parent=(++itr.curr);
        n = nullptr;
        delete n;
    }
  
    if(n==nullptr){
        delete n;
    }
    if(n->right && n->left==nullptr) {
        n->right->parent=(++itr).curr;
        n->parent->left=n->right;
        
    }
    else if (n->right==nullptr && n->left == nullptr) {
        if (n->parent->right == n) {
            n->parent->right = nullptr;
            n = nullptr;
            delete n;
        }
        else{
            n->parent->left = nullptr;
            n = nullptr;
            delete n;
        }
    }
    
    --sz;
}

/* tree insert function
     
@param val value to insert
*/
void Tree::insert(const double& val){
    if(!root)
        root= new node(val);
    else {
        node*n = new node(val);
        root->insertNode(n);
    }
    ++sz;
}

/* function returns size
 
*/
int& Tree::size(){
    return sz;
}

/* fills tree and calls insert function
     
@param n node to insert recursively
*/
void Tree::traverseInsert(const node* n) {
    insert(n->val);
    if(n->left)
        traverseInsert(n->left);
    if(n->right)
        traverseInsert(n->right);
}
void Tree::deleteTree(node* n){
    if(n){
        if(n->left)
            deleteTree(n->left);
        if(n->right)
            deleteTree(n->right);
        delete n;
    }
}


//node node node node node node
    
/* node constructor
     
@param val value to make node
*/
node::node(const double& val) : val(val), parent(nullptr), left(nullptr), right(nullptr) {}

/* node insert function
     
@param n node to insert
*/
void node::insertNode(node* n){
    // if this value is less than new node value, new node should go right
    if (val < n->val) {
        if (right) // if this node has a right child
            right->insertNode(n); // recurse on the right child
        else{ // if the right child is null
            n->parent=this;
            this->right=n;
        }
    }
    // if this value is larger than new node value, new node should go left
    else if (val > n->val) {
        if (left) // if this node has a left child
            left->insertNode(n); // recurse on the left child
        else{
            n->parent=this;
            this->left=n;
        }
    }
}// nothing to add if new node value neither < nor > than current value

//iterator iterator iterator iterator

/* iterator constructor
     
@param n node to start at
@param T tree to iterate through
*/
iterator::iterator(node* n, const Tree* T) : curr(n), container(T) {}

/* iterator ++ prefix operator
*/
iterator &iterator::operator++() {
    if (!curr->parent && !curr->right){
        curr = nullptr;
    }
    
    else if(curr-> right) { //if has right child
        node* p = curr-> right;
        while(p -> left) {
            p = p->left;
        }
        curr  = p;
    }
    else { // is a left child
        if(curr-> parent && curr -> parent -> left == curr) {
            curr = curr -> parent;
        }
        else { // does not have right child and is right child
            if(curr ->parent-> right == curr) {
                node*p = curr -> parent;
                while(p-> parent && p -> parent -> right == p) {
                    p = p-> parent;
                }
                curr = p-> parent;
            }
        }
    }
    return *this;
    
}

/* iterator ++ postfix operator

@param int unused
*/
iterator iterator::operator++(int){
    iterator *itr;
    itr->curr=curr;
    ++curr;
    return *itr;
    }

/* iterator dereference operator
*/
const double& iterator::operator*() const{
    return curr->val;
}

/* iterator arrow operator
*/
const double* iterator::operator->() const {
    return & (curr->val);
}

/* iterator equals operator
*/
bool iterator::operator==(const iterator& rhs) const{
    return ((curr==rhs.curr) && (container == rhs.container));
}

/* iterator not equal operator
*/
bool operator!=(const iterator& lhs, const iterator& rhs){
    return !(lhs==rhs);
}
}

//end of namespace
//end of namespace



#endif /* Header_h */

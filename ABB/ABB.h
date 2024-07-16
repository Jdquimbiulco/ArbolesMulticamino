#include <iostream>

struct node {
    int key;
    struct node *left, *right;
};
 
 


 struct node* newNode(int item)
 {
     struct node* temp
         = new struct node;
     temp->key = item;
     temp->left = temp->right = nullptr;
     return temp;
 }
  
 
 struct node* insert(struct node* node, int key)
 {
     // If the tree is empty, return a new node
     if (node == nullptr)
         return newNode(key);
  
     // Otherwise, recur down the tree
     if (key < node->key)
         node->left = insert(node->left, key);
     else if (key > node->key)
         node->right = insert(node->right, key);
  
     // Return the (unchanged) node pointer
     return node;
 }
  

 struct node* search(struct node* root, int key)
 {
     // Base Cases: root is null or key is present at root
     if (root == nullptr || root->key == key)
         return root;
  
     // Key is greater than root's key
     if (root->key < key)
         return search(root->right, key);
  
     // Key is smaller than root's key
     return search(root->left, key);
 }

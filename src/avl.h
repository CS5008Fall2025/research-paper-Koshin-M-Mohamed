#ifndef AVL_H
#define AVL_H

// Node for an AVL tree. Stores key, height, and child.
// Height is stored to keep insert balanced without recalculating the whole subtree.
typedef struct AvlNode {
    int key;
    int height;
    struct AvlNode* left;
    struct AvlNode* right;
} AvlNode;

// Tracks how many rotations happen during inserts.
extern int avl_rotation_count;

// Insert a key and return the new root (in case rotation changes the root).
AvlNode* avl_insert(AvlNode* root, int key);

// Search for a key.
AvlNode* avl_search(AvlNode* root, int key);

// Print sorted order (in-order traversal).
void avl_inorder_print(AvlNode* root);

// Get height of the tree.
int avl_tree_height(AvlNode* root);

// Release memory used by the tree.
void avl_free(AvlNode* root);

#endif

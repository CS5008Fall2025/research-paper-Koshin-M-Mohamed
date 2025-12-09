#ifndef BST_H
#define BST_H

// Basic BST node. Key only for comparing, child point to left right.
typedef struct BSTNode {
    int key;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

// Standard BST insert.
BSTNode* bst_insert(BSTNode* root, int key);

// Find a key starting from this root.
BSTNode* bst_search(BSTNode* root, int key);

// Height calculation (how deep the tree gets).
int bst_tree_height(BSTNode* root);

void bst_free(BSTNode* root);

#endif

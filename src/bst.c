#include <stdlib.h>
#include "bst.h"

// Insert into a normal BST with no balancing.
// Sorted input will force everything to the right branch.
BSTNode* bst_insert(BSTNode* root, int key) {
    if (root == NULL) {
        BSTNode* node = malloc(sizeof(BSTNode));
        node->key = key;
        node->left = NULL;
        node->right = NULL;
        return node;
    }

    if (key < root->key)
        root->left = bst_insert(root->left, key);
    else
        root->right = bst_insert(root->right, key);

    return root;
}

// Basic recursive search.
// Just follow the BST rule until we either find the key or hit null.
// Worst case this goes all the way down for sorted trees.
BSTNode* bst_search(BSTNode* root, int key) {
    if (root == NULL || root->key == key)
        return root;

    if (key < root->key)
        return bst_search(root->left, key);

    return bst_search(root->right, key);
}

// Height of the tree from this root.
// I use this to show how unbalanced it gets compared to AVL.
int bst_tree_height(BSTNode* root) {
    if (root == NULL)
        return 0;

    int left_height = bst_tree_height(root->left);
    int right_height = bst_tree_height(root->right);

    return 1 + (left_height > right_height ? left_height : right_height);
}
// Free
void bst_free(BSTNode* root) {
    if (root == NULL)
        return;

    bst_free(root->left);
    bst_free(root->right);
    free(root);
}

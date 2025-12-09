#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

int avl_rotation_count = 0;

// Basic max helper.
static int max(int a, int b) {
    return (a > b) ? a : b;
}

// Read height from node safely.
static int node_height(AvlNode* node) {
    return node ? node->height : 0;
}

// Update the height of a node based on its children.
static void update_height(AvlNode* node) {
    node->height = 1 + max(node_height(node->left), node_height(node->right));
}

// Balance factor: positive means left-heavy, negative means right-heavy.
static int get_balance(AvlNode* node) {
    return node ? (node_height(node->left) - node_height(node->right)) : 0;
}

// Allocate a new node.
static AvlNode* avl_create_node(int key) {
    AvlNode* node = malloc(sizeof(AvlNode));
    node->key = key;
    node->height = 1; // new leaf
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Single right rotation.
static AvlNode* right_rotate(AvlNode* y) {
    avl_rotation_count++;

    AvlNode* x = y->left;
    AvlNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    update_height(y);
    update_height(x);

    return x;
}

// Single left rotation.
static AvlNode* left_rotate(AvlNode* x) {
    avl_rotation_count++;

    AvlNode* y = x->right;
    AvlNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    update_height(x);
    update_height(y);

    return y;
}

// Insert into AVL. Insert like BST and then rebalance if needed.
AvlNode* avl_insert(AvlNode* root, int key) {
    if (root == NULL)
        return avl_create_node(key);

    if (key < root->key)
        root->left = avl_insert(root->left, key);
    else if (key > root->key)
        root->right = avl_insert(root->right, key);
    else
        return root; // ignore duplicate

    // Update height after inserting into a subtree.
    update_height(root);

    // Check if this node became unbalanced.
    int balance = get_balance(root);

    // Four rebalance cases:
    if (balance > 1 && key < root->left->key)
        return right_rotate(root);

    if (balance < -1 && key > root->right->key)
        return left_rotate(root);

    if (balance > 1 && key > root->left->key) {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }

    if (balance < -1 && key < root->right->key) {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }

    return root;
}

// Search normally.
AvlNode* avl_search(AvlNode* root, int key) {
    if (root == NULL || key == root->key)
        return root;
    if (key < root->key)
        return avl_search(root->left, key);
    return avl_search(root->right, key);
}

// Print in sorted order.
void avl_inorder_print(AvlNode* root) {
    if (!root) return;
    avl_inorder_print(root->left);
    printf("%d ", root->key);
    avl_inorder_print(root->right);
}

// Just return the height stored at the root.
int avl_tree_height(AvlNode* root) {
    return node_height(root);
}

// Cleanup tree memory.
void avl_free(AvlNode* root) {
    if (!root) return;
    avl_free(root->left);
    avl_free(root->right);
    free(root);
}

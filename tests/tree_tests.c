#include <assert.h>
#include <stdio.h>
#include "../src/bst.h"
#include "../src/avl.h"

// Simple test to confirm BST insert and search work how I expect it to.
static void test_bst_insert_search() {
    BSTNode* r = NULL;

    r = bst_insert(r, 5);
    r = bst_insert(r, 2);
    r = bst_insert(r, 7);

    // search hits
    assert(bst_search(r, 5) != NULL);
    assert(bst_search(r, 2) != NULL);
    assert(bst_search(r, 7) != NULL);

    // search miss
    assert(bst_search(r, 10) == NULL);

    bst_free(r);
}

// Here I want to show how BST behaves with sorted inserts.
// This should make the height equal to the number of inserts.
static void test_bst_height_sorted() {
    BSTNode* r = NULL;
    for (int i = 1; i <= 10; i++) {
        r = bst_insert(r, i);
    }

    int h = bst_tree_height(r);
    // worst case shape
    assert(h == 10); 

    bst_free(r);
}

// AVL should stay balanced even if I do sorted inserts.
// Height should be small, logarithmic.
static void test_avl_height_sorted() {
    AvlNode* r = NULL;
    avl_rotation_count = 0; // clean slate

    for (int i = 1; i <= 10; i++) {
        r = avl_insert(r, i);
    }

    int h = avl_tree_height(r);
    // with 10 nodes, height should definitely be greater than or equal 5
    assert(h <= 5);

    // also check that rotations actually happened
    assert(avl_rotation_count > 0);

    avl_free(r);
}

// Quick check that AVL search matches BST behavior for hits/misses.
static void test_avl_search() {
    AvlNode* r = NULL;

    r = avl_insert(r, 8);
    r = avl_insert(r, 4);
    r = avl_insert(r, 12);

    assert(avl_search(r, 8) != NULL);
    assert(avl_search(r, 4) != NULL);
    assert(avl_search(r, 12) != NULL);
    assert(avl_search(r, 100) == NULL);

    avl_free(r);
}

int main() {
    test_bst_insert_search();
    test_bst_height_sorted();
    test_avl_height_sorted();
    test_avl_search();

    // If it reaches here, all tests passed.
    printf("Tree tests passed.\n");
    return 0;
}

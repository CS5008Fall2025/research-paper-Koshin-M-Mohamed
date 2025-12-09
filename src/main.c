#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "bst.h"
#include "avl.h"

// I use this to measure how long inserts and searches take.
// I convert time to milliseconds to make the output easier to read.
static double get_time_ms() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000.0) + (tv.tv_usec / 1000.0);
}

int main(int argc, char** argv) {
    // I want the user to pick the input size 
    if (argc < 2) {
        printf("usage: ./run <N>\n");
        return 1;
    }

    int N = atoi(argv[1]);

    // both trees start empty
    BSTNode* bst_root = NULL;
    AvlNode* avl_root = NULL;

    double start, end;
    double bst_insert_time, avl_insert_time;
    double bst_search_time, avl_search_time;

    // insert N items (sorted order)
    // sorted input makes BST form a tall chain,
    // and shows AVL rotations keeping it balanced.
    start = get_time_ms();
    for (int i = 0; i < N; i++) {
        bst_root = bst_insert(bst_root, i);
    }
    end = get_time_ms();
    bst_insert_time = end - start;

    // same insert test for AVL tree
    // AVL should stay close to log(n) height
    start = get_time_ms();
    for (int i = 0; i < N; i++) {
        avl_root = avl_insert(avl_root, i);
    }
    end = get_time_ms();
    avl_insert_time = end - start;

    // search test on BST
    // Look up random keys to see average behavior
    start = get_time_ms();
    for (int i = 0; i < N; i++) {
        int key = rand() % N;
        bst_search(bst_root, key);
    }
    end = get_time_ms();
    bst_search_time = end - start;

    // same search test on AVL
    start = get_time_ms();
    for (int i = 0; i < N; i++) {
        int key = rand() % N;
        avl_search(avl_root, key);
    }
    end = get_time_ms();
    avl_search_time = end - start;

// Print
printf("n = %d\n", N);
printf("bst height = %d\n", bst_tree_height(bst_root));
printf("avl height = %d\n", avl_tree_height(avl_root));
printf("bst insert time = %.2f ms\n", bst_insert_time);
printf("avl insert time = %.2f ms\n", avl_insert_time);
printf("bst search time = %.2f ms\n", bst_search_time);
printf("avl search time = %.2f ms\n", avl_search_time);
printf("avl rotations = %d\n", avl_rotation_count);


    bst_free(bst_root);
    avl_free(avl_root);

    return 0;
}

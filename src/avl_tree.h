#ifndef __AVL_TREE__
#define __AVL_TREE__

#include <stdlib.h>

typedef struct node {
    void        *data;
    struct node *left;
    struct node *right;
} node_t;

typedef struct {
    node_t *root;
    size_t  length;
    size_t  element_size;
} avl_tree_t;

void avl_init(avl_tree_t *tree, size_t element_size);
void avl_destroy(avl_tree_t *tree);
void avl_destroy_traversal(node_t *node);

#endif // __AVL_TREE__

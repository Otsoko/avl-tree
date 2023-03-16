#ifndef __AVL_TREE__
#define __AVL_TREE__

#include <stdlib.h>

typedef struct node {
    void        *data;
    struct node *left;
    struct node *right;
    int          height;
} node_t;

typedef struct {
    node_t *root;
    size_t  length;
    size_t  element_size;
} avl_tree_t;

void    avl_init(avl_tree_t *tree, size_t element_size);
void    avl_destroy(avl_tree_t *tree);
void    avl_destroy_traversal(node_t *node);
node_t *avl_create_node(avl_tree_t *tree, void *data);
int     avl_height(node_t *node);
node_t *avl_inorder_successor(node_t *node);
int     avl_get_balance_factor(node_t *node);
node_t *avl_rotate_right(node_t *y);
node_t *avl_rotate_left(node_t *x);
node_t *avl_insert(avl_tree_t *tree, void *data, int (*avl_cmp_fptr)(const void *a, const void *b));
node_t *avl_insert_traversal(avl_tree_t *tree, node_t *node, void *data, int (*avl_cmp_fptr)(const void *a, const void *b));
node_t *avl_delete(avl_tree_t *tree, void *data, int (*avl_cmp_fptr)(const void *a, const void *b));
node_t *avl_delete_traversal(avl_tree_t *tree, node_t *node, void *data, int (*avl_cmp_fptr)(const void *a, const void *b));

#endif // __AVL_TREE__

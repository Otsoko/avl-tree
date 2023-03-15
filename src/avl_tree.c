#include "avl_tree.h"
#include <string.h>

void avl_init(avl_tree_t *tree, size_t element_size) {
    tree->root         = NULL;
    tree->length       = 0;
    tree->element_size = 0;
}

void avl_destroy(avl_tree_t *tree) {
    avl_destroy_traversal(tree->root);
    tree->root         = NULL;
    tree->length       = 0;
    tree->element_size = 0;
}

void avl_destroy_traversal(node_t *node) {
    if (node == NULL) {
        return;
    }

    avl_destroy_traversal(node->left);
    avl_destroy_traversal(node->right);
    free(node->data);
    free(node);
}

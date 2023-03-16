#include "avl_tree.h"
#include <string.h>

void avl_init(avl_tree_t *tree, size_t element_size) {
    tree->root         = NULL;
    tree->length       = 0;
    tree->element_size = element_size;
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

node_t *avl_create_node(avl_tree_t *tree, void *data) {
    node_t *new = malloc(sizeof(node_t));

    if (!new) {
        return NULL;
    }

    new->data = malloc(tree->element_size);

    if (!new->data) {
        free(new);
        return NULL;
    }

    memcpy(new->data, data, tree->element_size);
    new->left   = NULL;
    new->right  = NULL;
    new->height = 1;

    return new;
}

int avl_height(node_t *node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

node_t *avl_inorder_successor(node_t *node) {
    node_t *current = node;

    while (current && current->left != NULL) {
        current = current->left;
    }

    return current;
}

int avl_get_balance_factor(node_t *node) {
    if (node == NULL) {
        return 0;
    }

    return avl_height(node->left) - avl_height(node->right);
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

node_t *avl_rotate_right(node_t *y) {
    node_t *x  = y->left;
    node_t *t2 = x->right;

    x->right = y;
    y->left  = t2;

    y->height = max(avl_height(y->left), avl_height(y->right)) + 1;
    x->height = max(avl_height(x->left), avl_height(x->right)) + 1;

    return x;
}

node_t *avl_rotate_left(node_t *x) {
    node_t *y  = x->right;
    node_t *t2 = y->left;

    y->left  = x;
    x->right = t2;

    x->height = max(avl_height(x->left), avl_height(x->right)) + 1;
    y->height = max(avl_height(y->left), avl_height(y->right)) + 1;

    return y;
}

node_t *avl_insert(avl_tree_t *tree, void *data, int (*avl_cmp_fptr)(const void *a, const void *b)) {
    tree->root = avl_insert_traversal(tree, (tree->root), data, avl_cmp_fptr);
    return tree->root;
}
node_t *avl_insert_traversal(avl_tree_t *tree, node_t *node, void *data, int (*avl_cmp_fptr)(const void *a, const void *b)) {
    if (node == NULL) {
        node = avl_create_node(tree, data);
        tree->length++;
        return node;
    }

    if (avl_cmp_fptr(data, (node)->data) < 0) {
        (node)->left = avl_insert_traversal(tree, (node)->left, data, avl_cmp_fptr);
    } else if (avl_cmp_fptr(data, (node)->data) > 0) {
        (node)->right = avl_insert_traversal(tree, (node)->right, data, avl_cmp_fptr);
    } else {
        // Element already exists
        return node;
    }

    (node)->height = 1 + max(avl_height((node)->left), avl_height((node)->right));
    int balance    = avl_get_balance_factor(node);

    if (balance > 1 && avl_cmp_fptr(data, (node)->left->data) < 0) {
        return avl_rotate_right(node);
    }

    if (balance < -1 && avl_cmp_fptr(data, (node)->right->data) > 0) {
        return avl_rotate_left(node);
    }

    if (balance > 1 && avl_cmp_fptr(data, (node)->left->data) > 0) {
        (node)->left = avl_rotate_left((node)->left);
        return avl_rotate_right(node);
    }

    if (balance < -1 && avl_cmp_fptr(data, (node)->right->data) < 0) {
        (node)->right = avl_rotate_right((node)->right);
        return avl_rotate_left(node);
    }

    return node;
}
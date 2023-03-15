#include "avl_tree.h"
#include <stdio.h>
#include <time.h>

#define DISTANCE 8
#define MIN_RAND 0
#define MAX_RAND 100
#define MIN_ASCII 65
#define MAX_ASCII 123

typedef struct data {
    int  number;
    char character;
} data_t;

void inorderTraversal(node_t *node);
void preorderTraversal(node_t *node);
void postorderTraversal(node_t *node);

void avlPrintTraversal(node_t *node, int space);
void avlPrint(node_t *root);

int comparator(const void *a, const void *b);

int main(int argc, char const *argv[]) {
    return 0;
}

void inorderTraversal(node_t *node) {
    if (node == NULL) {
        return;
    }
    inorderTraversal(node->left);
    data_t *data = node->data;
    printf("[%d, %c] ", data->number, data->character);
    inorderTraversal(node->right);
}

void preorderTraversal(node_t *node) {
    if (node == NULL) {
        return;
    }
    data_t *data = node->data;
    printf("[%d, %c] ", data->number, data->character);
    preorderTraversal(node->left);
    preorderTraversal(node->right);
}

void postorderTraversal(node_t *node) {
    if (node == NULL) {
        return;
    }
    postorderTraversal(node->left);
    postorderTraversal(node->right);
    data_t *data = node->data;
    printf("[%d, %c] ", data->number, data->character);
}

void avlPrintTraversal(node_t *node, int space) {
    data_t *data = NULL;

    if (node == NULL)
        return;

    space += DISTANCE;

    avlPrintTraversal(node->right, space);

    printf("\n");
    for (int i = DISTANCE; i < space; i++) {
        printf(" ");
    }
    data = node->data;
    printf("[%d, %c] ", data->number, data->character);

    avlPrintTraversal(node->left, space);
}

void avlPrint(node_t *root) {
    avlPrintTraversal(root, 0);
}

int comparator(const void *a, const void *b) {
    const data_t *da = a;
    const data_t *db = b;
    return da->number - db->number;
}

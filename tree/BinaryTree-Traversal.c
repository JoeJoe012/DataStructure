#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef char E;
/*二叉树(Binary Tree)*/
typedef struct TreeNode * Node;
struct TreeNode {
    E element;
    struct TreeNode * left;
    struct TreeNode * right;
};
void preOrder(Node root) {
    if (root == NULL) return;
    printf("%c ", root->element);
    preOrder(root->left);
    preOrder(root->right);
}
void inOrder(Node root) {
    if (root == NULL) return;
    inOrder(root->left);
    printf("%c ", root->element);
    inOrder(root->right);
}
void postOrder(Node root) {
    if (root == NULL) return;
    postOrder(root->left);
    postOrder(root->right);
    printf("%c ", root->element);
}
int main() {
    Node a = malloc(sizeof(struct TreeNode));
    Node b = malloc(sizeof(struct TreeNode));
    Node c = malloc(sizeof(struct TreeNode));
    Node d = malloc(sizeof(struct TreeNode));
    Node e = malloc(sizeof(struct TreeNode));
    Node f = malloc(sizeof(struct TreeNode));
    a->element = 'A';
    b->element = 'B';
    c->element = 'C';
    d->element = 'D';
    e->element = 'E';
    f->element = 'F';
    a->left = b;
    a->right = c;
    b->left = d;
    b->right = e;
    c->right = f;
    c->left = NULL;
    d->left = d->right = NULL;
    e->left = e->right = NULL;
    f->left = f->right = NULL;
    /*
            A
          B   C
         D E   F
    */
    printf("Preorder Traversal: \n");
    preOrder(a);
    printf("\n\n");
    printf("Inorder Traversal: \n");
    inOrder(a);
    printf("\n\n");
    printf("Postorder Traversal: \n");
    postOrder(a);
    printf("\n\n");
}
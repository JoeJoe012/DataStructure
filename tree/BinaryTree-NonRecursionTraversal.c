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
    int flag;  //后序遍历: 当前节点需要经历左右子树都被遍历才行; 这里用flag存一下状态，0表示左子树遍历完成，1表示右子树遍历完成
};
//------------- 栈 ---------------
typedef Node T;
typedef struct ListNode * SNode;
struct ListNode {
    T element;
    struct ListNode * next;
};
void initStack(SNode head) {head->next = NULL;}
bool pushStack(SNode head, T element) {
    SNode newNode = malloc(sizeof(struct ListNode));
    if (newNode == NULL) return false;
    newNode->element = element;
    newNode->next = head->next;
    head->next = newNode;
    return true;
}
bool isEmpty(SNode head) {return head->next == NULL;}
T popStack(SNode head) {
    SNode top = head->next;
    T e = top->element;
    head->next = head->next->next;
    free(top);
    return e;
}
T peekStack(SNode head) {
    return head->next->element;
}
//--------------------------------
void preOrder(Node root) {
    struct ListNode stack;
    initStack(&stack);
    while (root != NULL || !isEmpty(&stack)) {  //两个条件, 只有当栈空并且节点为NULL时才终止循环
        while (root != NULL) {    //先不断遍历左子树，直到没有为止
            pushStack(&stack, root);  //途中每经过一个结点，就将结点丢进栈中
            printf("%c ", root->element);
            root = root->left;
        }
        root = popStack(&stack);  //经过前面的循环，明确左子树全部走完了，接着就是右子树了
        root = root->right;
        //得到右孩子，如果有右孩子，下一轮会重复上面的步骤；
        //如果没有右孩子那么这里的root就被赋值为NULL了，
        //下一轮开始会直接跳过上面的while，继续出栈下一个结点再找右子树
    }
}
void inOrder(Node root) {
    struct ListNode stack;
    initStack(&stack);
    while (root != NULL || !isEmpty(&stack)) {
        while (root != NULL) {
            pushStack(&stack, root);
            root = root->left;
        }
        root = popStack(&stack);
        printf("%c ", root->element);  //只需要将打印时机延后到左子树遍历完成
        root = root->right;
    }
}
//后序遍历的非递归写法的最大区别是将结点的出栈时机和打印时机都延后了
void postOrder(Node root) {
    struct ListNode stack;
    initStack(&stack);
    while (root != NULL || !isEmpty(&stack)) {
        while (root != NULL) {
            pushStack(&stack, root);
            root->flag = 0;  //首次入栈时，只能代表左子树遍历完成，所以flag置0
            root = root->left;
        }
        root = peekStack(&stack);  //注意这里只是获取到结点，并没有进行出栈操作，因为需要等待右子树遍历完才能出栈
        if (root->flag == 0) {  //如果仅仅遍历了左子树，那么flag就等于0
            root->flag = 1;    //此时标记为1表示遍历右子树
            root = root->right;
        } else {
            printf("%c ", root->element);  //当flag为1时走这边，此时左右都遍历完成了，这时再打印值出来
            popStack(&stack);  ////这时再把对应的结点出栈，因为左右都遍历了
            root = NULL;  //置为NULL，下一轮直接跳过while，然后继续取栈中剩余的结点，重复上述操作
        }
    }
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
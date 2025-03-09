#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef int E;
/*链栈(Linked Stack) - 先进后出结构*/
typedef struct ListNode * Node;
struct ListNode {
    E element;
    struct ListNode * next;
};
void init(Node head) {head->next = NULL;}
/**
 * 将一个元素推到栈里
 * @param stack 链表实现的链栈
 * @param element 待插入的元素
 * @return 元素推入成功返回true, 否则返回false
 */
bool pushStack(Node head, E element) {
    Node newNode = malloc(sizeof(struct ListNode));
    if (newNode == NULL) return false;
    newNode->element = element;
    newNode->next = head->next;
    head->next = newNode;
    return true;
}
bool isEmpty(Node head) {return head->next == NULL;}
/**
 * 删除此栈顶部的元素
 * @param head 链表实现的链栈
 * @return 返回删除的栈顶元素
 */
E popStack(Node head) {
    Node top = head->next;
    E e = top->element;
    head->next = head->next->next;
    free(top);
    return e;
}
void print(Node node) {
    if (node == NULL) {  //递归出口
        printf("|");
        return;
    }
    print(node->next);
    printf("%d, ", node->element);
}
void printStack(Node head) {
    print(head->next);
    printf("\n");
}
int main() {
    struct ListNode head;
    init(&head);
    for (int i = 0; i < 3; ++i) {
        pushStack(&head, i*100);
    }
    printStack(&head);
    while (!isEmpty(&head)) {
        printf("%d ", popStack(&head));   //将栈中所有元素依次出栈
    }
}
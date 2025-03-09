#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef int E;
/*循环单链表(Singly Circular Linked List)*/
typedef struct CListNode * CNode;
struct CListNode {
    E element;
    struct CListNode * next;
};
void init(CNode head) {head->next = head;}
bool insertCList(CNode head, E element, int index) {
    if (index < 1) return false;
    CNode prevNode = head;
    while (--index) {
        prevNode = prevNode->next;
        if (prevNode == head)
            return false;
    }
    CNode newNode = malloc(sizeof(struct CListNode));
    if (newNode == NULL) return false;
    newNode->element = element;
    newNode->next = prevNode->next;
    prevNode->next = newNode;
    return true;
}
bool deleteCList(CNode head, int index) {
    if (index < 1) return false;
    CNode prevNode = head;
    while (--index) {
        prevNode = prevNode->next;
        if (prevNode == head)
            return false;
    }
    if (prevNode->next == head) return false;
    CNode targetNode = prevNode->next;
    prevNode->next = prevNode->next->next;
    free(targetNode);
    return true;
}
void print(CNode head) {
    CNode temp = head;
    while (temp->next != head){
        temp = temp->next;
        printf("%d ", temp->element);
    }
    printf("\n");
}
E * get(CNode head, int index) {
    if (index < 1) return false;
    CNode temp = head;
    while (index--) {
        temp = temp->next;
        if (temp == head)
            return NULL;
    }
    return &temp->element;
}
int find(CNode head, E element) {
    CNode temp = head->next;
    int i = 1;
    while (temp != head) {
        if (temp->element == element) return i;
        temp = temp->next;
        i++;
    }
    return -1;
}
int size(CNode head) {
    CNode temp = head;
    int size = 0;
    while (temp->next != head){
        temp = temp->next;
        size++;
    }
    return size;
}
int main() {
    struct CListNode head;
    init(&head);
    for (int i = 0; i < 10; i++) {
        insertCList(&head, (i+1)*10, i+1);
    }
    printf("Size: %d, LinkedList: ", size(&head));
    print(&head);
    int i;
    while (1) {
        printf("-------------------------     ");
        if (scanf("%d", &i) && i < 1) return 0;
        E * e = get(&head, i);
        int index = find(&head, *e);
        printf("{\"element\": %d, \"index\": %d}\n", *e, index);
        deleteCList(&head, i);
        printf("size: %d\n", size(&head));
        print(&head);
    }
}
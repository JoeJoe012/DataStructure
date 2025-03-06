#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef int E;
/*单链表(Singly Linked List)*/
typedef struct ListNode * Node;
struct ListNode {
    E element;
    struct ListNode * next;
};
void init(Node head) {head->next = NULL;}
/**
 * 将指定元素插入到此链表中的指定位置
 *   ·单链表中的结点都有一个指向后继结点的指针, 因此插入操作的关键是找到指定位置的前驱结点(也就是上一个结点)
 * @param head 操作链表的头结点
 * @param element 待插入的元素
 * @param index 插入的位置, index的位序从1开始
 * @return 插入成功返回true, 否则返回false
 */
bool insertList(Node head, E element, int index) {
    if (index < 1) return false;
    while (--index) {    //while(--index){}条件表达式循环index-1次, 寻找目标位置的前驱结点
        head = head->next;
        if (head == NULL)    //若寻找过程中没有后续的结点, 则说明index超出可插入的范围
            return false; 
    }
    Node newNode = malloc(sizeof(struct ListNode));
    if (newNode == NULL) return false;
    newNode->element = element;
    newNode->next = head->next;    //到这步, head指向目标位置的前驱结点
    head->next = newNode;
    return true;
}
/**
 * 删除此链表中指定位置的元素
 *   ·单链表删除操作的关键是找到目标位置的前驱结点
 * @param head 操作链表的头结点
 * @param index 删除的位置, index的位序从1开始
 * @return 若删除成功返回true, 否则返回false
 */
bool deleteList(Node head, int index) {
    if (index < 1) return false;
    while (--index) {
        head = head->next;
        if (head == NULL)
            return false;
    }
    if (head->next == NULL) {    //待删除结点为NULL则直接返回false
        return false;
    }
    Node targetNode = head->next;
    head->next = head->next->next;
    free(targetNode);
    return true;
}
void print(Node head) {
    while (head->next != NULL) {
        head = head->next;
        printf("%d ", head->element);
    }
    printf("\n");
}
E * get(Node head, int index) {
    if (index < 1) return NULL;
    while (index--) {
        head = head->next;
        if (head == NULL)
            return NULL;
    }
    return &head->element;
}
int find(Node head, E element) {
    head = head->next;
    int i = 1;
    while(head != NULL) {
        if (head->element == element) return i;
        head = head->next;
        i++;
    }
    return -1;
}
int size(Node head) {
    int size = 0;
    while (head->next != NULL) {    //如果下一个为NULL那就停止
        head = head->next;
        size++;
    }
    return size;
}
int main() {
    struct ListNode head;
    init(&head);
    for (int i = 0; i < 10; i++) {
        insertList(&head, (i+1)*10, i+1);
    }
    printf("Size: %d, LinkedList: ", size(&head));
    print(&head);
    int i;
    while (1) {
        printf("------------------------------");
        if (scanf("%d", &i) && i < 1) return 0;
        E * e = get(&head, i);
        int index = find(&head, *e);
        printf("{\"element\": %d, \"index\": %d}\n", *e, index);
        deleteList(&head, i);
        printf("size: %d\n", size(&head));
        print(&head);
    }
}
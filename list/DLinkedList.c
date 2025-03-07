#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef int E;
/*双向链表(Doubly Linked List)*/
typedef struct DListNode * DNode;
struct DListNode {
    E element;
    struct DListNode * prev;  //指向前驱节点的指针
    struct DListNode * next;  //指向后继节点的指针
};
void init(DNode head) {head->prev = head->next = NULL;}
/**
 * 将指定元素插入到此双向链表中的指定位置
 *   ·虽然双向链表中的结点都有一个指向前驱的指针和一个指向后继的指针,
 *    但是可插入的范围为[1,size+1], 因此此双链表的插入操作也是寻找指定位置的前驱节点(和单链表一样)
 *   ·为什么双链表的节点有两个指针, 插入操作还是要找指定位置的前驱节点呢?
 *    解: 思考两种情况: 
 *        I. 第一次执行insertDList(, , 1);
 *        II. 当前链表大小size, 执行insertDList(, , size+1);
 * @param head 双向链表的头节点
 * @param element 待插入的元素
 * @param index 插入的位置, index位序从1开始
 * @return 插入成功返回true, 否则返回false
 */
bool insertDList(DNode head, E element, int index) {
    if (index < 1) return false;
    while (--index) {
        head = head->next;
        if (head == NULL)
            return false;
    }
    DNode newNode = malloc(sizeof(struct DListNode));
    if (newNode == NULL) return false;
    newNode->element = element;
    if (head->next != NULL) {
        head->next->prev = newNode;
        newNode->next = head->next;
        newNode->prev = head;
        head->next = newNode;
    } else {
        newNode->next = NULL;
        newNode->prev = head;
        head->next = newNode;
    }
    return true;
}
/**
 * 删除此双向链表中指定位置的元素
 *   ·单链表删除操作需寻找目标位置的前驱节点
 *   ·双向链表删除操作找目标位置的节点就可以了
 * @param head 双向链表的头节点
 * @param index 插入的位置, index的位序从1开始
 * @return 插入成功返回true, 否则返回false
 */
bool deleteDList(DNode head, int index) {
    if (index < 1) return false;
    while (index--) {
        head = head->next;
        if (head == NULL)
            return false;
    }
    DNode targetNode = head;
    if (head->next != NULL) {  //需判断目标位置的后继节点是否为NULL, 避免NullPointerException
        head->next->prev = head->prev;
        head->prev->next = head->next;      
    } else {
        head->prev->next = NULL;
    }
    free(targetNode);
    return true;
}
void print(DNode head) {
    while (head->next != NULL) {
        head = head->next;
        printf("%d ", head->element);
    }
    printf("\n");
}
E * get(DNode head, int index) {
    if (index < 1) return NULL;
    while (index--) {
        head = head->next;
        if (head == NULL)
            return NULL;
    }
    return &head->element;
}
int find(DNode head, E element) {
    head = head->next;
    int i = 1;
    while (head != NULL) {
        if (head->element == element) return i;
        head = head->next;
        i++;
    }
    return -1;
}
int size(DNode head) {
    int size = 0;
    while (head->next != NULL) {
        head = head->next;
        size++;
    }
    return size;
}
int main() {
    struct DListNode head;
    init(&head);
    for (int i = 0; i < 10; i++) {
        insertDList(&head, (i+1)*10, i+1);
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
        deleteDList(&head, i);
        printf("size: %d\n", size(&head));
        print(&head);
    }
}
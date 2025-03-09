#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef int E;
typedef struct ListNode * Node;
struct ListNode {
    E element;
    struct ListNode * next;
};
/*队列(Queue) - 先进先出结构*/
typedef struct Queue * LinkedQueue;
struct Queue {  //因为要存储队首指针和队尾指针，所以这里封装一个新的结构体
    Node front;  //队首指针
    Node rear;  //队尾指针
};
bool init(LinkedQueue queue) {
    Node head = malloc(sizeof(struct ListNode));
    if (head == NULL) return false;
    head->next = NULL;
    queue->front = queue->rear = head;
    return true;
}
/**
 * 将元素添加到此队列的队尾位置
 * @param queue 队列
 * @param element 插入的元素
 * @return 插入成功返回true, 否则返回false
 */
bool offerQueue(LinkedQueue queue, E element) {
    Node newNode = malloc(sizeof(struct ListNode));
    if (newNode == NULL) return false;
    newNode->element = element;
    newNode->next = NULL;   
    queue->rear->next = newNode;  //先让尾节点的next指向新的节点
    queue->rear = newNode;    //然后让队尾指针指向新的尾节点
    return true;
}
bool isEmpty(LinkedQueue queue) {
    return queue->front == queue->rear;
}
/**
 * 删除此队列的头部元素
 * @param queue 队列
 * @return 返回删除的元素
 */
E pollQueue(LinkedQueue queue) {
    Node temp = queue->front->next;
    E e = temp->element;
    queue->front->next = queue->front->next->next;  //直接让头结点指向下下个结点
    if (queue->rear == temp)
        queue->rear = queue->front;  //如果队尾就是待出队的结点，那么队尾回到队首位置上
    free(temp);
    return e;
}
void print(LinkedQueue queue) {
    printf("<<< ");
    Node temp = queue->front;  //queue->front就是单链表的头节点, 后面打印操作和单链表一样
    while (temp->next != NULL) {
        temp = temp->next;
        printf("%d ", temp->element);
    }
    printf("<<<\n");
}
int main() {
    struct Queue queue;
    init(&queue);
    for (int i = 0; i < 5; ++i) {
        offerQueue(&queue, (i + 1)*100);
    }
    print(&queue);
    while (!isEmpty(&queue)){
        printf("%d ", pollQueue(&queue));
    }
}
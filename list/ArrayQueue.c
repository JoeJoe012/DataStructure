#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
static const int DEFAULT_CAPACITY = 10;
typedef int E;
/*数组实现的循环队列(Queue)*/
typedef struct Queue * ArrayQueue;
struct Queue {
    E * array;
    int capacity;
    int front;  //队首指针指向出队了的元素
    int rear;  //队尾指针指向最后插入的元素
};
bool init(ArrayQueue queue) {
    queue->array = malloc(sizeof(E) * DEFAULT_CAPACITY);
    if (queue->array == NULL) return false;
    queue->capacity = DEFAULT_CAPACITY;
    queue->front = queue->rear = 0;
    return true;
}
/**
 * 将元素添加到此队列的队尾位置
 *   ·判断队列是否已满的条件: (queue->rear + 1) % queue->capacity == queue->front
 * @param queue 数组实现的循环队列
 * @param element 插入的元素
 * @return 插入成功返回true, 否则返回false
 */
bool offerQueue(ArrayQueue queue, E element) {
    if ((queue->rear + 1) % queue->capacity == queue->front)  //先判断队列是否已满，如果队尾下一个就是队首，那么说明已满
        return false;
    queue->rear = (queue->rear + 1) % queue->capacity;  //队尾先向前移动一位，注意取余计算才能实现循环
    queue->array[queue->rear] = element;
    return true;
}
bool isEmpty(ArrayQueue queue) {
    return queue->front == queue->rear;  //队首指针和队尾指针相等时, 队列为空
}
/**
 * 删除此队列的头部元素
 * @param queue 数组实现的循环队列
 * @return 返回删除的元素
 */
E pollQueue(ArrayQueue queue) {
    queue->front = (queue->front + 1) % queue->capacity;  //队首指针后移一位
    return queue->array[queue->front];
}
void print(ArrayQueue queue) {
    printf("<<< ");
    int i = queue->front;
    while (i != queue->rear) {
        i = (i + 1) % queue->capacity;
        printf("%d ", queue->array[i]);
    }
    printf("<<<\n");
}
int main() {
    struct Queue queue;
    init(&queue);
    for (int i = 0; i < 5; ++i) {
        offerQueue(&queue, (i + 1) * 100);
    }
    print(&queue);
    while (!isEmpty(&queue)) {
        printf("%d ", pollQueue(&queue));
    }
}
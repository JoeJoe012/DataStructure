#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
static const int DEFAULT_CAPACITY = 10;
typedef int E;
/*顺序表(Sequence List)*/
typedef struct List * ArrayList;
struct List {
    E * array;  //指向顺序表的底层数组
    int capacity;  //数组的容量
    int size;  //顺序表中的元素数量
};
/**
 * 检查插入的范围: 
 *   ·数组中元素的索引范围为[0,size-1], 可在最后面插入元素，因此数组中插入元素的范围为[0,size]
 *   ·序表位序从1开始, 因此顺序表中插入元素的范围为[1,size+1]
 * @return index在插入的范围内返回true，否则返回false
 */
bool rangeCheckForInsert(int index, int size) {
    if (index < 1 || index > size + 1)
        return false;
    return true;
}
/**
 * 检查元素索引的范围:
 *   ·数据中元素的索引访问为[0,size-1]
 *   ·顺序表位序从1开始, 因此顺序表中元素的索引范围为[1,size]
 */
bool checkIndex(int index, int size) {
    if (index < 1 || index > size)
        return false;
    return true;
}
bool init(ArrayList list) {
    list->array = malloc(sizeof(E) * DEFAULT_CAPACITY);
    if(list->array == NULL) return false;
    list->capacity = DEFAULT_CAPACITY;
    list->size = 0;
    return true;
}
bool grow(ArrayList list) {
    int newCapacity = list->capacity + (list->capacity >> 1);
    E * newArray = realloc(list->array, sizeof(E) * newCapacity);
    if (newArray == NULL) return false;
    list->array = newArray;
    list->capacity = newCapacity;
    return true;
}
/**
 * 将指定元素插入到此顺序表中的指定位置
 * @param list 操作的顺序表
 * @param element 待插入的元素
 * @param index 插入的位置, index的位序从1开始
 * @return 插入成功返回ture, 否则返回false
 */
bool insertList(ArrayList list, E element, int index) {
    if (rangeCheckForInsert(index, list->size) == false)
        return false;
    if (list->size == list->capacity && grow(list) == false) 
        return false;
    for (int i = list->size; i > index - 1; i--) {  //输入参数index位序从1开始, 实际插入位置为index-1
        list->array[i] = list->array[i - 1];    //指定位置以及位置之后的元素往后移一位
    }
    list->array[index - 1] = element;
    list->size++;
    return true;
}
/**
 * 删除此顺序表中指定位置的元素
 * @param list 操作的顺序表
 * @param index 插入的位置, index的位序从1开始
 * @return 删除成功返回true, 否则返回false
 */
bool deleteList(ArrayList list, int index) {
    if (checkIndex(index, list->size) == false)
        return false;
    for (int i = index - 1; i < list->size - 1; i++) {  //输入参数index位序从1开始, 实际删除位置为index-1
        list->array[i] = list->array[i + 1];    //index, index + 1...后面的元素依次覆盖前一个
    }
    list->size--;
    return true;
}
void print(ArrayList list) {
    for (int i = 0; i < list->size; i++)
        printf("%d ", list->array[i]);
    printf("\n");
}
int size(ArrayList list) {
    return list->size;
}
E * get(ArrayList list, int index) {
    if (checkIndex(index, list->size) == false) return NULL;
    return &list->array[index - 1];
}
int find(ArrayList list, E element) {
    for (int i = 0; i < list->size; i++) {
        if (list->array[i] == element)
            return i + 1;
    }
    return -1;
}
int main() {
    struct List list;
    if (init(&list)) {
        for (int i = 1; i <= 30; i++) {
            insertList(&list, i * 10, i);
        }
        print(&list);
    } else {
        printf("顺序表初始化失败!");
    }
    
}
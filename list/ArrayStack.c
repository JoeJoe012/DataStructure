#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
static const int DEFAULT_CAPACITY = 10;
typedef int E;
/*顺序栈(Sequence Stack)*/
typedef struct Stack * ArrayStack;
struct Stack {
    E * array;
    int capacity;
    int top;  //表示当前的栈顶位置, 存的是栈顶元素的下标
};
bool init(ArrayStack stack) {
    stack->array = malloc(sizeof(E) * DEFAULT_CAPACITY);
    if (stack->array == NULL) return false;
    stack->capacity = DEFAULT_CAPACITY;
    stack->top = -1;
    return true;
}
bool grow(ArrayStack stack) {
    int newCapacity = stack->capacity + (stack->capacity >> 1);
    E * newArray = realloc(stack->array, sizeof(struct Stack) * newCapacity);
    if (newArray == NULL) return false;
    stack->array = newArray;
    stack->capacity = newCapacity;
    return true;
}
bool pushStack(ArrayStack stack, E element) {
    if ((stack->top == stack->capacity - 1) && !grow(stack)) return false;
    stack->array[stack->top + 1] = element;
    stack->top++;
    return true;
}
bool isEmpty(ArrayStack stack) {
    return stack->top == -1;
}
E popStack(ArrayStack stack) {
    return stack->array[stack->top--];
}
void print(ArrayStack stack) {
    printf("|");
    for (int i = 0; i <= stack->top; i++) {
        printf("%d, ", stack->array[i]);
    }
    printf("\n");
}
int main() {
    struct Stack stack;
    init(&stack);
    for (int i = 0; i < 3; ++i) {
        pushStack(&stack, i*100);
    }
    print(&stack);
    while (!isEmpty(&stack)) {
        printf("%d ", popStack(&stack));   //将栈中所有元素依次出栈
    }
}
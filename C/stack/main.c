#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct Stack {
  int top;
  int data[MAX];
} Stack;

Stack *init(int size) {
  Stack *s = (Stack *)malloc(sizeof(Stack));
  s->top = -1;
  return s;
}

int isEmpty(Stack *stack) { return stack->top == -1; }

int isFull(Stack *stack) { return stack->top == MAX - 1; }

void push(Stack *stack, int data) {
  if (isFull(stack)) {
    printf("Stack Overflow\n");
    return;
  }
  stack->data[++(stack->top)] = data;
}

void pop(Stack *stack) {
  if (isEmpty(stack)) {
    printf("Error : Stack empty, can't pop.\n");
    return;
  }
  --stack->top;
}

int peek(Stack *stack) {
  int peekVal = stack->data[stack->top];
  printf("Peek: %d\n", peekVal);
  return peekVal;
}

void display(Stack *stack) {
  printf("[ ");
  for (int i = 0; i < stack->top; i++) {
    printf("%d", stack->data[i]);
    if (i != stack->top - 1)
      printf(" , ");
  }
  printf(" ]\n");
}

int main() {
  printf("Stack C Implementation\n");
  Stack *s = init(MAX);
  push(s, 10);
  push(s, 20);
  peek(s);
  push(s, 30);
  pop(s);
  display(s);
  return 1;
}

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int value;
  struct Node *next;
} Node;

typedef struct {
  Node *front;
  Node *back;
} Queue;

void init(Queue *q) {
  q->front = NULL;
  q->back = NULL;
}

int isEmpty(Queue *q) { return q->front == NULL; }

// add elem. @ back. returns success: 0
int enqueue(Queue *q, int value) {
  Node *n = malloc(sizeof(Node)); // create node
  if (!n)
    exit(EXIT_FAILURE);

  n->value = value; // set node
  n->next = NULL;

  if (q->back == NULL) { // queue is empty
    q->front = n;
    q->back = n;
  } else {
    q->back->next = n;
    q->back = n;
  }

  return 0;
}

int dequeue(Queue *q, int *outValue) {
  if (isEmpty(q))
    exit(EXIT_FAILURE);

  Node *n = q->front; // get front node
  if (outValue) {
    *outValue = n->value;
  }

  q->front = n->next; // update front to point to the next value
  if (q->front == NULL) {
    q->back = NULL;
  }
  free(n); // free old front memory allocation

  return 0;
}

void clear(Queue *q) {
  int tmp;
  while (dequeue(q, &tmp) == 0) {
  }
}

void display(Queue *q) {
  Node *cur = q->front;
  printf("[");
  while (cur) {
    printf(" %d ", cur->value);
    cur = cur->next;
  }
  printf("]\n");
}

int main(void) {
  Queue q;
  init(&q);

  /* Enqueue some values */
  for (int i = 1; i <= 5; i++) {
    enqueue(&q, i * 10);
    display(&q);
  }

  /* Dequeue and print all values */
  int value;
  while (!isEmpty(&q)) {
    if (dequeue(&q, &value) == 0) {
      printf("dequeued: %d\n", value);
    }
  }

  /* Make sure everything is freed (safe even if already empty) */
  clear(&q);

  return 0;
}

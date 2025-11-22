#include <stdio.h>

#define CAPACITY 5

typedef struct {
  int data[CAPACITY];
  int head;
  int tail;
  int size;
} Queue;

void init(Queue *q) {
  q->head = 0;
  q->tail = 0;
  q->size = 0;
}

int isEmpty(Queue *q) { return q->size == 0; }
int isFull(Queue *q) { return q->size == CAPACITY; }

int enqueue(Queue *q, int value) {
  if (isFull(q))
    return -1;

  q->data[q->tail] = value;
  q->tail = (q->tail + 1) % CAPACITY;
  q->size++;
  return 0;
}

int dequeue(Queue *q, int *outputValue) {
  if (isEmpty(q))
    return -1;

  if (outputValue)
    *outputValue = q->data[q->head];

  q->head = (q->head + 1) % CAPACITY;
  q->size--;
  return 0;
}

void display(Queue *q) {
  if (isEmpty(q)) {
    printf("[empty]\n");
    return;
  }

  printf("Queue: ");
  int idx = q->head;
  for (int i = 0; i < q->size; ++i) {
    printf("%d ", q->data[idx]);
    idx = (idx + 1) % CAPACITY;
  }
  printf("\n");
}

int main(void) {
  Queue q;
  init(&q);

  printf("Enqueueing 10, 20, 30...\n");
  enqueue(&q, 10);
  enqueue(&q, 20);
  enqueue(&q, 30);
  display(&q);

  int val;

  printf("Dequeuing two elements...\n");
  dequeue(&q, &val);
  printf("Dequeued: %d\n", val);
  dequeue(&q, &val);
  printf("Dequeued: %d\n", val);
  display(&q);

  printf("Enqueueing 40, 50, 60 (to test wraparound)...\n");
  enqueue(&q, 40);
  enqueue(&q, 50);
  enqueue(&q, 60); // should fill queue
  display(&q);

  printf("Attempting enqueue on full queue...\n");
  if (enqueue(&q, 999) == -1) {
    printf("Queue is full, cannot enqueue 999\n");
  }

  printf("Draining queue...\n");
  while (!isEmpty(&q)) {
    dequeue(&q, &val);
    printf("Dequeued: %d\n", val);
  }
  display(&q);

  return 0;
}


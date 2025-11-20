#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node *next;
} Node;

Node *init(int data) {
  Node *head = (Node *)malloc(sizeof(Node));
  head->data = data;
  head->next = NULL;
  return head;
}

void insertAtBegining(Node **head, int data) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->next = *head;
  newNode->data = data;
  *head = newNode;
}

void delete(Node **head, int key) {
  Node *curr = *head;
  Node *prev = NULL;
  if (curr != NULL && curr->data == key) {
    *head = curr->next;
    free(curr);
    return;
  }
  while (curr != NULL && curr->data != key) {
    prev = curr;
    curr = curr->next;
  }

  if (curr == NULL)
    return;

  prev->next = curr->next;
  free(curr);
}

void display(Node *head) {
  Node *curr = head;
  if (curr == NULL) {
    printf("List is empty\n");
    return;
  }

  while (curr != NULL) {
    printf("(%p => data: %d , next: %p) --> ", curr, curr->data, curr->next);
    curr = curr->next;
  }
  printf("NULL\n\n");
}

int main() {
  printf("Linked List C Implementation\n");

  Node *head = init(10);
  insertAtBegining(&head, 20);
  insertAtBegining(&head, 30);
  display(head);
  delete(&head, 30);
  display(head);

  return 1;
}

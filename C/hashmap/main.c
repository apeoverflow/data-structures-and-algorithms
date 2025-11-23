#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 101

typedef struct Entry {
  char *key;
  int value;
  struct Entry *next;
} Entry;

static Entry *table[TABLE_SIZE];

// djb2 hashing algorithm
unsigned int hash(const char *key) {
  // historical seed Bernstein found to give good early results
  unsigned long h = 5381;
  int c;
  while ((c = *key++)) { // foreach char c in key
    // polynomial rolling hash in base 33
    h = ((h << 5) + h) + c; // h = (h * 33) + current_char
  }
  return h % TABLE_SIZE;
}

void put(const char *key, int value) {
  unsigned int idx = hash(key);
  Entry *e = table[idx];
  while (e) { // loop through all entries under idx, if key is found - update
    if (strcmp(key, table[idx]->key) == 0) {
      e->value = value;
      return;
    }
    e = e->next;
  }

  // no existing key found - create
  Entry *newEntry = malloc(sizeof(Entry));
  newEntry->key = strdup(key);
  newEntry->value = value;
  newEntry->next = table[idx];
  table[idx] = newEntry;
}

int *get(const char *key) {
  unsigned int idx = hash(key);
  Entry *e = table[idx];
  while (e) {
    if (strcmp(key, e->key) == 0) {
      return &e->value;
    }
    e = e->next;
  }
  return NULL;
}

void delete(const char *key) {
  unsigned int idx = hash(key);
  Entry *e = table[idx];
  Entry *prev = NULL;
  while (e) {
    if (strcmp(e->key, key) == 0) {
      if (prev)
        prev->next = e->next;
      else
        table[idx] = e->next;
      free(e->key);
      free(e);
      return;
    }
    prev = e;
    e = e->next;
  }
}

int main() {
  put("asdf", 3);
  put("zxcv", 8);

  int *v = get("asdf");
  if (v) {
    printf("asdf: %d\n", *v);
  }

  delete("asdf");
  if (!get("asdf"))
    printf("asdf has been removed\n");

  return 0;
}

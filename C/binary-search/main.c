#include <stdio.h>

int binarySearch(int arr[], int size, int needle) {
  int left = 0;
  int right = size - 1;
  while (left <= right) {
    int middle = left + (right - left) / 2;
    if (arr[middle] == needle)
      return middle;
    else if (arr[middle] < needle)
      left = middle + 1;
    else
      right = middle - 1;
  }
  return -1;
}

int main(void) {
  const int SIZE = 10;
  int arr[SIZE];
  for (int i = 0; i < SIZE; i++) {
    arr[i] = i * 10;
  }
  int needle = 40;
  int idx = binarySearch(arr, SIZE, needle);
  if (idx != -1)
    printf("idx: %d", idx);
  return 0;
}

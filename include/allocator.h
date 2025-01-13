/*

    Heap Allocator

*/


#include <stdbool.h>
#include <stddef.h>

#ifndef ALLOCATOR_H
#define ALLOCATOR_H

typedef struct segment {

  struct segment *above;
  struct segment *below;
  size_t height;
  bool free;

} segment_t;

void *allocate(size_t height);
void deallocate(void *heap_p);

#endif
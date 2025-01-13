/*

    Heap Allocator

*/

#include "include/allocator.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>

segment_t *stalk_p;

void *seed(size_t height) {

    void *heap_p = sbrk(sizeof(segment_t) + height);
    if ((void *) -1 == heap_p) {

        return NULL;

    }

    stalk_p = (segment_t *) heap_p;
    stalk_p->height = height;
    stalk_p->free = false;
    return heap_p;

}

segment_t *elevate() {

    segment_t *target_p = stalk_p;
    while (target_p) {

        if (!target_p->above) {

            return target_p;

        }

        target_p = target_p->above;

    }

    return NULL;

}

segment_t *sort(size_t height) {

    segment_t *target_p = stalk_p;
    while (target_p) {

        if (target_p->free && target_p->height == height) {

            target_p->free = false;
            return target_p;

        } else if (target_p->above && target_p->height > height) {

            /* Implement segment splitting. */

        }

        target_p = target_p->above;

    }

    return NULL;

}

void *bump(size_t height) {

    void *heap_p = sbrk(sizeof(segment_t) + height);
    if ((void *) -1 == heap_p) {

        return NULL;

    }

    segment_t *segment_p = (segment_t *) heap_p;
    segment_t *summit_p = elevate();
    if (!summit_p) {

        return NULL;

    }

    segment_p->height = height;
    segment_p->below = summit_p;
    segment_p->free = false;
    summit_p->above = segment_p;
    return heap_p;

}

void deallocate(void *heap_p) {

    segment_t *segment_p = (segment_t *) (heap_p - sizeof(segment_t));
    if (!segment_p) {

        return;

    }

    segment_p->free = true;

}

void *allocate(size_t height) {

    if (!stalk_p) {

        void *heap_p = seed(height);
        if (!heap_p) {

            return NULL;

        }

        return sizeof(segment_t) + heap_p;

    }

    segment_t *segment_p = sort(height);
    if (!segment_p) {

        segment_p = bump(height);

    }

    void *heap_p = (void *) segment_p;
    return sizeof(segment_t) + heap_p;

}
#pragma once

#include <stdbool.h>

#define fifo_foreach(fifo_header)                                              \
  for (size_t idx = fifo_header->tail; idx != fifo_header->head;               \
       idx = (idx + 1) % fifo_header->size)

struct FifoBufferHeader {
  size_t head;
  size_t tail;
  size_t size;
};

void fifo_header_clear(struct FifoBufferHeader *header);
void fifo_header_init(struct FifoBufferHeader *header, size_t size);
bool fifo_header_empty(struct FifoBufferHeader *header);
bool fifo_header_full(struct FifoBufferHeader *header);
bool fifo_header_enqueue(struct FifoBufferHeader *header, size_t *out_idx);
bool fifo_header_dequeue(struct FifoBufferHeader *header, size_t *out_idx);

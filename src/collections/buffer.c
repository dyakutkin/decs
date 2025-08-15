#include "buffer.h"

void fifo_header_clear(struct FifoBufferHeader *header) {
  header->head = header->tail = 0;
}

void fifo_header_init(struct FifoBufferHeader *header, size_t size) {
  fifo_header_clear(header);
  header->size = size;
}

bool fifo_header_empty(struct FifoBufferHeader *header) {
  return header->head == header->tail;
}

bool fifo_header_full(struct FifoBufferHeader *header) {
  return ((header->head + 1) % header->size) == header->tail;
}

bool fifo_header_enqueue(struct FifoBufferHeader *header, size_t *out_idx) {
  if (fifo_header_full(header)) {
    return false;
  }
  *out_idx = header->head;
  header->head = (header->head + 1) % header->size;
  return true;
}

bool fifo_header_dequeue(struct FifoBufferHeader *header, size_t *out_idx) {
  if (fifo_header_empty(header)) {
    return false;
  }
  *out_idx = header->tail;
  header->tail = (header->tail + 1) % header->size;
  return true;
}

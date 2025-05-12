// ======================================================================================
// Plik z definicje zawarych w biliotece bufora
// cyklicznego
// ======================================================================================
// Jakub Kurek 13-05-2025
// ======================================================================================

#include "ring_buf.h"

int rb_push(Rb_ptr rb, RingData data) {
    int data_pos = rb->push_pos;
    rb->buf[data_pos] = data;
    rb->push_pos = (data_pos + 1) % RB_BUF_ELEMENTS;
    return data_pos;
}

int rb_pop(Rb_ptr rb, RingData* data_ptr) {
    int data_pos = rb->pop_pos;
    rb->pop_pos = (data_pos + 1) % RB_BUF_ELEMENTS;
    *data_ptr = rb->buf[data_pos];
    return data_pos;
}

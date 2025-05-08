#include "ring_buf.h"

void rb_push(Rb_ptr rb, RingData data) {
    int data_pos = rb->push_pos;
    rb->buf[data_pos] = data;
    rb->push_pos = (data_pos + 1) % BUF_ELEMENTS;
}

RingData rb_pop(Rb_ptr rb) {
    int data_pos = rb->pop_pos;
    rb->pop_pos = (data_pos + 1) % BUF_ELEMENTS;
    return rb->buf[data_pos];
}

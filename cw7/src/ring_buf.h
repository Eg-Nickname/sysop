#ifndef RING_BUF
#define RING_BUF

#define BUF_ELEMENTS 8
#define ELEMENT_SIZE 32

typedef struct {
    char element[ELEMENT_SIZE];
} RingData;

typedef struct {
    RingData buf[BUF_ELEMENTS];
    int push_pos, pop_pos;
} RingBuff;

typedef RingBuff *Rb_ptr;

void rb_push(Rb_ptr, RingData);
RingData rb_pop(Rb_ptr);

#define SHM_SIZE sizeof(RingBuff)

#endif

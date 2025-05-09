#ifndef RING_BUF
#define RING_BUF

#define RB_BUF_ELEMENTS 8
#define RB_ELEMENT_SIZE 7

typedef struct {
    char element[RB_ELEMENT_SIZE];
} RingData;

typedef struct {
    RingData buf[RB_BUF_ELEMENTS];
    int push_pos, pop_pos;
} RingBuf;

typedef RingBuf *Rb_ptr;

// Puts data in ring bufer and returns postion in rb
int rb_push(Rb_ptr, RingData);
// Puts data into passed ptr and returns postion of inserted data
int rb_pop(Rb_ptr, RingData *);

#define SHM_SIZE sizeof(RingBuf)

#endif

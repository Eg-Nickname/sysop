#include "mqueue.h"

#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>

int queue_create(const char* name, long queue_max_msg, long queue_msg_size) {
    struct mq_attr attr = {.mq_flags = 0,
                           .mq_maxmsg = queue_max_msg,
                           .mq_msgsize = queue_msg_size,
                           .mq_curmsgs = 0};

    int qd = mq_open(name, O_CREAT | O_EXCL, 0666, attr);
    if (qd == -1) {
        perror("mq creation error");
        return 0;
    }
    return qd;
}

int queue_open(const char* name, int oflag) {
    int qd = mq_open(name, oflag);
    if (qd == -1) {
        perror("mq open error");
        return 0;
    }
    return qd;
}

int queue_close(int qd) {
    int unlink_ret = mq_close(qd);
    if (unlink_ret == -1) {
        perror("mq close error");
        return 0;
    }
    return 1;
}

int queue_destroy(const char* name) {
    int unlink_ret = mq_unlink(name);
    if (unlink_ret == -1) {
        perror("mq unlink error");
        return 0;
    }
    return 1;
}

int queue_get_attr(int qd, queue_attr* attr_ptr) {
    int get_attr_ret = mq_getattr(qd, attr_ptr);
    if (get_attr_ret == -1) {
        perror("get queue attr error");
        return 0;
    }
    return 1;
}

int queue_send(int qd, char* msg_ptr, size_t msg_size, unsigned int priotrity) {
    int send_ret = mq_send(qd, msg_ptr, msg_size, priotrity);
    if (send_ret == -1) {
        perror("queue msg send error");
        return 0;
    }
    return 1;
}

int queue_recive(int qd, char* msg_ptr, size_t msg_size) {
    int recive_ret = mq_receive(qd, msg_ptr, msg_size, NULL);
    if (recive_ret == -1) {
        perror("queue msg recive error");
        return 0;
    }
    return 1;
}

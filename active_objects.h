#ifndef ACTIVE_OBJECTS_H
#define ACTIVE_OBJECTS_H
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>
#include <time.h>
//linked list
typedef struct node {
    struct node *next;
    void *data;
} _node;
//queue with mutex and thread
typedef struct queue {
    pthread_cond_t _cond;
    pthread_mutex_t _mutex;
    _node *head;
    _node *tail;
} _queue;
//active object that has a thread and a queue
typedef struct activeObject {
    pthread_t pthr;
    _queue *queue;
    void *(*func)(void *);
} activeObject;
// global four pointers to active object
extern activeObject *_p1, *_p2, *_p3, *_p4;
//random number generator with 6 digits
void randonNum(activeObject *, int );
// test prime number
int check_prime(unsigned int );
// enqueue and dequeue
void enqueue(_queue *, void *);
void *dequeue(_queue *);
//functions
void *start(void *);
activeObject *createAO(void *(*func)(void *));
void cleanQueue(_queue *);
void stop(activeObject *, activeObject *, activeObject *, activeObject *);
_queue *getActiveObjectQueue(activeObject *);
void *active_1(void *);
void *active_2(void *);
void *active_3(void *);
void *active_4(void *);

#endif  // ACTIVE_OBJECTS_H

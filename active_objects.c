#include "active_objects.h"

activeObject *_p1, *_p2, *_p3, *_p4;
void *start(void *arg)
{
    activeObject* self = arg;

    for (void* task = dequeue(self->queue); task != NULL; task = dequeue(self->queue))
    {
        self->func(task);
    }

    return NULL;
}

activeObject *createAO(void *(*func)(void *))
{
    activeObject *active = calloc(1,sizeof(activeObject));
    if (active == NULL)
    {
        printf( "calloc failed.\n");
        exit(1);
    }
    active->queue = calloc(1, sizeof(_queue));
    if (active->queue == NULL)
    {
        printf("calloc failed.\n");
        exit(1);
    }
    pthread_mutex_init(&(active->queue->_mutex), NULL);
    pthread_cond_init(&(active->queue->_cond), NULL);

    active->queue->head = NULL;
    active->func = func;
    active->queue->tail = NULL;

    pthread_create(&(active->pthr), NULL, start, active);
    return active;
}



void stop(activeObject *_p1, activeObject *_p2, activeObject *_p3, activeObject *_p4)
{
    // stop all active objects and free memory
    // start with _p1 and end with _p4
    enqueue(_p1->queue, NULL);
    pthread_join(_p1->pthr, NULL);
    cleanQueue(_p1->queue);
    free(_p1);

    enqueue(_p2->queue, NULL);
    pthread_join(_p2->pthr, NULL);
    cleanQueue(_p2->queue);
    free(_p2);

    enqueue(_p3->queue, NULL);
    pthread_join(_p3->pthr, NULL);
    cleanQueue(_p3->queue);
    free(_p3);

    enqueue(_p4->queue, NULL);
    pthread_join(_p4->pthr, NULL);
    cleanQueue(_p4->queue);
    free(_p4);
}


_queue *getActiveObjectQueue(activeObject *ao) {return ao->queue;}

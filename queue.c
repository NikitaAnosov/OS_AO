#include "active_objects.h"

void enqueue(_queue *queue, void *num)
{
    _node *new_node = calloc(1,sizeof(_node));
    if (new_node == NULL)
    {
        fprintf(stderr, " calloc failed \n");
        exit(1);
    }
    new_node->data = num;
    new_node->next = NULL;
    pthread_mutex_lock(&(queue->_mutex));
    if (queue->head != NULL)
    {
        queue->tail->next = new_node;
        queue->tail = new_node;
    }
    else
    {
        queue->head = new_node;
        queue->tail = new_node;
    }
    pthread_cond_signal(&(queue->_cond));
    pthread_mutex_unlock(&(queue->_mutex));
}

void *dequeue(_queue *queue)
{
    pthread_mutex_lock(&(queue->_mutex));
    while (queue->head == NULL)
    {
        pthread_cond_wait(&(queue->_cond), &(queue->_mutex));
    }
    _node *head = queue->head;
    queue->head = head->next;
    void *num = head->data;
    if (queue->head == NULL)
    {
        queue->tail = NULL;
    }
    free(head);
    pthread_mutex_unlock(&(queue->_mutex));
    return num;
}
// clean all elements in the queue
void cleanQueue(_queue *queue)
{
    pthread_mutex_lock(&(queue->_mutex));
    _node *temp = queue->head;
    while (temp != NULL)
    {
        _node *nodeQ = temp;
        nodeQ = temp->next;
        free(nodeQ);
    }
    pthread_cond_destroy(&(queue->_cond));
    pthread_mutex_unlock(&(queue->_mutex));
    pthread_mutex_destroy(&(queue->_mutex));
    free(queue);
}
#ifndef DEQUE_H
#define DEQUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * @brief Represents a circular-array based Double-Ended Queue (Deque).
 */
typedef struct
{
    int *array;   /**< Pointer to the dynamically allocated circular array. */
    int front;    /**< Index of the front element. */
    int rear;     /**< Index of the next insertion position at the rear. */
    int capacity; /**< Internal capacity of the buffer (actual usable size is capacity - 1). */
} Deque;

/**
 * @brief Initializes a new Deque using a circular buffer.
 * @param capacity The maximum number of elements the deque can hold.
 * @return A new Deque instance.
 */
Deque init(int capacity)
{
    if (capacity <= 0)
    {
        perror("Invalid capacity for Deque");
        exit(EXIT_FAILURE);
    }
    Deque queue;
    queue.array = (int *)malloc((capacity + 1) * sizeof(int));
    if (!queue.array)
    {
        perror("Failed to initialize Deque");
        exit(EXIT_FAILURE);
    }
    queue.front = 0;
    queue.rear = 0;
    queue.capacity = capacity + 1;
    return queue;
}

/**
 * @brief Creates a deep copy of an existing Deque.
 * @param queue The Deque to be copied.
 * @return A new Deque instance.
 */
Deque copy(const Deque queue)
{
    Deque copied = init(queue.capacity - 1);
    int curr = queue.front;
    while (curr != queue.rear)
    {
        copied.array[copied.rear++] = queue.array[curr];
        curr = (curr + 1) % queue.capacity;
    }
    return copied;
}

/**
 * @brief Clears all elements from the Deque.
 * @param queue A pointer to the Deque to be cleared.
 */
void clear(Deque *queue)
{
    queue->front = 0;
    queue->rear = 0;
}

/**
 * @brief Deallocates the memory used by the Deque.
 * @param vector A pointer to the Deque to be destroyed.
 */
void destroy(Deque *vector)
{
    free(vector->array);
    vector->array = NULL;
    vector->front = 0;
    vector->rear = 0;
    vector->capacity = 0;
}

/**
 * @brief Checks if the Deque is empty.
 * @param queue The Deque to check.
 * @return true if the deque is empty, false otherwise.
 */
bool isEmpty(const Deque queue)
{
    return queue.front == queue.rear;
}

/**
 * @brief Checks whether the Deque is full.
 * @param queue The Deque to check.
 * @return true if the deque is full, false otherwise.
 */
bool isFull(const Deque queue)
{
    return (queue.rear + 1) % queue.capacity == queue.front;
}

/**
 * @brief Returns the current number of elements in the Deque.
 * @param queue The Deque to query.
 * @return The number of elements currently stored in the deque.
 */
int length(const Deque queue)
{
    if (queue.rear >= queue.front)
        return queue.rear - queue.front;
    return queue.capacity - queue.front + queue.rear;
}

/**
 * @brief Adds an element to the front of the Deque.
 * @param queue A pointer to the Deque.
 * @param value The integer value to be added.
 */
void enqueueFront(Deque *queue, int value)
{
    if (isFull(*queue))
    {
        printf("Deque Overflow\n");
        return;
    }
    queue->front = (queue->front - 1 + queue->capacity) % queue->capacity;
    queue->array[queue->front] = value;
}

/**
 * @brief Returns the element at the front of the Deque without removing it.
 * @param queue The Deque to peek at.
 * @return The value of the front element, or -1 if the deque is empty.
 */
int peekFront(const Deque queue)
{
    if (isEmpty(queue))
    {
        printf("Deque Underflow\n");
        return -1;
    }
    return queue.array[queue.front];
}

/**
 * @brief Removes and returns the element from the front of the Deque.
 * @param queue A pointer to the Deque.
 * @return The value of the dequeued element, or -1 if the deque is empty.
 */
int dequeueFront(Deque *queue)
{
    if (isEmpty(*queue))
    {
        printf("Deque Underflow\n");
        return -1;
    }
    int value = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    return value;
}

/**
 * @brief Adds an element to the rear of the Deque.
 * @param queue A pointer to the Deque.
 * @param value The integer value to be added.
 */
void enqueueRear(Deque *queue, int value)
{
    if (isFull(*queue))
    {
        printf("Deque Overflow\n");
        return;
    }
    queue->array[queue->rear] = value;
    queue->rear = (queue->rear + 1) % queue->capacity;
}

/**
 * @brief Returns the element at the rear of the Deque without removing it.
 * @param queue The Deque to peek at.
 * @return The value of the rear element, or -1 if the deque is empty.
 */
int peekRear(const Deque queue)
{
    if (isEmpty(queue))
    {
        printf("Deque Underflow\n");
        return -1;
    }
    return queue.array[(queue.rear - 1 + queue.capacity) % queue.capacity];
}

/**
 * @brief Removes and returns the element from the rear of the Deque.
 * @param queue A pointer to the Deque.
 * @return The value of the dequeued element, or -1 if the deque is empty.
 */
int dequeueRear(Deque *queue)
{
    if (isEmpty(*queue))
    {
        printf("Deque Underflow\n");
        return -1;
    }
    queue->rear = (queue->rear - 1 + queue->capacity) % queue->capacity;
    int value = queue->array[queue->rear];
    return value;
}

/**
 * @brief Prints the elements of the Deque from front to rear.
 * @param queue The Deque to traverse and print.
 */
void traverse(const Deque queue)
{
    int len = length(queue);
    printf("[");
    int i = queue.front;
    while (i != queue.rear)
    {
        printf(" %d", queue.array[i]);
        i = (i + 1) % queue.capacity;
    }
    printf(" ] : %d/%d\n", len, queue.capacity - 1);
}

#endif // DEQUE_H
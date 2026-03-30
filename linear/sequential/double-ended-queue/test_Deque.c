#include <assert.h>
#include <string.h>
#include "adt_Deque.h"

#define TEST_START(name) printf("\n--- Starting Test: %s ---\n", name)
#define TEST_PASSED(name) printf("--- Test PASSED: %s ---\n", name)
#define TEST_FAILED(name) printf("--- Test FAILED: %s ---\n", name)
#define ASSERT_TRUE(condition, message)            \
    if (!(condition))                              \
    {                                              \
        printf("ASSERTION FAILED: %s\n", message); \
        exit(EXIT_FAILURE);                        \
    }

void test_init_destroy()
{
    TEST_START("Initialization and Destruction");

    Deque dq1 = init(5);
    ASSERT_TRUE(dq1.array != NULL, "Array not allocated during init");
    ASSERT_TRUE(dq1.capacity == 6, "Internal capacity incorrect (should be capacity+1)");
    ASSERT_TRUE(length(dq1) == 0, "Length not initialized to 0");
    ASSERT_TRUE(dq1.front == 0, "Front not initialized correctly");
    ASSERT_TRUE(dq1.rear == 0, "Rear not initialized correctly");
    printf("Init 1: Capacity %d, Front %d, Rear %d, Length %d\n", dq1.capacity, dq1.front, dq1.rear, length(dq1));

    destroy(&dq1);
    ASSERT_TRUE(dq1.array == NULL, "Array not freed during destroy");
    ASSERT_TRUE(dq1.capacity == 0, "Capacity not reset after destroy");
    ASSERT_TRUE(length(dq1) == 0, "Length not reset after destroy");
    ASSERT_TRUE(dq1.front == 0, "Front not reset after destroy");
    ASSERT_TRUE(dq1.rear == 0, "Rear not reset after destroy");
    printf("Destroy 1: Array NULL, Capacity 0, Length 0\n");

    Deque dq2 = init(1);
    ASSERT_TRUE(dq2.array != NULL, "Array not allocated during init (cap 1)");
    ASSERT_TRUE(dq2.capacity == 2, "Internal capacity incorrect for cap 1");
    ASSERT_TRUE(dq2.front == 0, "Front not initialized correctly for cap 1");
    ASSERT_TRUE(dq2.rear == 0, "Rear not initialized correctly for cap 1");
    destroy(&dq2);

    TEST_PASSED("Initialization and Destruction");
}

void test_empty_full_checks()
{
    TEST_START("Empty and Full Checks");

    Deque dq = init(3);
    printf("Initial: ");
    traverse(dq);
    ASSERT_TRUE(isEmpty(dq), "Deque should be empty initially");
    ASSERT_TRUE(!isFull(dq), "Deque should not be full initially");

    enqueueRear(&dq, 10);
    printf("After enqueueRear 10: ");
    traverse(dq);
    ASSERT_TRUE(!isEmpty(dq), "Deque should not be empty after enqueue");
    ASSERT_TRUE(!isFull(dq), "Deque should not be full");

    enqueueFront(&dq, 5);
    printf("After enqueueFront 5: ");
    traverse(dq);
    ASSERT_TRUE(!isEmpty(dq), "Deque should not be empty");
    ASSERT_TRUE(!isFull(dq), "Deque should not yet be full");

    enqueueRear(&dq, 15);
    printf("After enqueueRear 15: ");
    traverse(dq);
    ASSERT_TRUE(isFull(dq), "Deque should now be full");

    dequeueFront(&dq);
    dequeueRear(&dq);
    dequeueFront(&dq);
    printf("After dequeuing all: ");
    traverse(dq);
    ASSERT_TRUE(isEmpty(dq), "Deque should be empty after dequeuing all");
    ASSERT_TRUE(!isFull(dq), "Deque should not be full after empty");

    destroy(&dq);
    TEST_PASSED("Empty and Full Checks");
}

void test_enqueue_dequeue_front()
{
    TEST_START("Enqueue and Dequeue Front");
    Deque dq = init(5);

    enqueueFront(&dq, 10);
    ASSERT_TRUE(peekFront(dq) == 10, "Peek front failed after 1st enqueue front");
    ASSERT_TRUE(length(dq) == 1, "Length incorrect after 1st enqueue front");
    printf("After enqueueFront 10: ");
    traverse(dq);

    enqueueFront(&dq, 20);
    ASSERT_TRUE(peekFront(dq) == 20, "Peek front failed after 2nd enqueue front");
    ASSERT_TRUE(length(dq) == 2, "Length incorrect after 2nd enqueue front");
    printf("After enqueueFront 20: ");
    traverse(dq);

    int val = dequeueFront(&dq);
    ASSERT_TRUE(val == 20, "Dequeue front returned incorrect value (1st)");
    ASSERT_TRUE(peekFront(dq) == 10, "Peek front failed after 1st dequeue front");
    ASSERT_TRUE(length(dq) == 1, "Length incorrect after 1st dequeue front");

    val = dequeueFront(&dq);
    ASSERT_TRUE(val == 10, "Dequeue front returned incorrect value (2nd)");
    ASSERT_TRUE(isEmpty(dq), "Deque not empty after 2nd dequeue front");
    ASSERT_TRUE(length(dq) == 0, "Length incorrect after 2nd dequeue front");

    ASSERT_TRUE(dq.front == dq.rear, "Front and rear should match when empty");

    destroy(&dq);
    TEST_PASSED("Enqueue and Dequeue Front");
}

void test_enqueue_dequeue_rear()
{
    TEST_START("Enqueue and Dequeue Rear");
    Deque dq = init(5);

    enqueueRear(&dq, 10);
    enqueueRear(&dq, 20);
    enqueueRear(&dq, 30);

    ASSERT_TRUE(peekRear(dq) == 30, "Peek rear failed");
    ASSERT_TRUE(length(dq) == 3, "Length incorrect");

    int val = dequeueRear(&dq);
    ASSERT_TRUE(val == 30, "Dequeue rear incorrect");

    val = dequeueRear(&dq);
    ASSERT_TRUE(val == 20, "Dequeue rear incorrect");

    val = dequeueRear(&dq);
    ASSERT_TRUE(val == 10, "Dequeue rear incorrect");

    ASSERT_TRUE(isEmpty(dq), "Deque should be empty");

    destroy(&dq);
    TEST_PASSED("Enqueue and Dequeue Rear");
}

void test_interleaved_operations()
{
    TEST_START("Interleaved Operations");
    Deque dq = init(7);

    enqueueRear(&dq, 1);
    enqueueFront(&dq, 2);
    enqueueRear(&dq, 3);
    enqueueFront(&dq, 4);

    ASSERT_TRUE(length(dq) == 4, "Length incorrect");
    ASSERT_TRUE(peekFront(dq) == 4, "Front incorrect");
    ASSERT_TRUE(peekRear(dq) == 3, "Rear incorrect");

    ASSERT_TRUE(dequeueFront(&dq) == 4, "Incorrect dequeueFront");
    ASSERT_TRUE(dequeueRear(&dq) == 3, "Incorrect dequeueRear");

    ASSERT_TRUE(peekFront(dq) == 2, "Front incorrect after operations");
    ASSERT_TRUE(peekRear(dq) == 1, "Rear incorrect after operations");

    destroy(&dq);
    TEST_PASSED("Interleaved Operations");
}

void test_copy_function()
{
    TEST_START("Copy Function");
    Deque original = init(10);

    enqueueRear(&original, 10);
    enqueueFront(&original, 5);
    enqueueRear(&original, 20);

    Deque copied = copy(original);

    ASSERT_TRUE(copied.capacity == original.capacity, "Copied capacity mismatch");
    ASSERT_TRUE(length(copied) == length(original), "Copied length mismatch");
    ASSERT_TRUE(copied.array != original.array, "Copied array points to same memory");

    int i = original.front;
    int j = copied.front;

    while (i != original.rear)
    {
        ASSERT_TRUE(original.array[i] == copied.array[j], "Copied data mismatch");
        i = (i + 1) % original.capacity;
        j = (j + 1) % copied.capacity;
    }

    destroy(&original);
    destroy(&copied);
    TEST_PASSED("Copy Function");
}

void test_clear_function()
{
    TEST_START("Clear Function");
    Deque dq = init(8);

    enqueueRear(&dq, 1);
    enqueueFront(&dq, 2);
    enqueueRear(&dq, 3);

    ASSERT_TRUE(length(dq) == 3, "Length incorrect before clear");

    clear(&dq);

    ASSERT_TRUE(isEmpty(dq), "Deque not empty after clear");
    ASSERT_TRUE(length(dq) == 0, "Length not zero after clear");
    ASSERT_TRUE(dq.front == 0, "Front not reset correctly");
    ASSERT_TRUE(dq.rear == 0, "Rear not reset correctly");

    enqueueFront(&dq, 100);
    enqueueRear(&dq, 200);

    ASSERT_TRUE(peekFront(dq) == 100, "Front incorrect after reinsert");
    ASSERT_TRUE(peekRear(dq) == 200, "Rear incorrect after reinsert");

    destroy(&dq);
    TEST_PASSED("Clear Function");
}

int main()
{
    printf("Starting Deque ADT Test Suite...\n");

    test_init_destroy();
    test_empty_full_checks();
    test_enqueue_dequeue_front();
    test_enqueue_dequeue_rear();
    test_interleaved_operations();
    test_copy_function();
    test_clear_function();

    printf("\nAll Deque ADT Tests Completed.\n");
    return 0;
}
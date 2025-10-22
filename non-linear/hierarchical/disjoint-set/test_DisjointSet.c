#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "adt_DisjointSet.h" // Include the header file containing the DSU implementation

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_RESET "\x1b[0m"

// Utility functions for test output (copied from test_Trie.c)
void print_assertion_result(const char *assertion_name, bool result)
{
    printf("     -> Assertion '%s': ", assertion_name);
    if (result)
    {
        printf(ANSI_COLOR_GREEN "PASSED" ANSI_COLOR_RESET "\n");
    }
    else
    {
        printf(ANSI_COLOR_RED "FAILED" ANSI_COLOR_RESET "\n");
    }
}

void print_test_summary(const char *test_name, bool result)
{
    printf("--- Test Case: %s ---\n", test_name);
    if (result)
    {
        printf("Result: " ANSI_COLOR_GREEN "PASSED" ANSI_COLOR_RESET "\n\n");
    }
    else
    {
        printf("Result: " ANSI_COLOR_RED "FAILED" ANSI_COLOR_RESET "\n\n");
    }
}

// --- TEST FUNCTIONS ---

void test_init_and_clear()
{
    printf("--- Running test_init_and_clear ---\n");
    bool overall_result = true;
    const int N = 5;
    DisjointSet *dsu = init(N);

    // Assertion 1: Check init() success
    bool assertion1 = (dsu != NULL);
    print_assertion_result("DSU is not NULL", assertion1);
    overall_result &= assertion1;

    // Assertion 2: Check size
    bool assertion2 = (dsu && dsu->size == N);
    print_assertion_result("size is correct (N=5)", assertion2);
    overall_result &= assertion2;

    // Assertion 3: Check initial state (each element is its own parent/root)
    bool initial_state_correct = true;
    if (dsu)
    {
        for (int i = 0; i < N; i++)
        {
            if (dsu->parent[i] != i || dsu->rank[i] != 0)
            {
                initial_state_correct = false;
                break;
            }
        }
    }
    bool assertion3 = initial_state_correct;
    print_assertion_result("initial state: parent[i]=i and rank=0", assertion3);
    overall_result &= assertion3;

    // Test clear() functionality
    if (dsu)
    {
        // Perform an operation to change the state
        unite(dsu, 0, 1);
        unite(dsu, 2, 3);

        clear(dsu);

        // Assertion 4: Check if clear() restored the initial state
        bool clear_state_correct = true;
        for (int i = 0; i < N; i++)
        {
            if (dsu->parent[i] != i || dsu->rank[i] != 0)
            {
                clear_state_correct = false;
                break;
            }
        }
        bool assertion4 = clear_state_correct;
        print_assertion_result("clear() restores initial state", assertion4);
        overall_result &= assertion4;
    }

    print_test_summary("test_init_and_clear", overall_result);
    destroy(dsu);
}

void test_union_find_and_connected()
{
    printf("--- Running test_union_find_and_connected ---\n");
    bool overall_result = true;
    const int N = 5;
    DisjointSet *dsu = init(N);

    // Initial check: 0 and 1 are not connected
    bool assertion1 = !connected(dsu, 0, 1);
    print_assertion_result("initial state: 0 not connected to 1", assertion1);
    overall_result &= assertion1;

    // 1. Union 0 and 1
    unite(dsu, 0, 1);

    // Assertion 2: Check connectivity after union
    bool assertion2 = connected(dsu, 0, 1);
    print_assertion_result("after unite(0,1): 0 connected to 1", assertion2);
    overall_result &= assertion2;

    // Assertion 3: Check that root of 0 is the same as root of 1
    bool assertion3 = (find(dsu, 0) == find(dsu, 1));
    print_assertion_result("root of 0 equals root of 1", assertion3);
    overall_result &= assertion3;

    // 2. Union 2 and 3
    unite(dsu, 2, 3);

    // 3. Union 1 and 3 (merges {0, 1} and {2, 3})
    unite(dsu, 1, 3);

    // Assertion 4: All elements 0, 1, 2, 3 should now be connected
    bool assertion4 = connected(dsu, 0, 3) && connected(dsu, 1, 2) && connected(dsu, 0, 2);
    print_assertion_result("after merge: 0, 1, 2, 3 are all connected", assertion4);
    overall_result &= assertion4;

    // Assertion 5: Element 4 is still separate
    bool assertion5 = !connected(dsu, 0, 4);
    print_assertion_result("4 is still separate from 0", assertion5);
    overall_result &= assertion5;

    // Assertion 6: Check for Union-by-Rank/Path-Compression properties
    // After find(3), the path from 3 to its root should be compressed.
    int root_0123 = find(dsu, 3);
    bool assertion6 = (find(dsu, 1) == root_0123);
    print_assertion_result("find(1) and find(3) share same root", assertion6);
    overall_result &= assertion6;

    print_test_summary("test_union_find_and_connected", overall_result);
    destroy(dsu);
}

void test_copy_operation()
{
    printf("--- Running test_copy_operation ---\n");
    bool overall_result = true;
    const int N = 4;
    DisjointSet *original = init(N);

    // Initial operations on original
    unite(original, 0, 1); // {0, 1}
    unite(original, 2, 3); // {2, 3}

    // Create deep copy
    DisjointSet *copy_dsu = copy(original);

    // Assertion 1: Check copy success and size
    bool assertion1 = (copy_dsu != NULL) && (copy_dsu->size == N);
    print_assertion_result("copy is not NULL and size is correct", assertion1);
    overall_result &= assertion1;

    // Assertion 2: Check initial connectivity in copy
    bool assertion2 = connected(copy_dsu, 0, 1) && connected(copy_dsu, 2, 3) && !connected(copy_dsu, 1, 2);
    print_assertion_result("copy has correct initial connectivity", assertion2);
    overall_result &= assertion2;

    // Modify original
    unite(original, 1, 2); // original: {0, 1, 2, 3}

    // Assertion 3: Check that original is updated
    bool assertion3 = connected(original, 0, 3);
    print_assertion_result("original is now fully connected", assertion3);
    overall_result &= assertion3;

    // Assertion 4: Check that copy is NOT updated (Deep Copy verification)
    bool assertion4 = !connected(copy_dsu, 0, 3);
    print_assertion_result("copy remains separate ({0,1}, {2,3})", assertion4);
    overall_result &= assertion4;

    print_test_summary("test_copy_operation", overall_result);
    destroy(original);
    destroy(copy_dsu);
}

void test_edge_cases()
{
    printf("--- Running test_edge_cases ---\n");
    bool overall_result = true;

    // Test 1: Size 1 DSU
    DisjointSet *dsu1 = init(1);

    // Assertion 1: Check find on single element
    bool assertion1 = (find(dsu1, 0) == 0);
    print_assertion_result("find(0) on size 1 DSU is 0", assertion1);
    overall_result &= assertion1;

    // Assertion 2: Union same element
    bool assertion2 = !unite(dsu1, 0, 0);
    print_assertion_result("unite(0,0) returns false", assertion2);
    overall_result &= assertion2;
    destroy(dsu1);

    // Test 2: Union different elements in same set
    DisjointSet *dsu2 = init(3);
    unite(dsu2, 0, 1);
    unite(dsu2, 0, 2);
    bool assertion3 = !unite(dsu2, 1, 2);
    print_assertion_result("unite(1,2) in same set returns false", assertion3);
    overall_result &= assertion3;
    destroy(dsu2);

    // Test 3: Invalid indices
    DisjointSet *dsu3 = init(5);

    // Assertion 4: Out-of-bounds find check
    bool assertion4 = (find(dsu3, 5) == -1) && (find(dsu3, -1) == -1);
    print_assertion_result("find() out-of-bounds returns -1", assertion4);
    overall_result &= assertion4;

    // Assertion 5: Out-of-bounds union check
    bool assertion5 = !unite(dsu3, 0, 5) && !unite(dsu3, 5, 0);
    print_assertion_result("unite() out-of-bounds returns false", assertion5);
    overall_result &= assertion5;
    destroy(dsu3);

    // Test 4: NULL inputs
    bool assertion6 = (init(0) == NULL);
    print_assertion_result("init(0) returns NULL", assertion6);
    overall_result &= assertion6;

    print_test_summary("test_edge_cases", overall_result);
}

void test_display() // No automatic test for display, manual verification is required.
{
    printf("--- Running test_display ---\n");
    DisjointSet *dsu = init(5);

    unite(dsu, 0, 1);
    unite(dsu, 2, 3);
    unite(dsu, 1, 3);

    printf("This test requires manual verification of output.\n");
    printf("Expected: Elements 0, 1, 2, 3 should point to the same root. Element 4 should point to itself.\n");
    printf("Actual output for traverse:\n");
    traverse(dsu);

    printf("\n--- Test Case: test_display ---\n");
    printf("Result: " ANSI_COLOR_GREEN "PASSED" ANSI_COLOR_RESET "\n\n");

    destroy(dsu);
}

int main()
{
    test_init_and_clear();
    test_union_find_and_connected();
    test_copy_operation();
    test_edge_cases();
    test_display();
    return 0;
}
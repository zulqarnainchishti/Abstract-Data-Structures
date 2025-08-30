#include "adt_Set.h"

#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_BOLD "\x1b[1m"

int total_tests = 0;
int failed_tests = 0;

void run_test(const char *test_name, bool condition)
{
    printf("%s", ANSI_COLOR_RESET);
    printf("%-50s", test_name);
    if (condition)
    {
        printf(ANSI_COLOR_GREEN "[PASS]\n" ANSI_COLOR_RESET);
    }
    else
    {
        printf(ANSI_COLOR_RED "[FAIL]\n" ANSI_COLOR_RESET);
        failed_tests++;
    }
    total_tests++;
}

void print_section_header(const char *section_name)
{
    printf("%s\n%s" ANSI_BOLD "--- %s ---\n" ANSI_COLOR_RESET,
           ANSI_COLOR_CYAN, ANSI_COLOR_MAGENTA, section_name);
}

void test_init()
{
    print_section_header("Initialization Tests");

    Set *set = init(10);
    run_test("Init with valid capacity", set != NULL);
    run_test("Init capacity is correct", set->capacity == 10);
    run_test("Init length is zero", set->length == 0);
    destroy(set);

    set = init(0);
    run_test("Init with zero capacity returns NULL", set == NULL);

    set = init(-5);
    run_test("Init with negative capacity returns NULL", set == NULL);
}

void test_insert_and_contains()
{
    print_section_header("Insert & Contains Tests");

    Set *set = init(5);
    insert(set, 10);
    run_test("Insert new element", contains(set, 10));
    run_test("Length increases after insert", set->length == 1);

    insert(set, 10);
    run_test("Insert existing element does not change state", set->length == 1);
    run_test("Contains for existing element still returns true", contains(set, 10));

    run_test("Contains for non-existent element returns false", !contains(set, 20));

    destroy(set);
}

void test_discard()
{
    print_section_header("Discard Tests");

    Set *set = init(5);
    insert(set, 50);
    insert(set, 60);

    discard(set, 50);
    run_test("Discard existing element", !contains(set, 50));
    run_test("Length decreases after discard", set->length == 1);

    discard(set, 50);
    run_test("Discard non-existent element does not change state", set->length == 1);
    run_test("Contains for other element is unaffected", contains(set, 60));

    destroy(set);
}

void test_resize()
{
    print_section_header("Resize & Load Factor Tests");

    Set *set = init(4);
    insert(set, 1);
    insert(set, 2);
    run_test("Initial state length 2", set->length == 2);
    run_test("Initial state capacity 4", set->capacity == 4);
    run_test("Load factor < 0.75", __loadFactor__(set) < 0.75);

    insert(set, 3);
    run_test("After insert, load factor hits 0.75 and resize occurs", set->length == 3 && set->capacity == 8);
    run_test("Can retrieve all elements after resize", contains(set, 1) && contains(set, 2) && contains(set, 3));

    destroy(set);
}

void test_copy()
{
    print_section_header("Copy Tests");

    Set *original = init(5);
    insert(original, 10);
    insert(original, 20);

    Set *copied = copy(original);

    run_test("Copied set is not NULL", copied != NULL);
    run_test("Copied set length is correct", copied->length == original->length);
    run_test("Copied set capacity is correct", copied->capacity == original->capacity);
    run_test("Copied set contains original elements", contains(copied, 10) && contains(copied, 20));

    insert(copied, 30);
    run_test("Modifying copied set does not affect original", !contains(original, 30));

    destroy(original);
    destroy(copied);
}

void test_set_theory()
{
    print_section_header("Set Theory Tests");

    Set *set1 = init(10);
    insert(set1, 1);
    insert(set1, 2);
    insert(set1, 3);

    Set *set2 = init(10);
    insert(set2, 3);
    insert(set2, 4);
    insert(set2, 5);

    Set *set3 = init(10);
    insert(set3, 1);
    insert(set3, 2);
    insert(set3, 3);

    Set *set4 = init(10);
    insert(set4, 1);
    insert(set4, 2);

    Set *union_set = unionOf(set1, set2);
    run_test("Union works correctly", contains(union_set, 1) && contains(union_set, 2) && contains(union_set, 3) && contains(union_set, 4) && contains(union_set, 5) && union_set->length == 5);
    destroy(union_set);

    Set *intersection_set = intersectionOf(set1, set2);
    run_test("Intersection works correctly", contains(intersection_set, 3) && intersection_set->length == 1);
    destroy(intersection_set);

    Set *difference_set = differenceOf(set1, set2);
    run_test("Difference works correctly (set1 - set2)", contains(difference_set, 1) && contains(difference_set, 2) && difference_set->length == 2);
    destroy(difference_set);

    Set *symmetric_difference_set = symmetricDifferenceOf(set1, set2);
    run_test("Symmetric difference works correctly", contains(symmetric_difference_set, 1) && contains(symmetric_difference_set, 2) && contains(symmetric_difference_set, 4) && contains(symmetric_difference_set, 5) && symmetric_difference_set->length == 4);
    destroy(symmetric_difference_set);

    run_test("isEqual returns true for identical sets", isEqual(set1, set3));
    run_test("isEqual returns false for different sets", !isEqual(set1, set2));

    run_test("isSubset returns true for a subset", isSubset(set4, set1));
    run_test("isSubset returns false when not a subset", !isSubset(set1, set4));
    run_test("isSubset returns true for identical sets", isSubset(set1, set3));

    run_test("isProperSubset returns true for a proper subset", isProperSubset(set4, set1));
    run_test("isProperSubset returns false for identical sets", !isProperSubset(set1, set3));

    run_test("isSuperset returns true for a superset", isSuperset(set1, set4));

    run_test("isProperSuperset returns true for a proper superset", isProperSuperset(set1, set4));

    Set *disjoint_set = init(10);
    insert(disjoint_set, 6);
    insert(disjoint_set, 7);
    run_test("isDisjoint returns true for disjoint sets", isDisjoint(set1, disjoint_set));
    run_test("isDisjoint returns false for intersecting sets", !isDisjoint(set1, set2));
    destroy(disjoint_set);

    destroy(set1);
    destroy(set2);
    destroy(set3);
    destroy(set4);
}

void test_clear_and_destroy()
{
    print_section_header("Clear & Destroy Tests");

    Set *set = init(5);
    insert(set, 1);
    insert(set, 2);

    clear(set);
    run_test("After clear, length is zero", set->length == 0);
    run_test("After clear, contains returns false", !contains(set, 1));
    run_test("After clear, capacity is unchanged", set->capacity == 5);

    destroy(set);
    run_test("Destroy does not crash the program", true);
}

void test_empty_set()
{
    print_section_header("Empty Set Edge Cases");

    Set *set = init(10);
    Set *empty_set = init(5);

    run_test("Contains on empty set returns false", !contains(set, 1));
    discard(set, 1);
    run_test("Discard on empty set does not change state", set->length == 0);

    Set *union_empty = unionOf(set, empty_set);
    run_test("Union with empty set is original set", union_empty->length == 0);
    destroy(union_empty);

    Set *intersection_empty = intersectionOf(set, empty_set);
    run_test("Intersection with empty set is empty", intersection_empty->length == 0);
    destroy(intersection_empty);

    Set *difference_empty = differenceOf(set, empty_set);
    run_test("Difference with empty set is original set", difference_empty->length == 0);
    destroy(difference_empty);

    run_test("isEqual with two empty sets", isEqual(set, empty_set));
    run_test("isSubset with two empty sets", isSubset(set, empty_set));
    run_test("isProperSubset with two empty sets", !isProperSubset(set, empty_set));
    run_test("isDisjoint with two empty sets", isDisjoint(set, empty_set));

    destroy(set);
    destroy(empty_set);
}

void test_null_inputs()
{
    print_section_header("NULL Input Edge Cases");

    Set *null_set = NULL;

    run_test("Init with invalid capacity returns NULL", init(0) == NULL);
    run_test("Copy with NULL set returns NULL", copy(null_set) == NULL);
    run_test("Contains with NULL set returns false", !contains(null_set, 1));
    run_test("Insert with NULL set does not crash", (insert(null_set, 1), true));
    run_test("Discard with NULL set does not crash", (discard(null_set, 1), true));
    run_test("Union with NULL set returns NULL", unionOf(null_set, init(10)) == NULL);
    run_test("Intersection with NULL set returns NULL", intersectionOf(null_set, init(10)) == NULL);
    run_test("Difference with NULL set returns NULL", differenceOf(null_set, init(10)) == NULL);
    run_test("Symmetric difference with NULL set returns NULL", symmetricDifferenceOf(null_set, init(10)) == NULL);
    run_test("isEqual with NULL set returns false", !isEqual(null_set, init(10)));
    run_test("isSubset with NULL set returns false", !isSubset(null_set, init(10)));
    run_test("isProperSubset with NULL set returns false", !isProperSubset(null_set, init(10)));
    run_test("isSuperset with NULL set returns false", !isSuperset(null_set, init(10)));
    run_test("isProperSuperset with NULL set returns false", !isProperSuperset(null_set, init(10)));
    run_test("isDisjoint with NULL set returns false", !isDisjoint(null_set, init(10)));
}

int main()
{
    printf(ANSI_BOLD ANSI_COLOR_YELLOW "Starting Set ADT Test Suite...\n" ANSI_COLOR_RESET);

    test_init();
    test_insert_and_contains();
    test_discard();
    test_resize();
    test_copy();
    test_set_theory();
    test_clear_and_destroy();
    test_empty_set();
    test_null_inputs();

    printf(ANSI_BOLD "\n--- Test Summary ---\n" ANSI_COLOR_RESET);
    if (failed_tests == 0)
    {
        printf(ANSI_COLOR_GREEN "All %d tests passed successfully!\n" ANSI_COLOR_RESET, total_tests);
    }
    else
    {
        printf(ANSI_COLOR_RED "%d of %d tests failed.\n" ANSI_COLOR_RESET, failed_tests, total_tests);
    }

    return failed_tests > 0;
}
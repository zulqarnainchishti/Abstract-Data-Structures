#include "adt_Map.h"

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

    Map *map = init(10);
    run_test("Init with valid capacity", map != NULL);
    run_test("Init capacity is correct", map->capacity == 10);
    run_test("Init length is zero", map->length == 0);
    destroy(map);

    map = init(0);
    run_test("Init with zero capacity returns NULL", map == NULL);

    map = init(-5);
    run_test("Init with negative capacity returns NULL", map == NULL);
}

void test_put_and_get()
{
    print_section_header("Put & Get Tests");

    Map *map = init(5);
    put(map, "test_key_1", 100);
    run_test("Put new key", contains(map, "test_key_1"));
    run_test("Get existing key", get(map, "test_key_1") == 100);
    run_test("Length increases after put", map->length == 1);

    put(map, "test_key_1", 200);
    run_test("Update existing key's value", get(map, "test_key_1") == 200);
    run_test("Length does not increase on update", map->length == 1);

    run_test("Get non-existent key returns -1", get(map, "non_existent") == -1);

    destroy(map);
}

void test_collisions()
{
    print_section_header("Collision Handling Tests");

    Map *map = init(2);
    put(map, "A", 1);
    put(map, "C", 3);
    put(map, "E", 5);

    run_test("Put with multiple keys that might collide", map->length == 3);
    run_test("Retrieve first collided key", get(map, "A") == 1);
    run_test("Retrieve second collided key", get(map, "C") == 3);
    run_test("Retrieve third collided key", get(map, "E") == 5);

    destroy(map);
}

void test_resize()
{
    print_section_header("Resize & Load Factor Tests");

    Map *map = init(4);
    put(map, "a", 1);
    put(map, "b", 2);
    run_test("Initial state length 2", map->length == 2);
    run_test("Initial state capacity 4", map->capacity == 4);
    run_test("Load factor < 0.75", __loadFactor__(map) < 0.75);

    put(map, "c", 3);
    run_test("After put, load factor hits 0.75 and resize occurs", map->length == 3 && map->capacity == 8);
    run_test("Can retrieve all keys after resize", get(map, "a") == 1 && get(map, "b") == 2 && get(map, "c") == 3);

    destroy(map);
}

void test_pop()
{
    print_section_header("Pop Tests");

    Map *map = init(5);
    put(map, "key_to_pop", 99);
    put(map, "another_key", 11);

    int popped_value = pop(map, "key_to_pop");
    run_test("Pop returns correct value", popped_value == 99);
    run_test("Popped key is no longer in map", !contains(map, "key_to_pop"));
    run_test("Length decreases after pop", map->length == 1);
    run_test("Other keys are unaffected after pop", get(map, "another_key") == 11);

    popped_value = pop(map, "non_existent");
    run_test("Pop on non-existent key returns -1", popped_value == -1);
    run_test("Length does not decrease when key not found", map->length == 1);

    destroy(map);
}

void test_copy()
{
    print_section_header("Copy Tests");

    Map *original = init(5);
    put(original, "key1", 1);
    put(original, "key2", 2);

    Map *copied = copy(original);

    run_test("Copied map is not NULL", copied != NULL);
    run_test("Copied map length is correct", copied->length == original->length);
    run_test("Copied map capacity is correct", copied->capacity == original->capacity);
    run_test("Copied map contains original keys", contains(copied, "key1") && contains(copied, "key2"));

    put(copied, "key3", 3);
    run_test("Modifying copied map does not affect original", !contains(original, "key3"));

    Entry *orig_entry = original->buckets[__hashFunction__("key1", original->capacity)];
    Entry *copied_entry = copied->buckets[__hashFunction__("key1", copied->capacity)];
    run_test("Key pointers are different (deep copy)", orig_entry->key != copied_entry->key);

    destroy(original);
    destroy(copied);
}

void test_clear_and_destroy()
{
    print_section_header("Clear & Destroy Tests");

    Map *map = init(5);
    put(map, "a", 1);
    put(map, "b", 2);

    clear(map);
    run_test("After clear, length is zero", map->length == 0);
    run_test("After clear, contains returns false", !contains(map, "a"));

    destroy(map);
    run_test("Destroy does not crash the program", true);
}

void test_items()
{
    print_section_header("Items Function Tests");

    Map *map = init(5);
    put(map, "test1", 1);
    put(map, "test2", 2);
    put(map, "test3", 3);

    Entry *item_list = items(map);
    run_test("Items function returns a non-NULL pointer", item_list != NULL);

    int count = 0;
    for (int i = 0; i < map->length; i++)
    {
        if (strcmp(item_list[i].key, "test1") == 0)
            count++;
        if (strcmp(item_list[i].key, "test2") == 0)
            count++;
        if (strcmp(item_list[i].key, "test3") == 0)
            count++;
    }
    run_test("Items function returns all items", count == 3);

    for (int i = 0; i < map->length; i++)
    {
        free(item_list[i].key);
    }
    free(item_list);

    destroy(map);
}

void test_empty_map()
{
    print_section_header("Empty Table Edge Cases");

    Map *map = init(10);
    run_test("Get on empty map returns -1", get(map, "any_key") == -1);
    run_test("Pop on empty map returns -1", pop(map, "any_key") == -1);
    run_test("Contains on empty map returns false", !contains(map, "any_key"));
    run_test("Items on empty map returns NULL", items(map) == NULL);

    destroy(map);
}

void test_null_inputs()
{
    print_section_header("NULL Input Edge Cases");

    Map *null_map = NULL;

    run_test("Init with invalid capacity returns NULL", init(0) == NULL);
    run_test("Copy with NULL map returns NULL", copy(null_map) == NULL);
    run_test("Get with NULL map returns -1", get(null_map, "key") == -1);
    run_test("Put with NULL map does not crash", (put(null_map, "key", 1), true));
    run_test("Pop with NULL map returns -1", pop(null_map, "key") == -1);
    run_test("Contains with NULL map returns false", !contains(null_map, "key"));
    run_test("Items with NULL map returns NULL", items(null_map) == NULL);
}

int main()
{
    printf(ANSI_BOLD ANSI_COLOR_YELLOW "Starting Map ADT Test Suite...\n" ANSI_COLOR_RESET);

    test_init();
    test_put_and_get();
    test_collisions();
    test_resize();
    test_pop();
    test_copy();
    test_items();
    test_clear_and_destroy();
    test_empty_map();
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
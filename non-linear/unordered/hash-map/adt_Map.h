#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * @struct Entry
 * @brief Represents a single key-value pair and a pointer to the next entry in a chain.
 */
typedef struct Entry
{
    char *key;          /**< The string key. */
    int value;          /**< The integer value associated with the key. */
    struct Entry *next; /**< Pointer to the next entry in the same bucket (collision chain). */
} Entry;

/**
 * @struct Map
 * @brief Represents the map data structure.
 */
typedef struct
{
    Entry **buckets; /**< A pointer to the array of map buckets. */
    int length;      /**< The number of key-value pairs currently in the map. */
    int capacity;    /**< The total number of buckets in the map. */
} Map;

/**
 * @brief Initializes a new map with a given capacity.
 * @param capacity The initial capacity of the map. Must be greater than 0.
 * @return A pointer to the newly created Map, or NULL if allocation fails or capacity is invalid.
 */
Map *init(const int capacity)
{
    if (capacity <= 0)
        return NULL;
    Map *table = (Map *)malloc(sizeof(Map));
    if (table == NULL)
        return NULL;
    table->buckets = (Entry **)calloc(capacity, sizeof(Entry *));
    if (table->buckets == NULL)
    {
        free(table);
        return NULL;
    }
    table->length = 0;
    table->capacity = capacity;
    return table;
}

/**
 * @brief Creates a deep copy of an existing map.
 * @param table A pointer to the map to copy.
 * @return A pointer to the new, copied Map, or NULL if the original table is NULL or allocation fails.
 */
Map *copy(const Map *table)
{
    if (table == NULL)
        return NULL;
    Map *copied = init(table->capacity);
    if (copied == NULL)
        return NULL;
    for (int i = 0; i < table->capacity; i++)
    {
        Entry *src = table->buckets[i];
        Entry *dst = copied->buckets[i];
        while (src != NULL)
        {
            Entry *entry = (Entry *)malloc(sizeof(Entry));
            if (entry == NULL)
                return NULL;
            entry->key = strdup(src->key);
            entry->value = src->value;
            entry->next = NULL;
            if (dst == NULL)
                copied->buckets[i] = entry;
            else
                dst->next = entry;
            dst = entry;
            src = src->next;
        }
    }
    copied->length = table->length;
    copied->capacity = table->capacity;
    return copied;
}

/**
 * @brief Removes all key-value pairs from the map, but does not deallocate the table itself.
 * @param table A pointer to the Map to clear.
 */
void clear(Map *table)
{
    if (table == NULL)
        return;
    Entry *curr, *next;
    for (int i = 0; i < table->capacity; i++)
    {
        curr = table->buckets[i];
        while (curr != NULL)
        {
            next = curr->next;
            free(curr->key);
            free(curr);
            curr = next;
        }
        table->buckets[i] = NULL;
    }
    table->length = 0;
}

/**
 * @brief Destroys and deallocates the map and all its contents.
 * @param table A pointer to the Map to destroy.
 */
void destroy(Map *table)
{
    if (table == NULL)
        return;
    Entry *curr, *next;
    for (int i = 0; i < table->capacity; i++)
    {
        curr = table->buckets[i];
        while (curr != NULL)
        {
            next = curr->next;
            free(curr->key);
            free(curr);
            curr = next;
        }
        table->buckets[i] = NULL;
    }
    free(table->buckets);
    free(table);
}

/**
 * @brief Hash function using the djb2 algorithm for string keys.
 * @param key The string key to hash.
 * @param capacity The capacity of the map.
 * @return The hash index within the range [0, capacity-1].
 */
// int __hashFunction__(const char *key, const int capacity)
// {
//     // djb2 algorithm
//     unsigned long hash = 5381;
//     // magic constant chosen empirically for good distribution
//     while (*key)
//         hash = (hash << 5) + hash + *key++;
//     // hash = hash * 33 + current character
//     int index = hash % capacity;
//     // index in [0, capacity-1]
//     return index;
// }

/**
 * @brief Hash function using the FNV-1a algorithm for string keys.
 * @param key The string key to hash.
 * @param capacity The capacity of the map.
 * @return The hash index within the range [0, capacity-1].
 */
int __hashFunction__(const char *key, const int capacity)
{
    // FNV-1a algorithm
    unsigned long hash = 2166136261u;
    // FNV 32-bit offset basis, 'u' enforces unsigned arithmetic with defined modular overflow (wrap-around modulo 2^32)
    while (*key)
    {
        hash ^= (unsigned char)(*key++);
        // cast enforces unsigned 8-bit interpretation (0–255)
        hash *= 16777619u;
        // FNV 32-bit prime, unsigned multiplication with well-defined modular overflow (mod 2^32)
    }
    int index = hash % capacity;
    // index in [0, capacity-1]
    return index;
}

/**
 * @brief Calculates the load factor of the map.
 * @param table A pointer to the Map.
 * @return The load factor as a double.
 */
double __loadFactor__(const Map *table)
{
    return (double)table->length / table->capacity;
}

/**
 * @brief Resizes the map when the load factor is too high.
 * @param table A pointer to the Map.
 */
void __resize__(Map *table)
{
    if (__loadFactor__(table) < 0.75)
        return;
    int newCapacity = table->capacity * 2;
    Entry **newBuckets = (Entry **)calloc(newCapacity, sizeof(Entry *));
    if (newBuckets == NULL)
        return;
    for (int i = 0; i < table->capacity; i++)
    {
        Entry *curr = table->buckets[i];
        while (curr != NULL)
        {
            Entry *next = curr->next;
            int index = __hashFunction__(curr->key, newCapacity);
            curr->next = newBuckets[index];
            newBuckets[index] = curr;
            curr = next;
        }
    }
    free(table->buckets);
    table->buckets = newBuckets;
    table->capacity = newCapacity;
}

/**
 * @brief Inserts or updates a key-value pair in the map.
 * @param table A pointer to the Map.
 * @param key The string key.
 * @param value The integer value.
 * @note If the key already exists, its value is updated. The table will resize automatically if the load factor exceeds 75%.
 */
void put(Map *table, const char *key, const int value)
{
    if (table == NULL || key == NULL)
        return;
    int index = __hashFunction__(key, table->capacity);
    Entry *curr = table->buckets[index];
    while (curr != NULL)
    {
        if (strcmp(curr->key, key) == 0)
        {
            curr->value = value;
            return;
        }
        curr = curr->next;
    }
    Entry *newEntry = (Entry *)malloc(sizeof(Entry));
    if (newEntry == NULL)
        return;
    newEntry->key = strdup(key);
    newEntry->value = value;
    newEntry->next = table->buckets[index];
    table->buckets[index] = newEntry;
    table->length++;
    __resize__(table);
}

/**
 * @brief Removes a key-value pair from the map and returns its value.
 * @param table A pointer to the Map.
 * @param key The string key of the entry to remove.
 * @return The integer value of the removed entry, or -1 if the key is not found.
 */
int pop(Map *table, const char *key)
{
    if (table == NULL || key == NULL)
        return -1;
    int index = __hashFunction__(key, table->capacity);
    Entry *prev = NULL;
    Entry *curr = table->buckets[index];
    while (curr != NULL)
    {
        if (strcmp(curr->key, key) == 0)
        {
            if (prev == NULL)
                table->buckets[index] = curr->next;
            else
                prev->next = curr->next;
            int value = curr->value;
            free(curr->key);
            free(curr);
            table->length--;
            return value;
        }
        prev = curr;
        curr = curr->next;
    }
    return -1;
}

/**
 * @brief Retrieves the value associated with a given key.
 * @param table A pointer to the Map.
 * @param key The string key to look for.
 * @return The integer value associated with the key, or -1 if the key is not found.
 */
int get(const Map *table, const char *key)
{
    if (table == NULL || key == NULL)
        return -1;
    int index = __hashFunction__(key, table->capacity);
    Entry *curr = table->buckets[index];
    while (curr != NULL)
    {
        if (strcmp(curr->key, key) == 0)
            return curr->value;
        curr = curr->next;
    }
    return -1;
}

/**
 * @brief Checks if a key is present in the map.
 * @param table A pointer to the Map.
 * @param key The string key to search for.
 * @return true if the key is in the table, false otherwise.
 */
bool contains(const Map *table, const char *key)
{
    if (table == NULL || key == NULL)
        return false;
    int index = __hashFunction__(key, table->capacity);
    Entry *curr = table->buckets[index];
    while (curr != NULL)
    {
        if (strcmp(curr->key, key) == 0)
            return true;
        curr = curr->next;
    }
    return false;
}

/**
 * @brief Retrieves all key-value pairs as a dynamically allocated array.
 * @param table A pointer to the Map.
 * @return A dynamically allocated array of Entry structs, or NULL if the table is empty or allocation fails. The caller is responsible for freeing this memory.
 */
Entry *items(const Map *table)
{
    if (table == NULL || table->length == 0)
        return NULL;
    Entry *itemList = (Entry *)malloc(table->length * sizeof(Entry));
    if (itemList == NULL)
        return NULL;
    int count = 0;
    Entry *curr;
    for (int i = 0; i < table->capacity; i++)
    {
        curr = table->buckets[i];
        while (curr != NULL)
        {
            itemList[count].key = strdup(curr->key);
            itemList[count].value = curr->value;
            itemList[count].next = NULL;
            count++;
            curr = curr->next;
        }
    }
    return itemList;
}

/**
 * @brief Prints all key-value pairs to the console.
 * @param table A pointer to the Map.
 */
void traverse(const Map *table)
{
    if (table == NULL)
        return;
    printf("{ ");
    for (int i = 0; i < table->capacity; i++)
    {
        Entry *curr = table->buckets[i];
        while (curr != NULL)
        {
            printf("%s:%d ", curr->key, curr->value);
            curr = curr->next;
        }
    }
    printf("} : %.2f\n", __loadFactor__(table));
}

/**
 * @brief Displays the internal structure of the map for debugging purposes.
 * @param table A pointer to the Map.
 */
void describe(const Map *table)
{
    if (table == NULL)
        return;
    Entry *curr;
    for (int i = 0; i < table->capacity; i++)
    {
        printf("%2d | ", i);
        curr = table->buckets[i];
        while (curr != NULL)
        {
            printf("{%s,%d}", curr->key, curr->value);
            curr = curr->next;
            if (curr != NULL)
                printf(" -> ");
        }
        printf("\n");
    }
}

#endif // MAP_H
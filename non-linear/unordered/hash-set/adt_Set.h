#ifndef SET_H
#define SET_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

/**
 * @enum Status
 * @brief Represents the state of a bucket in the hash table.
 */
typedef enum
{
    EMPTY,    /**< The bucket is empty. */
    OCCUPIED, /**< The bucket is occupied by an element. */
    DELETED   /**< The bucket was occupied but the element was deleted. */
} Status;

/**
 * @struct Entry
 * @brief Represents a single key and its status in the hash table.
 */
typedef struct
{
    int key;       /**< The integer key stored in the bucket. */
    Status status; /**< The current status of the bucket. */
} Entry;

/**
 * @struct Set
 * @brief Represents the hash set data structure.
 */
typedef struct
{
    Entry *buckets; /**< A pointer to the array of hash table buckets. */
    int length;     /**< The number of elements currently in the set. */
    int capacity;   /**< The total number of buckets in the hash table. */
} Set;

/**
 * @brief Initializes a new hash set with a given capacity.
 * @param capacity The initial capacity of the hash set. Must be greater than 0.
 * @return A pointer to the newly created Set, or NULL if allocation fails or capacity is invalid.
 */
Set *init(const int capacity)
{
    if (capacity <= 0)
        return NULL;
    Set *set = (Set *)malloc(sizeof(Set));
    if (set == NULL)
        return NULL;
    set->buckets = (Entry *)malloc(capacity * sizeof(Entry));
    if (set->buckets == NULL)
    {
        free(set);
        return NULL;
    }
    for (int i = 0; i < capacity; i++)
        set->buckets[i].status = EMPTY;
    set->length = 0;
    set->capacity = capacity;
    return set;
}

/**
 * @brief Creates a deep copy of an existing set.
 * @param set A pointer to the set to copy.
 * @return A pointer to the new, copied Set, or NULL if the original set is NULL.
 */
Set *copy(const Set *set)
{
    if (set == NULL)
        return NULL;
    Set *copied = init(set->capacity);
    for (int i = 0; i < set->capacity; i++)
    {
        copied->buckets[i].status = set->buckets[i].status;
        if (set->buckets[i].status == OCCUPIED)
            copied->buckets[i].key = set->buckets[i].key;
    }
    copied->length = set->length;
    copied->capacity = set->capacity;
    return copied;
}

/**
 * @brief Removes all elements from the set, but does not deallocate the set itself.
 * @param set A pointer to the set to clear.
 */
void clear(Set *set)
{
    if (set == NULL)
        return;
    for (int i = 0; i < set->capacity; i++)
        set->buckets[i].status = EMPTY;
    set->length = 0;
}

/**
 * @brief Destroys and deallocates the set and its internal buckets.
 * @param set A pointer to the set to destroy.
 */
void destroy(Set *set)
{
    if (set == NULL)
        return;
    free(set->buckets);
    free(set);
}

/**
 * @brief Primary hash function using the multiplication method.
 * @param key The integer key to hash.
 * @param capacity The capacity of the hash table.
 * @return The initial hash index within the range [0, capacity-1].
 */
int __hf1__(const int key, const int capacity)
{
    double A = (sqrt(5.0) - 1) / 2.0;
    double frac = fmod(key * A, 1.0);
    return (int)(capacity * frac);
}

/**
 * @brief Secondary hash function for double hashing.
 * @param key The integer key to hash.
 * @param capacity The capacity of the hash table.
 * @return The step size for probing, adjusted to avoid zero [1, capacity-1].
 */
int __hf2__(const int key, const int capacity)
{
    return (key % (capacity - 1)) + 1;
}

/**
 * @brief Unified double hashing probe function.
 * @param key The integer key.
 * @param capacity The capacity of the hash table.
 * @param attempt The current probe attempt number.
 * @return The probed index in the hash table.
 */
int __hashFunction__(const int key, const int capacity, const int attempt)
{
    return (__hf1__(key, capacity) + attempt * __hf2__(key, capacity)) % capacity;
}

/**
 * @brief Calculates the load factor of the set.
 * @param set A pointer to the Set structure.
 * @return The load factor as a double.
 */
double __loadFactor__(const Set *set)
{
    return (double)set->length / set->capacity;
}

/**
 * @brief Resizes the hash set when the load factor is too high.
 * @param set A pointer to the Set structure.
 */
void __resize__(Set *set)
{
    if (__loadFactor__(set) < 0.75)
        return;
    int newCapacity = set->capacity * 2;
    Entry *newBuckets = (Entry *)malloc(newCapacity * sizeof(Entry));
    if (newBuckets == NULL)
        return;
    for (int i = 0; i < newCapacity; i++)
        newBuckets[i].status = EMPTY;
    for (int i = 0; i < set->capacity; i++)
    {
        if (set->buckets[i].status == OCCUPIED)
        {
            int key = set->buckets[i].key;
            for (int j = 0; j < newCapacity; j++)
            {
                int index = __hashFunction__(key, newCapacity, j);
                if (newBuckets[index].status == EMPTY)
                {
                    newBuckets[index].key = key;
                    newBuckets[index].status = OCCUPIED;
                    break;
                }
            }
        }
    }
    free(set->buckets);
    set->buckets = newBuckets;
    set->capacity = newCapacity;
}

/**
 * @brief Inserts a new key into the set.
 * @param set A pointer to the set.
 * @param key The integer key to insert.
 * @note If the key already exists, the function does nothing. The set will resize automatically if the load factor exceeds 75%.
 */
void insert(Set *set, const int key)
{
    if (set == NULL)
        return;
    for (int i = 0; i < set->capacity; i++)
    {
        int index = __hashFunction__(key, set->capacity, i);
        if (set->buckets[index].status == OCCUPIED && set->buckets[index].key == key)
            return;
        if (set->buckets[index].status == EMPTY || set->buckets[index].status == DELETED)
        {
            set->buckets[index].status = OCCUPIED;
            set->buckets[index].key = key;
            set->length++;
            __resize__(set);
            return;
        }
    }
}

/**
 * @brief Removes a key from the set.
 * @param set A pointer to the set.
 * @param key The integer key to discard.
 * @note If the key does not exist, the function does nothing.
 */
void discard(Set *set, const int key)
{
    if (set == NULL)
        return;
    for (int i = 0; i < set->capacity; i++)
    {
        int index = __hashFunction__(key, set->capacity, i);
        if (set->buckets[index].status == EMPTY)
            return;
        if (set->buckets[index].status == OCCUPIED && set->buckets[index].key == key)
        {
            set->buckets[index].status = DELETED;
            set->length--;
            return;
        }
    }
}

/**
 * @brief Checks if a key is present in the set.
 * @param set A pointer to the set.
 * @param key The integer key to search for.
 * @return true if the key is in the set, false otherwise.
 */
bool contains(const Set *set, const int key)
{
    if (set == NULL)
        return false;
    for (int i = 0; i < set->capacity; i++)
    {
        int index = __hashFunction__(key, set->capacity, i);
        if (set->buckets[index].status == EMPTY)
            return false;
        else if (set->buckets[index].status == OCCUPIED && set->buckets[index].key == key)
            return true;
    }
    return false;
}

/**
 * @brief Computes the union of two sets.
 * @param set1 A pointer to the first set.
 * @param set2 A pointer to the second set.
 * @return A new Set containing all unique elements from both sets, or NULL on error.
 */
Set *unionOf(const Set *set1, const Set *set2)
{
    if (set1 == NULL || set2 == NULL)
        return NULL;
    Set *result = init(set1->capacity + set2->capacity);
    for (int i = 0; i < set1->capacity; i++)
        if (set1->buckets[i].status == OCCUPIED)
            insert(result, set1->buckets[i].key);
    for (int i = 0; i < set2->capacity; i++)
        if (set2->buckets[i].status == OCCUPIED)
            insert(result, set2->buckets[i].key);
    return result;
}

/**
 * @brief Computes the intersection of two sets.
 * @param set1 A pointer to the first set.
 * @param set2 A pointer to the second set.
 * @return A new Set containing elements common to both sets, or NULL on error.
 */
Set *intersectionOf(const Set *set1, const Set *set2)
{
    if (set1 == NULL || set2 == NULL)
        return NULL;
    Set *result = init(set1->capacity < set2->capacity ? set1->capacity : set2->capacity);
    for (int i = 0; i < set1->capacity; i++)
        if (set1->buckets[i].status == OCCUPIED && contains(set2, set1->buckets[i].key))
            insert(result, set1->buckets[i].key);
    return result;
}

/**
 * @brief Computes the difference of two sets (set1 - set2).
 * @param set1 A pointer to the first set.
 * @param set2 A pointer to the second set.
 * @return A new Set containing elements from set1 that are not in set2, or NULL on error.
 */
Set *differenceOf(const Set *set1, const Set *set2)
{
    if (set1 == NULL || set2 == NULL)
        return NULL;
    Set *result = init(set1->capacity);
    for (int i = 0; i < set1->capacity; i++)
        if (set1->buckets[i].status == OCCUPIED && !contains(set2, set1->buckets[i].key))
            insert(result, set1->buckets[i].key);
    return result;
}

/**
 * @brief Computes the symmetric difference of two sets.
 * @param set1 A pointer to the first set.
 * @param set2 A pointer to the second set.
 * @return A new Set containing elements unique to each set, or NULL on error.
 */
Set *symmetricDifferenceOf(const Set *set1, const Set *set2)
{
    if (set1 == NULL || set2 == NULL)
        return NULL;
    Set *result = init(set1->capacity + set2->capacity);
    for (int i = 0; i < set1->capacity; i++)
        if (set1->buckets[i].status == OCCUPIED && !contains(set2, set1->buckets[i].key))
            insert(result, set1->buckets[i].key);
    for (int i = 0; i < set2->capacity; i++)
        if (set2->buckets[i].status == OCCUPIED && !contains(set1, set2->buckets[i].key))
            insert(result, set2->buckets[i].key);
    return result;
}

/**
 * @brief Checks if two sets are equal.
 * @param set1 A pointer to the first set.
 * @param set2 A pointer to the second set.
 * @return true if both sets contain the same elements, false otherwise.
 */
bool isEqual(const Set *set1, const Set *set2)
{
    if (set1 == NULL || set2 == NULL || set1->length != set2->length)
        return false;
    for (int i = 0; i < set1->capacity; i++)
        if (set1->buckets[i].status == OCCUPIED && !contains(set2, set1->buckets[i].key))
            return false;
    return true;
}

/**
 * @brief Checks if one set is a subset of another.
 * @param subset A pointer to the potential subset.
 * @param set A pointer to the larger set.
 * @return true if subset is a subset of set, false otherwise.
 */
bool isSubset(const Set *subset, const Set *set)
{
    if (subset == NULL || set == NULL || subset->length > set->length)
        return false;
    for (int i = 0; i < subset->capacity; i++)
        if (subset->buckets[i].status == OCCUPIED && !contains(set, subset->buckets[i].key))
            return false;
    return true;
}

/**
 * @brief Checks if one set is a proper subset of another.
 * @param subset A pointer to the potential proper subset.
 * @param set A pointer to the larger set.
 * @return true if subset is a proper subset of set, false otherwise.
 */
bool isProperSubset(const Set *subset, const Set *set)
{
    if (subset == NULL || set == NULL || subset->length >= set->length)
        return false;
    for (int i = 0; i < subset->capacity; i++)
        if (subset->buckets[i].status == OCCUPIED && !contains(set, subset->buckets[i].key))
            return false;
    return true;
}

/**
 * @brief Checks if one set is a superset of another.
 * @param superset A pointer to the potential superset.
 * @param set A pointer to the smaller set.
 * @return true if superset is a superset of set, false otherwise.
 */
bool isSuperset(const Set *superset, const Set *set)
{
    return isSubset(set, superset);
}

/**
 * @brief Checks if one set is a proper superset of another.
 * @param superset A pointer to the potential proper superset.
 * @param set A pointer to the smaller set.
 * @return true if superset is a proper superset of set, false otherwise.
 */
bool isProperSuperset(const Set *superset, const Set *set)
{
    return isProperSubset(set, superset);
}

/**
 * @brief Checks if two sets are disjoint (have no common elements).
 * @param set1 A pointer to the first set.
 * @param set2 A pointer to the second set.
 * @return true if the sets are disjoint, false otherwise.
 */
bool isDisjoint(const Set *set1, const Set *set2)
{
    if (set1 == NULL || set2 == NULL)
        return false;
    for (int i = 0; i < set1->capacity; i++)
        if (set1->buckets[i].status == OCCUPIED && contains(set2, set1->buckets[i].key))
            return false;
    return true;
}

/**
 * @brief Prints all elements of the set to the console.
 * @param set A pointer to the set.
 */
void traverse(const Set *set)
{
    if (set == NULL)
        return;
    printf("{");
    for (int i = 0; i < set->capacity; i++)
    {
        if (set->buckets[i].status == OCCUPIED)
            printf(" %d", set->buckets[i].key);
    }
    printf(" } : %.2f\n", __loadFactor__(set));
}

/**
 * @brief Displays the internal structure of the set for debugging purposes.
 * @param set A pointer to the set.
 */
void describe(const Set *set)
{
    if (set == NULL)
        return;
    for (int i = 0; i < set->capacity; i++)
    {
        printf("%2d | ", i);
        if (set->buckets[i].status == EMPTY)
            printf("EMP\n");
        else if (set->buckets[i].status == OCCUPIED)
            printf("%d\n", set->buckets[i].key);
        else if (set->buckets[i].status == DELETED)
            printf("DEL\n");
    }
}

#endif // SET_H
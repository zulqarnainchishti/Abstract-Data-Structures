#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * @struct DisjointSet
 * @brief Represents the Disjoint Set Union (DSU) data structure.
 * @note Implements Union-by-Rank and Path-Compression for near O(1) amortized time complexity.
 */
typedef struct
{
    int *parent; // Stores the parent of each element (representative/root if parent[i] == i)
    int *rank;   // Stores the rank (approximate height) of the tree rooted at the index
    int size;    // Total number of elements in the universe [0, size - 1]
} DisjointSet;

/**
 * @brief Initializes a new Disjoint Set structure for 'n' elements.
 * @param n The number of elements (universe size) to manage, from 0 to n-1.
 * @return A pointer to the newly created DisjointSet, or NULL on failure.
 */
DisjointSet *init(int n)
{
    if (n <= 0)
        return NULL;
    DisjointSet *dsu = (DisjointSet *)malloc(sizeof(DisjointSet));
    if (dsu == NULL)
        return NULL;
    dsu->parent = (int *)malloc(n * sizeof(int));
    dsu->rank = (int *)calloc(n, sizeof(int));
    if (dsu->parent == NULL || dsu->rank == NULL)
    {
        free(dsu->parent);
        free(dsu->rank);
        free(dsu);
        return NULL;
    }
    dsu->size = n;
    // Each element starts in its own set
    for (int i = 0; i < n; i++)
        dsu->parent[i] = i;
    return dsu;
}

/**
 * @brief Creates a deep copy of an existing Disjoint Set structure.
 * @param source The DisjointSet to copy.
 * @return A pointer to the new, copied DisjointSet, or NULL on failure.
 */
DisjointSet *copy(const DisjointSet *source)
{
    if (source == NULL)
        return NULL;
    DisjointSet *dsu = init(source->size);
    if (dsu == NULL)
        return NULL;

    for (int i = 0; i < source->size; i++)
    {
        dsu->parent[i] = source->parent[i];
        dsu->rank[i] = source->rank[i];
    }
    return dsu;
}

/**
 * @brief Resets the Disjoint Set to its initial state, where every element is in its own set.
 * @param dsu The DisjointSet structure to clear.
 */
void clear(DisjointSet *dsu)
{
    if (dsu == NULL)
        return;
    for (int i = 0; i < dsu->size; i++)
    {
        dsu->parent[i] = i;
        dsu->rank[i] = 0;
    }
}

/**
 * @brief Frees all memory allocated for the DisjointSet structure.
 * @param dsu The DisjointSet structure to destroy.
 */
void destroy(DisjointSet *dsu)
{
    if (dsu == NULL)
        return;
    free(dsu->parent);
    free(dsu->rank);
    free(dsu);
}

/**
 * @brief Finds the representative (root) of the set containing element 'i'.
 * @note This function implements the crucial **Path Compression** optimization.
 * @param dsu The DisjointSet structure.
 * @param i The element whose set representative is sought (0 <= i < dsu->size).
 * @return The index of the set representative, or -1 if dsu or index is invalid.
 */
int find(DisjointSet *dsu, int i)
{
    if (dsu == NULL || i < 0 || i >= dsu->size)
        return -1;
    // Base case: i is the root
    if (dsu->parent[i] == i)
        return i;
    // Path Compression: set parent[i] directly to the root
    return dsu->parent[i] = find(dsu, dsu->parent[i]);
}

/**
 * @brief Unites the sets containing elements 'i' and 'j'.
 * @note This function implements the **Union-by-Rank** optimization.
 * @param dsu The DisjointSet structure.
 * @param i The first element.
 * @param j The second element.
 * @return True if the union was successful (i.e., i and j were in different sets), otherwise false.
 */
bool unite(DisjointSet *dsu, int i, int j)
{
    if (dsu == NULL || i < 0 || i >= dsu->size || j < 0 || j >= dsu->size)
        return false;
    int root_i = find(dsu, i);
    int root_j = find(dsu, j);

    if (root_i != root_j)
    {
        // Union by Rank: attach the smaller rank tree to the root of the larger rank tree
        if (dsu->rank[root_i] < dsu->rank[root_j])
            dsu->parent[root_i] = root_j;
        else if (dsu->rank[root_i] > dsu->rank[root_j])
            dsu->parent[root_j] = root_i;
        else
        {
            // Ranks are equal, so choose one as the new root and increment its rank
            dsu->parent[root_j] = root_i;
            dsu->rank[root_i]++;
        }
        return true;
    }
    return false;
}

/**
 * @brief Checks if two elements are in the same disjoint set.
 * @param dsu The DisjointSet structure.
 * @param i The first element.
 * @param j The second element.
 * @return True if 'i' and 'j' belong to the same set, otherwise false.
 */
bool connected(DisjointSet *dsu, int i, int j)
{
    if (dsu == NULL || i < 0 || i >= dsu->size || j < 0 || j >= dsu->size)
        return false;
    return find(dsu, i) == find(dsu, j);
}

/**
 * @brief Displays the current state of the DisjointSet structure (parent, rank, and root for each element).
 * @note This function calls the non-const `find` to ensure path compression occurs for the roots displayed.
 * @param dsu The DisjointSet structure to traverse.
 */
void traverse(const DisjointSet *dsu)
{
    if (dsu == NULL)
    {
        printf("DisjointSet is NULL.\n");
        return;
    }
    printf("DisjointSet State (Size: %d)\n", dsu->size);
    printf("---------------------------\n");
    for (int i = 0; i < dsu->size; i++)
    {
        // Casting away const to call find and trigger path compression for current display
        printf("Element %d: Parent=%d, Rank=%d, Root=%d\n", i, dsu->parent[i], dsu->rank[i], find((DisjointSet *)dsu, i));
    }
}

#endif // DISJOINT_SET_H
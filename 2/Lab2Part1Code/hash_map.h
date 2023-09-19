#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <optional>
#include <stddef.h>
#include <stdlib.h>

#include "hash_list.h"

class hash_map
{

public:
    /**
     * @brief Construct a new hash map object
     */
    hash_map(size_t capacity);

    /**
     * @brief Construct a new hash map object
     *
     * @param other
     *  The map to create a copy of
     */
    hash_map(const hash_map &other);

    /**
     * @brief Constructs a new hash map from other
     *
     * @param other
     *  The map to create a copy of
     * @return hash_map&
     *  Returns a reference to the newly constructed hash map. This ensures that
     *  a = b = c works
     */
    hash_map &operator=(const hash_map &other);

    /**
     * @brief Insert the key/value pair into the map. If the specified key already exists
     * in the map update the associated value, otherwise insert a new key value pair
     *
     * @param key
     *  The key to insert
     * @param value
     *  The value to insert
     */
    void insert(int key, float value);

    /**
     * @brief Return an optional containing the value associated with the specified key.
     * If the key isn't in the map return an empty optional.
     *
     * @param key
     *  The key to search for
     * @return
     *  An empty optional (if the key isn't in the map), otherwise return an optional
     *  containing the value associated with the specified key
     */
    std::optional<float> get_value(int key) const;

    /**
     * @brief Remove the key and corresponding value from the map and return true.
     * If the key isn't in the map return false.
     *
     * @param key
     *  The key to remove from the list
     * @return
     *  True if key was present
     *  False otherwise
     */
    bool remove(int key);

    /**
     * @brief Return the number of key/value pairs in the map
     */
    size_t get_size() const;

    /**
     * @brief Returns the capacity of the map
     *
     * @return
     *  The capacity of the hash map
     */
    size_t get_capacity() const;

    /**
     * @brief Copies all the keys from the hash_map into the specified array
     *
     * @param keys
     *  A pointer to an array that has enough space to store all the keys
     *  in the hash_map.
     */
    void get_all_keys(int *keys);

    /**
     * @brief Get the number of elements in each hash_list pointed to by _head.
     * So buckets[0] should be the number of elements in the hash list at index 0
     *    buckets[1] should be the number of elements in the hash list at index 1
     *    etc
     * In order for this to work you MUST use the hash function that we specified in the
     * handout. To remind you again here, the hash function is simply the absolute value of the
     * key
     *
     * @param buckets
     *  A pointer to an array that has at least _capacity elements
     */
    void get_bucket_sizes(size_t *buckets);

    /**
     * @brief Frees all memory associated with the map
     */
    ~hash_map();

private:
    /** The number of key/value pairs in the map */
    size_t _size;

    /** The number of buckets in the hash map */
    size_t _capacity;

    /** A pointer to an array of hash_lists */
    hash_list *_head;
};

#endif
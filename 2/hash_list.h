#ifndef HASH_LIST_H
#define HASH_LIST_H

#include <optional>
#include <stddef.h>
#include <stdlib.h>

/** A single key/value pair in the linked list */
struct node
{
    /** The key the node is storing */
    int key;

    /** the value the node is storing */
    float value;

    /** a pointer to the next node */
    node *next;
};

/** A list that stores key/value pairs */
class hash_list
{

public:

    /**
     * @brief Create an empty list
     */
    hash_list();

    /**-----------------------------------------------------------------------------------
     * START Part 1
     *------------------------------------------------------------------------------------*/

    /**
     * @brief Insert a node with the corresponding key value pair into the list.
     * If a node with the associated key already exists, update that node with the new value
     * instead of adding a new node to the list.
     * 
     * @param key
     *  The key to insert into the list
     * @param value
     *  The value to insert into the list
     */
    void insert(int key, float value);

    /**
     * @brief 
     * 
     * @return true if the list is empty
     * @return false if the list is not empty
     */
    bool isEmpty() const;

    /**
     * @brief Return an optional containing the value associated with the specified key. If the key
     * isn't in the list return an empty optional.
     * 
     * @param key
     *  The key to search the list for
     * @return
     *  If the key isn't in the list returns an empty optional
     *  If the key is in the list returns the corresponding value
     */
    std::optional<float> get_value(int key) const;

    /**
     * @brief Remove the node containing the specified key from the list and return true.
     * If the key isn't in the list return false.
     * 
     * @param key
     *  The key to remove from the list
     * @return
     *  True if the key was removed from the list
     *  False if the key wasn't in the list
     */
    bool remove(int key);

    /**
     * @brief Return the number of nodes in the list. 
     * This function must run in constant time
     * 
     * @return
     *  the number of nodes in the list
     */
    size_t get_size() const;

    /**
     * @brief Free all memory associated with the nodes. 
     * This must not free the nodes recursively
     */
    ~hash_list();


    /**-----------------------------------------------------------------------------------
     * END Part 1
     *------------------------------------------------------------------------------------*/


    /**-----------------------------------------------------------------------------------
     * START Part 2
     *------------------------------------------------------------------------------------*/
    /**
     * @brief The copy constructor
     * 
     * @param other
     *  The list to create a copy of
     */
    hash_list(const hash_list &other);

    /**
     * @brief Assignment operator
     * 
     * @param other
     *  The list to create a copy of 
     * @return
     *  A reference to the list that was created. This allows for code like
     *  a = b = c to work
     */
    hash_list &operator=(const hash_list &other);

    /**
     * @brief Resets the iterator back to point to the first element in the list. If the list is 
     * empty then the iterator is set to NULL.
     */
    void reset_iter();

    /**
     * @brief Moves the iterator to the next element. If the iterator points to the last element
     * of the list when this is called the iterator is set to NULL. If the iterator is NULL
     * when this function is called then this function does nothing
     */
    void increment_iter();

    /**
     * @brief Return an optional that contains a pointer to the key and a pointer to the value
     * of the node pointed to by the iterator. If the iterator is NULL this returns
     * an empty optional
     * 
     * @return
     *  If the iterator is NULL returns an empty optional
     *  Otherwise returns a pointer to the key/value pointed to by the current iterator
     */
    std::optional<std::pair<const int *, float *>> get_iter_value();

    /**
     * @brief Returns true if the iterator is NULL
     * 
     * @return
     *  True if the iterator is NULL
     *  False otherwise
     */
    bool iter_at_end();
    /**-----------------------------------------------------------------------------------
     * END Part 2
     *------------------------------------------------------------------------------------*/

private:

    /** The number of nodes in the list */
    size_t size;

    /** A pointer to the first node in the list */
    node *head;

    /** The node that the iterator is currently pointing to */
    node *iter_ptr;
};

#endif

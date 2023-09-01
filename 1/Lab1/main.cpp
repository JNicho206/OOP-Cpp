#include <iostream>

#include "hash_list.h"

int trace_1();
int trace_2();
int trace_3();
int trace_4();
int trace_5();

#ifdef PART2 // Only test iterators in part 2
void iterator_example(hash_list &list)
{
    /** We have to reset the iterator before we use it */
    list.reset_iter();

    /** We want to iterate over all nodes, so keep iterating until we're at the end */
    while (!list.iter_at_end())
    {
        /** Get pointers to key/value pairs */
        std::optional<std::pair<const int *, float *>> node_values = list.get_iter_value();

        /** Increment the VALUE. Note that the key remains unchanged */
        (*node_values.value().second)++;

        std::cout << "Key: " << *node_values.value().first
                  << " and value: " << *node_values.value().second << std::endl;

        /** Go to the next element */
        list.increment_iter();
    }
}
#endif

int main(int argc, char *argv[])
{

#ifdef PART1
    hash_list list;

    if (list.get_size() != 0)
    {
        std::cout << "Invalid size" << std::endl;
        exit(1);
    }

    list.insert(3, 3);
    list.insert(4, 4);
    list.insert(5, 5);
    list.insert(6, 6);

    if (list.get_size() != 4)
    {
        std::cout << "Invalid size" << std::endl;
        exit(1);
    }

    if (!list.get_value(3).has_value())
    {
        std::cout << "expected 3 to be in list but it wasn't" << std::endl;
        exit(1);
    }

    if (!list.remove(3))
    {
        std::cout << "Failed to remove 3 from list" << std::endl;
        exit(1);
    }

    if (list.get_value(3).has_value())
    {
        std::cout << "Unexpected 3 in list" << std::endl;
        exit(1);
    }
#endif

#ifdef PART2
    iterator_example(list);
#endif

}

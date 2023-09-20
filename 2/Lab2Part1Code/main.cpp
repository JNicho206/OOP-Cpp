#include "hash_map.h"
#include <iostream>


int main(int argc, char** argv)
{
    //Test cases

    hash_map* map = new hash_map(3);

    for (int i = 0; i < 3; i++)
    {
        hash_list hash_l = map->get_head()[i];
        std::cout << hash_l.get_size() << hash_l.get_head();
    }
}
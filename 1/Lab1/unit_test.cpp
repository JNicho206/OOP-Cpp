#include "unit_test.h"

void t_insert_empty()
{
    std::cout << "Testing insert into empty list ... ";
    hash_list list;

    list.insert(3, 3);

    if (list.get_size() != 1)
    {
        std::cout << "Test failed: ";
        std::cout << "Invalid size when testing insert" << std::endl;
    }

    if (!list.get_value(3).has_value())
    {
        std::cout << "Test failed: ";
        std::cout << "expected 3 to be in list but it wasn't" << std::endl;
    }

    std::cout << "Test passed" << std::endl;
}

void t_insert_nonempty()
{
    std::cout << "Testing insert into nonempty list ... ";
    hash_list list;

    list.insert(3, 3);
    list.insert(4, 4);

    if (list.get_size() != 2)
    {   
        std::cout << "Test failed: ";
        std::cout << "Invalid size when testing insert" << std::endl;
    }

    if (!list.get_value(3).has_value())
    {
        std::cout << "Test failed: ";
        std::cout << "expected 3 to be in list but it wasn't" << std::endl;
    }

    if (!list.get_value(3).has_value())
    {
        std::cout << "Test failed: ";
        std::cout << "expected 4 to be in list but it wasn't" << std::endl;
    }

    list.insert(3,5);

    if (list.get_size() != 2)
    {
        std::cout << "Test failed: ";
        std::cout << "invalid size after duplicate key insertion." << std::endl;
    }

    if (!list.get_value(3).has_value())
    {
        std::cout << "Test failed: ";
        std::cout << "expected 3 to be in the list but it wasn't." << std::endl;
    }


    std::cout << "Test passed!";
}

void t_remove()
{
    hash_list list;

    list.insert(1, 1);
    list.insert(2,2);

}

int main(int argc, char *argv[])
{


    

    
}
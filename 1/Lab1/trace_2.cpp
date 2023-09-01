

#include <iostream>
#include "hash_list.h"

int trace_2()
{
    std::cout << "Running trace 2\n";
    
    hash_list list;
    std::cout << "Inserting key=1, value=1\n";
    list.insert(1, 1);
    std::cout << "Inserting key=1, value=11\n";
    list.insert(1, 11);
    std::cout << "Inserting key=2, value=2\n";
    list.insert(2, 2);
    std::cout << "Inserting key=2, value=22\n";
    list.insert(2, 22);
    std::cout << "Inserting key=3, value=3\n";
    list.insert(3, 3);
    std::cout << "Inserting key=3, value=33\n";
    list.insert(3, 33);
    std::cout << "Inserting key=4, value=4\n";
    list.insert(4, 4);
    std::cout << "Inserting key=4, value=44\n";
    list.insert(4, 44);
    if (!list.get_value(4).has_value())
    {
        std::cout << "GET failed for key=4\n";
        return 1;
    }
    else
    {
        std::cout << "GET succeeded for key=4\n";
        
    }
    if (!list.get_value(3).has_value())
    {
        std::cout << "GET failed for key=3\n";
        return 1;
    }
    else
    {
        std::cout << "GET succeeded for key=3\n";
        
    }
    if (!list.get_value(2).has_value())
    {
        std::cout << "GET failed for key=2\n";
        return 1;
    }
    else
    {
        std::cout << "GET succeeded for key=2\n";
        
    }
    if (!list.get_value(1).has_value())
    {
        std::cout << "GET failed for key=1\n";
        return 1;
    }
    else
    {
        std::cout << "GET succeeded for key=1\n";
        
    }
    
    return 0;
}


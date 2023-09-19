#include "hash_list.h"

hash_list::hash_list() { size = 0; head = nullptr; iter_ptr = nullptr;}

/**-----------------------------------------------------------------------------------
 * START Part 1
 *------------------------------------------------------------------------------------*/
bool hash_list::isEmpty() const
{
    return size == 0;
}

void hash_list::insert(int key, float value) 
{
    //Empty list
    if (this->isEmpty())
    {
        //Create node
        node* n = new node;
        n->key = key;
        n->value = value;
        n->next = nullptr;
        head = n;
        size++;
    }
    else 
    {
        //Insert key at the end of the list or replace if key is present
        node* n;
        n = head;
        while (1)
        {
            //Same key so replace
            if (n->key == key)
            {
                n->value = value;
                return;
            }
            else
            {
                if (n->next == nullptr)
                {
                    //Create new node
                    node* next = new node;
                    next->key = key;
                    next->value = value;
                    next->next = nullptr;
                    n->next = next;
                    size++;
                    return;
                }
                else
                {
                    n = n->next;
                }

            }
        }
    }
}

std::optional<float> hash_list::get_value(int key) const 
{ 
    if (this->isEmpty())
    {
        return std::nullopt;
    }

    node* n = head;
    while (n != nullptr && n->key != key)
    {
        n = n->next;
    }
    if (n == nullptr)
    {
        return std::nullopt; 
    }
    else 
    {
        //Return optional with value
        std::optional<float> ret_val = n->value;
        return ret_val;
    }
}

bool hash_list::remove(int key) 
{ 
    if (this->isEmpty())
    {
        return false;
    }

    node* n = head;
    //If the node to be removed is the head node
    if (n->key == key)
    {
        head = n->next;
        delete n;
        size--;
        return true;   
    }

    while(1)
    {
        if (n->next == nullptr)
        {
            return false;
        }   
        else if (n->next->key == key)
        {
            //Remove node
            node* del = n->next;
            n->next = del->next;

            delete del;
            size--;
            return true;
        }
        else 
        {
            n = n->next;
        }
    }
}

size_t hash_list::get_size() const { return size; }

hash_list::~hash_list() 
{
    node* fre = head;
    while (head != nullptr)
    {
        head = head->next;
        delete fre;
        fre = head;
    }
}

/**-----------------------------------------------------------------------------------
 * END Part 1
 *------------------------------------------------------------------------------------*/


/**-----------------------------------------------------------------------------------
 * START Part 2
 *------------------------------------------------------------------------------------*/

hash_list::hash_list(const hash_list &other) : head(nullptr), size(0)
{
    //Copy constructor

    //Object is not initialized yet so don't have to free anything
    

    node* curr = other.head;

    while (curr != nullptr)
    {
        insert(curr->key, curr->value);
        curr = curr->next;
    }

    
    
}

hash_list &hash_list::operator=(const hash_list &other) 
{
    //Overloaded assignment operator
    
    //Handle self assignment 
    if (this == &other)
    {
        return *this;
    }

    //Invoke copy constructor to allocate memory and copy values
    hash_list temp(other);

    //Swap pointers
    std::swap(head, temp.head);
    //Now the temporary list points to the original list (the one to be deallocated)
    
    return *this;

    //temp goes out of scope, the destructor is called and the memory is freed.

}

void hash_list::reset_iter()
{
    if (this->get_size() == 0)
    {
        iter_ptr = nullptr;
        return;
    }

    iter_ptr = head;
}


void hash_list::increment_iter() 
{
    if (this->iter_at_end()) { return; }
    if (iter_ptr->next == nullptr) { iter_ptr = nullptr; return; }
    else { iter_ptr = iter_ptr->next; }
}


std::optional<std::pair<const int *, float *>> hash_list::get_iter_value() 
{ 

    if (this->iter_at_end()) { return std::nullopt; }
    
    const int* p = (&(iter_ptr->key));
    float* fp = &(iter_ptr->value);
    std::optional<std::pair<const int *, float *>> ret;
    ret = std::make_pair(p, fp);
    return ret;
}


bool hash_list::iter_at_end() { return (iter_ptr == nullptr) ? true : false; }
/**-----------------------------------------------------------------------------------
 * END Part 2
 *------------------------------------------------------------------------------------*/

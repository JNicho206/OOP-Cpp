#include "hash_map.h"

hash_map::hash_map(size_t capacity)
{
    this->_size = 0;
    this->_capacity = capacity;
    this->_head = new hash_list[capacity];
}

hash_map::hash_map(const hash_map &other) :  _size(0), _capacity(0), _head(nullptr) 
{
    //Empty hash map
    if (other.get_capacity() == 0)
    {
        return;
    }

    _head = new hash_list[other.get_capacity()];
    _capacity = other.get_capacity();
    _size = other.get_size();

    for (int i = 0; i < _capacity; i++)
    {
        _head[i] = other._head[i];
    }

}

hash_map& hash_map::operator=(const hash_map &other)
{
    if (this == &other)
    {
        return *this;
    }

    hash_map temp(other);

    std::swap(this->_head, temp._head);
    
    this->_capacity = temp._capacity;
    this->_size = temp._size;

    return *this;
}

void hash_map::insert(int key, float value)
{
    //Use hash function to get bucket index
    int index = key % this->_capacity;

    size_t before = this->_head[index].get_size();
    //Insert into list at that index
    this->_head[index].insert(key, value);

    if (before == this->_head[index].get_size()) { return; }

    //Increment size
    this->_size++;
}

std::optional<float> hash_map::get_value(int key) const
{
    //If empty return nullopt
    if (this->get_size() == 0)
    {
        return std::nullopt;
    }

    int index = key % this->get_capacity();

    //Hash list get_value returns nullopt if it doesn't exist or a populated optional
    return this->_head[index].get_value(key);
}

bool hash_map::remove(int key)
{
    //If map is empty return false
    if (this->get_size() == 0) { return false; }

    //Search
    int index = key % this->get_capacity();
    if (this->_head[index].remove(key) == false)
    {
        return false;
    }
    else
    {
        this->_size -= 1;
        return true;
    }


}

size_t hash_map::get_size() const 
{
    return this->_size;
}

size_t hash_map::get_capacity() const 
{
    return this->_capacity;
}

hash_list* hash_map::get_head() const
{
    return this->_head;
}

void hash_map::get_all_keys(int* keys)
{
    //For each bucket (list)
    int key_index = 0;
    for (int i = 0; i < this->get_capacity(); i++)
    {
        hash_list curr_list = this->_head[i];
        curr_list.reset_iter();
        std::optional<std::pair<const int*, float*>> iter_val = curr_list.get_iter_value();
        //For each node
        while (iter_val.has_value())
        {
            std::pair<const int*, float*> iter_pair = iter_val.value();
            //  Grab key and put in array
            const int* key = iter_pair.first;
            keys[key_index] = *key;
            //  Increment index
            key_index++;
            curr_list.increment_iter();
            iter_val = curr_list.get_iter_value();
        }
    }
    
    
}

void hash_map::get_bucket_sizes(size_t *buckets)
{
    int bucket_index = 0;

    //Loop through buckets (lists)
    for (int i = 0; i < this->get_capacity(); i++)
    {
        //Assign bucket size
        buckets[bucket_index] = this->_head[i].get_size();

        bucket_index++;
    }
}

hash_map::~hash_map()
{
    for (int i = 0; i < this->get_capacity(); i++)
    {
        _head[i].~hash_list();
    }

    delete[] this->_head;
}
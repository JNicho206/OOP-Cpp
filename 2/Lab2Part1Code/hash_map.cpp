#include "hash_map.h";

hash_map::hash_map(size_t capacity)
{

}

hash_map::hash_map(const hash_map &other)
{

}

hash_map& hash_map::operator=(const hash_map &other)
{

}

void hash_map::insert(int key, float value)
{
    //Use hash function to get bucket index
    
    //Insert into list at that index

    //Increment capacity
}

std::optional<float> hash_map::get_value(int key) const
{
    //If empty return nullopt

    //If key doesn't exist return nullopt

    //Else return
    //std::optional<float> ret = 


}

bool hash_map::remove(int key)
{
    //If map is empty return false

    //If key doesn't exist return null opt

    this->_capacity -= 1;
    return true;
}

size_t hash_map::get_size() const 
{
    return this->_size;
}

size_t hash_map::get_capacity() const 
{
    return this->_capacity;
}

void hash_map::get_all_keys(int* keys)
{
    //For each bucket (list)
    //For each node
    //  Grab key and put in array
    //  Increment index
}

void hash_map::get_bucket_sizes(size_t *buckets)
{

}
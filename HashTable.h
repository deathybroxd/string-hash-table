/* HashTable .h
- templated, all implementations here
*/
#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <utility>
#include <optional>
#include <functional>
#include <cstddef>

template <class K, class V>
class HashTable {
public:
    // constructor
    HashTable();

    // destructor (default) - no heap allocated memory
    ~HashTable() = default;

    // insert kv
    void Insert(const K& key, const V& value);

    // resize hashtable
    void Resize(const std::size_t& newSize);

    // get index
    std::optional<V> Get(const K& key);

    // remove index
    std::optional<V> Remove(const K& key);

    // size
    std::size_t Size();

    // is empty
    bool IsEmpty();

private:
    // index helper function - returns a size_t index
    std::size_t GetIndex(const K& key, std::size_t tableSize);

    std::vector<std::list<std::pair<K, V>>> m_table; // the actual hash table, a vector of "buckets" of kv pairs
    std::size_t m_size; 
    static constexpr double LOAD_FACTOR_THRESHOLD = 0.7; // sweetspot value for resizing hash table, 1 waits too long, 0.3 resizes too much
    static constexpr int DEFAULT_TABLE_SIZE = 8;
};

// default constructor
template <class K, class V>
HashTable<K, V>::HashTable() : m_table(DEFAULT_TABLE_SIZE), m_size(0) {}

template <class K, class V>
void HashTable<K, V>::Insert(const K& key, const V& value) {
    std::size_t index = GetIndex(key, m_table.size());
    std::list<std::pair<K, V>>& bucket = m_table.at(index);

    // search for the key, if found just update the corresponding value
    for(auto it = bucket.begin(); it != bucket.end(); ++it) {
        if(it->first == key) {
            it->second = value;
            return;
        }
    }
    // key not found, so add to the current bucket
    bucket.push_back(std::make_pair(key, value));
    m_size++;

    // resize table after increment
    double loadFactor = static_cast<double>(m_size) / m_table.size();
    if(loadFactor > LOAD_FACTOR_THRESHOLD) {
        Resize(m_table.size() * 2);
    }
}

template <class K, class V>
void HashTable<K, V>::Resize(const std::size_t& newSize) {
    std::vector<std::list<std::pair<K, V>>> resizedTable(newSize);

    for(std::size_t i = 0; i < m_table.size(); ++i) {
        std::list<std::pair<K, V>>& bucket = m_table.at(i);
        for(auto it = bucket.begin(); it != bucket.end(); ++it) {
            K key = it->first;
            V value = it->second;
            std::size_t index = GetIndex(key, newSize);
            resizedTable.at(index).push_back(std::make_pair(key, value));
        }
    }
   m_table = std::move(resizedTable); // m_table = resizedTable is fine but move makes it faster
}

template <class K, class V>
std::optional<V> HashTable<K, V>::Get(const K& key) {
    std::size_t index = GetIndex(key, m_table.size());
    std::list<std::pair<K, V>>& bucket = m_table.at(index);
    for(auto it = bucket.begin(); it != bucket.end(); ++it) {
        if(it->first == key) {
            return it->second; // value
        }
    }
    return std::nullopt;
}

template <class K, class V>
std::optional<V> HashTable<K, V>::Remove(const K& key) {
    std::size_t index = GetIndex(key, m_table.size());
    std::list<std::pair<K, V>>& bucket = m_table.at(index);
    for(auto it = bucket.begin(); it != bucket.end(); ++it) {
        if(it->first == key) {
            V value = it->second;
            bucket.erase(it);
            m_size--;
            return value;
        }
    }
    return std::nullopt;
}

template <class K, class V>
std::size_t HashTable<K, V>::Size() {
    return m_size;
}

template <class K, class V>
bool HashTable<K, V>::IsEmpty() {
    if(m_size <= 0) {
        return true;
    } else {
        return false;
    }
}


// ***** PRIVATE METHODS *****
template <class K, class V>
std::size_t HashTable<K, V>::GetIndex(const K& key, std::size_t tableSize) {
    std::hash<K> hasher;
    std::size_t hashValue = hasher(key);
    return hashValue % tableSize;
}

#endif
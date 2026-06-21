/* StringHashTable .h
- templated, all implementations here
*/
#ifndef STRINGHASHTABLE_H
#define STRINGHASHTABLE_H
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <utility>
#include <optional>
#include <functional>
#include <cstddef>

template <class V>
class StringHashTable {
public:
    // constructor
    StringHashTable();

    // destructor (default) - no heap allocated memory
    ~StringHashTable() = default;

    // insert kv
    void Insert(const std::string& key, const V& value);

    // resize hashtable
    void Resize(const std::size_t& newSize);

    // get index
    std::optional<V> Get(const std::string& key);

    // remove index
    std::optional<V> Remove(const std::string& key);

    // size
    std::size_t Size();

    // is empty
    bool IsEmpty();

private:
    // index helper function - returns a size_t index
    std::size_t GetIndex(const std::string& key, std::size_t tableSize);

    // hasher helper function - returns a size_t hash
    std::size_t StringHash(const std::string& key);

    std::vector<std::list<std::pair<std::string, V>>> m_table; // the actual hash table, a vector of "buckets" of kv pairs
    std::size_t m_size; 
    static constexpr double LOAD_FACTOR_THRESHOLD = 0.7; // sweetspot value for resizing hash table, 1 waits too long, 0.3 resizes too much
    static constexpr int DEFAULT_TABLE_SIZE = 8;
    static constexpr std::size_t PRIME_MULTIPLIER = 31; // for StringHash()
    static constexpr std::size_t LARGE_PRIME_MODULO = 1'000'000'009; // for StringHash()
};

// default constructor
template<class V>
StringHashTable<V>::StringHashTable() : m_table(DEFAULT_TABLE_SIZE), m_size(0) {}

template<class V>
void StringHashTable<V>::Insert(const std::string& key, const V& value) {
    std::size_t index = GetIndex(key, m_table.size());
    std::list<std::pair<std::string, V>>& bucket = m_table.at(index);

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

template<class V>
void StringHashTable<V>::Resize(const std::size_t& newSize) {
    std::vector<std::list<std::pair<std::string, V>>> resizedTable(newSize);

    for(std::size_t i = 0; i < m_table.size(); ++i) {
        std::list<std::pair<std::string, V>>& bucket = m_table.at(i);
        for(auto it = bucket.begin(); it != bucket.end(); ++it) {
            std::string key = it->first;
            V value = it->second;
            std::size_t index = GetIndex(key, newSize);
            resizedTable.at(index).push_back(std::make_pair(key, value));
        }
    }
   m_table = std::move(resizedTable); // m_table = resizedTable is fine but move makes it faster
}

template<class V>
std::optional<V> StringHashTable<V>::Get(const std::string& key) {
    std::size_t index = GetIndex(key, m_table.size());
    std::list<std::pair<std::string, V>>& bucket = m_table.at(index);
    for(auto it = bucket.begin(); it != bucket.end(); ++it) {
        if(it->first == key) {
            return it->second; // value
        }
    }
    return std::nullopt;
}

template<class V>
std::optional<V> StringHashTable<V>::Remove(const std::string& key) {
    std::size_t index = GetIndex(key, m_table.size());
    std::list<std::pair<std::string, V>>& bucket = m_table.at(index);
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

template<class V>
std::size_t StringHashTable<V>::Size() {
    return m_size;
}

template<class V>
bool StringHashTable<V>::IsEmpty() {
    if(m_size <= 0) {
        return true;
    } else {
        return false;
    }
}


// ***** PRIVATE METHODS *****
template<class V>
std::size_t StringHashTable<V>::GetIndex(const std::string& key, std::size_t tableSize) {
    std::size_t hashValue = StringHash(key);
    return hashValue % tableSize;
}

template<class V>
std::size_t StringHashTable<V>::StringHash(const std::string& key) {
    std::size_t hash = 0;
    for(const char& ch : key) {
        hash = (hash * PRIME_MULTIPLIER + ch) % LARGE_PRIME_MODULO;
    }
    return hash;
}

#endif
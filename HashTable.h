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

template <class K, class V>
class HashTable {
public:
    // constructor
    HashTable();

    // destructor (default)
    ~HashTable() = default;

    // insert kv
    void Insert();

    // resize hashtable
    void Resize();

    // get index
    std::optional<V> Get();

    // remove index
    std::optional<V> Remove();

private:
    // index helper function
    int GetIndex();

    std::vector<std::list<std::pair<K, V>>>

};
#endif
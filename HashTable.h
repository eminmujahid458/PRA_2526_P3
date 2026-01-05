#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include <string>

#include "Dict.h"
#include "TableEntry.h"
#include "../P1/PRA_2526_P1/ListLinked.h"

template <typename V>
class HashTable : public Dict<V> {

private:
    int n;
    int max;
    ListLinked<TableEntry<V>>* table;

    int h(std::string key) {
        int sum = 0;
        for (size_t i = 0; i < key.size(); i++)
            sum += int(key.at(i));
        return sum % max;
    }

public:
    HashTable(int size) {
        max = size;
        n = 0;
        table = new ListLinked<TableEntry<V>>[max];
    }

    ~HashTable() {
        delete[] table;
    }
    
    void insert(std::string key, V value) {
    int pos = h(key);
    TableEntry<V> te(key);

    if (table[pos].search(te) != -1)
        throw std::runtime_error("Key '" + key + "' already exists!");

    table[pos].append(TableEntry<V>(key, value));
    n++;
    }

    V search(std::string key) {
    int pos = h(key);
    TableEntry<V> te(key);

    int idx = table[pos].search(te);
    if (idx == -1)
        throw std::runtime_error("Key '" + key + "' not found!");

    return table[pos].get(idx).value;
    }
    
    V remove(std::string key) {
    int pos = h(key);
    TableEntry<V> te(key);

    int idx = table[pos].search(te);
    if (idx == -1)
        throw std::runtime_error("Key '" + key + "' not found!");

    V val = table[pos].get(idx).value;
    table[pos].remove(idx);
    n--;
    return val;
    }

    int entries() {
        return n;
    }

    int capacity() {
        return max;
    }

    V operator[](std::string key) {
        return search(key);
    }
    friend std::ostream& operator<<(std::ostream& os, const HashTable<V>& ht) {
    os << "HashTable [entries: " << ht.n << ", capacity: " << ht.max << "]\n";
    os << "==============\n";
    for (int i = 0; i < ht.max; ++i) {
        os << "== Cubeta " << i << " ==\nList => [";

        // Imprimir los elementos de la lista en la cubeta i
        for (int j = 0; j < ht.table[i].size(); ++j) {
            TableEntry<V> e = ht.table[i].get(j);
            os << "('" << e.key << "' => " << e.value << ")";
            if (j != ht.table[i].size() - 1) os << " ";
        }

        os << "]\n\n";
    }
    os << "==============\n";
    return os;
}
};

#endif

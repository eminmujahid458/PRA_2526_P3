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
        if (table[pos].search(te))
            throw std::runtime_error("Clave duplicada");
        table[pos].insert(TableEntry<V>(key, value));
        n++;
    }

    V search(std::string key) {
        int pos = h(key);
        TableEntry<V> te(key);
        if (!table[pos].search(te))
            throw std::runtime_error("Clave no encontrada");
        return table[pos].search(te).value;
    }

    V remove(std::string key) {
        int pos = h(key);
        TableEntry<V> te(key);
        if (!table[pos].search(te))
            throw std::runtime_error("Clave no encontrada");
        V val = table[pos].search(te).value;
        table[pos].remove(te);
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

    friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &th) {
        for (int i = 0; i < th.max; i++) {
            out << i << ": " << th.table[i] << "\n";
        }
        return out;
    }
};

#endif


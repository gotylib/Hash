#pragma once
#include <iostream>;
#include <string>
#include <vector>
#include <list>

using namespace std;

template <typename Key, typename Value>
class HashTable {
private:
    class ListNode {
    public:
        Key* key;
        Value* value;
        ListNode(Key* key = nullptr, Value* value = nullptr) : key(key), value(value) {}
        ~ListNode() {
            delete key;
            delete value;
        }
    };
    vector<ListNode> table;
    int capacity;
    int size;

    int hash(const Key& key) {
        if constexpr (std::is_same_v<Key, std::string>) {
            return std::hash<std::string>{}(key) % capacity;
        }
        else {
            return std::hash<Key>{}(key) % capacity;
        }
    }

    void rehash() {
        long oldCapacity = capacity;
        capacity *= 2;
        vector<ListNode> newTable(capacity);
        for (size_t i = 0; i < oldCapacity; i++) {
            if (table[i].key != nullptr) {
                long index = hash(*table[i].key);
                newTable[index].key = new Key(*table[i].key);
                newTable[index].value = new Value(*table[i].value);
            }
        }
        table = std::move(newTable);
    }

public:
    HashTable(int capacity = 10) : capacity(capacity), size(0) {
        table.resize(capacity);
    }

    void insert(const Key& key, const Value& value) {
        size_t index = hash(key);
        if (table[index].key == nullptr) {
            table[index].key = new Key(key);
            table[index].value = new Value(value);
        }
        else {
            index++;
            while(table[index].key != nullptr) {
                index++;
                if (index = capacity - 1) {
                    break;
                }
            }
            if (index = capacity - 1) {
                rehash();
                index = hash(key);
                table[index].key = new Key(key);
                table[index].value = new Value (value);
            }
        }
        size++;

        if (static_cast<double>(size) / capacity >= 0.7) {
            rehash();
        }
    }

    Value show(const Key& key) {
        size_t index = hash(key);
        if (*table[index].key == key) {
            return *table[index].value;
        }
        else {
            index++;
            while (*table[index].key != key)
            {
                index ++;
                if (index == capacity - 1) {
                    break;
                }
            }
            if (index == capacity - 1) {
                cout << "Element isn't found" << endl;
                return Value();
            }
            else {
                return *table[index].value;
            }
        }
    }
};
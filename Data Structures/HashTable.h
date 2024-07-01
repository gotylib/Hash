#pragma once
#include <iostream>;
#include <vector>
#include <list>

using namespace std;

template <typename Key, typename Value>
class HashTable {
private:
    class ListNode {
    public:
        Key key;
        Value value;
        ListNode(const Key& key, const Value& value) : key(key), value(value), next(nullptr) {}
        ListNode* next;
    };
    vector<list<ListNode>> table;
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
        capacity = capacity * 2;
        vector<list<ListNode>> newTable(capacity * 2);
        for (size_t i = 0; i < oldCapacity; i++) {
            for (ListNode ln : table[i]) {
                size_t newIndex = hash(ln.key);
                newTable[newIndex].push_back(ln);
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

        table[index].push_back(ListNode(key, value));
        size++;

        if (static_cast<double>(size) / capacity >= 0.7) {
            rehash();
        }
    }

    Value show(const Key& key) {
        size_t index = hash(key);
        for (ListNode ln : table[index]) {
            if (ln.key == key) {
                return ln.value;
            }
        }
        cout << "Element isn't found" << endl;
        return Value();
    }
};
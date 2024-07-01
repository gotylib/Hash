//#include "HashTable.h"
#include "HashTableWithOpenAddressing.h"
#include "trie-Tree.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;


int main() {
    Trie trie;

    trie.insert("apple");
    trie.insert("banana");
    trie.insert("orange");

    std::cout << trie.search("apple") << std::endl;   // Output: 1 (true)
    std::cout << trie.search("banana") << std::endl;  // Output: 1 (true)
    std::cout << trie.search("orange") << std::endl;  // Output: 1 (true)
    std::cout << trie.search("grape") << std::endl;   // Output: 0 (false)

    std::cout << trie.startsWith("app") << std::endl;     // Output: 1 (true)
    std::cout << trie.startsWith("ban") << std::endl;     // Output: 1 (true)
    std::cout << trie.startsWith("ora") << std::endl;     // Output: 1 (true)
    std::cout << trie.startsWith("gr") << std::endl;      // Output: 0 (false)

    return 0;
}
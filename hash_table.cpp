#include <iostream>
#include "doubly_list.cpp"

class Varchar {
private:
    std::string value;
    unsigned int length;
public:
    Varchar(unsigned int length) : value(length, ' '), length(length) {}
};

template <typename KeyType, typename ValueType> class HashTable {
private:
    struct Entry {
        KeyType key;
        ValueType value;

        Entry() {};

        Entry(const KeyType& key, const ValueType& value) : key(key), value(value) {}

        friend std::ostream& operator<<(std::ostream& os, const Entry& entry) {
            os << "Key: " << entry.key << ", Value: " << entry.value;
            return os;
        }
    };

    DoublyList<Entry> buckets;
    std::hash<KeyType> hashFunction;
    unsigned int size = 0;

public:
    HashTable(unsigned int initialSize = 10) : size(initialSize) {
        buckets.set_length(initialSize);
    }

    void insert(const KeyType& key, const ValueType& value) {
        buckets[hashFunction(key) % size] = Entry(key, value);
    }

    void print() {
        buckets.print();
    }

};

int main() {
    
    HashTable<std::string, int> hashTable;

    hashTable.insert("apple", 5);
    hashTable.insert("appleqq", 10);
    hashTable.print();
    
    return 0;
}

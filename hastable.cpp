#include <iostream>
#include <stdexcept>
#include <string>

using T = std::string;

template<class T>
class hashtable {

    struct node {
        int hash;
        std::string key;
        T value;
    };

public:

    bool empty() const {
        return size_ == 0;
    }

    int size() const {
        return size_;
    }

    int insert(const std::string &key, const T &value) {

        if (2 * size_ >= capacity) {
            rehash(2 * capacity + 1);
        }

        int index = hash(key);
        node *new_node = new node();
        new_node->hash = index;

        while (bucket[index % capacity] != nullptr) {
            ++index;
        }

        new_node->key = key;
        new_node->value = value;

        bucket[index % capacity] = new_node;
        size_++;

        return index % capacity;
    }

    void erase(const std::string &key) {
        // erases elements
    }

    const T &at(const std::string &key) const {

        const int index = hash(key);

        for (int i = 0; i < capacity; ++i) {

            node *cursor = bucket[(index + i) % capacity];

            if (cursor != nullptr and cursor->key == key) {

                return cursor->value;
            }
        }

        throw std::runtime_error("key not found");
    }

    T &at(const std::string &key) {

        const int index = hash(key);

        for (int i = 0; i < capacity; ++i) {

            node *cursor = bucket[(index + i) % capacity];

            if (cursor != nullptr and cursor->key == key) {

                return cursor->value;
            }
        }

        throw std::runtime_error("key not found");
    }

    bool contains(const std::string &key) const {

        const int index = hash(key);

        for (int i = 0; i < capacity; ++i) {

            node *cursor = bucket[(index + i) % capacity];

            if (cursor != nullptr and cursor->key == key) {

                return true;
            }
        }

        return false;
    }

    void rehash(int new_capacity) {

        node **new_bucket = new node*[new_capacity];
        for (int i = 0; i < capacity; ++i) {

            if (bucket[i] == nullptr) {
                continue;
            }

            int index = bucket[i]->hash;

            while (new_bucket[index % new_capacity] != nullptr) {
                ++index;
            }

            new_bucket[index % new_capacity] = bucket[i];
        }

        delete[] bucket;
        bucket = new_bucket;
        capacity = new_capacity;

    }

private:

    int hash(const std::string &key) const {

        int c = 0;

        for (int i = 0; i < key.size(); ++i) {
            c = c + key[i] * i;
        }

        return c;

    }

    node **bucket = nullptr;
    int capacity = 0;

    int size_ = 0;
};

struct song {
    int duration = 0;
    int playtime = 0;
};

int main() {

    std::ios::sync_with_stdio(false);

    hashtable<song> hashtable;

    int size;
    std::cin >> size;

    hashtable.rehash(size);

    std::string command;

    while (command != "END") {
        std::cin >> command;

        if (command == "ADD") {

            std::string name;
            std::cin >> name;

            song song;
            std::cin >> song.duration;

            int index = hashtable.insert(name, song);
            std::cout << name << ' ' << index << '\n';

        }

        else if (command == "PLAY") {

            std::string name;
            std::cin >> name;

            song& song = hashtable.at(name);
            song.playtime = song.playtime + song.duration;

            std::cout << name << ' ' << song.playtime << '\n';
        }

        else if (command == "TIME") {

            std::string name;
            std::cin >> name;

            song& song = hashtable.at(name);

            std::cout << name << ' ' << song.playtime << '\n';

        }
    }

    return 0;

}
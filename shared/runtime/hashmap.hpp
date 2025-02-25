#pragma once

#pragma optimize("", on)

#include <vector>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <stdexcept>

namespace SPDB {

    struct key{
        int i;
        int j;
    };

    class HashNode {
    public:
        int _value = 0;
        int _key = -1;

        HashNode() = default;

        explicit HashNode(const int& key, const int& value) {
            this->_key = key;
            this->_value = value;
        }

        HashNode(const HashNode& source) {
            this->_value = source._value;
            this->_key = source._key;
        };
    };

    uint_fast64_t loadFactor, startDepth;

    class HashMap {
    public:

        std::vector<std::vector<SPDB::HashNode>> table;
        int *usage = nullptr;

        explicit HashMap(uint_fast64_t load_factor, uint_fast64_t start_depth) {
            SPDB::loadFactor = load_factor;
            SPDB::startDepth = start_depth;

            this->usage = new int[load_factor]{0};

            this->table.resize(load_factor);

            for (int i = 0; i < load_factor; ++i) {
                this->table[i].resize(start_depth);
                this->table[i].reserve(start_depth * 2);
            }
        }

        [[maybe_unused]] int put(struct key &key, int &value) {

            for (int c = ((key.j)%(SPDB::startDepth)); c < table[key.i].size();c++){
                if(table[key.i][c]._key == -1){
                   table[key.i][c]._value += value; 
                   table[key.i][c]._key = key.j;
                   return 0;
                }
            }

            int prev_size = table[key.i].size();
            table[key.i].resize(prev_size*2);
            table[key.i][prev_size]._value += value; 
            table[key.i][prev_size]._key = key.j;      

            return 0;
        }

        [[maybe_unused]] int get(struct key &key) {
            for (int c = ((key.j)%(SPDB::startDepth)); c < table[key.i].size();c++){
                if(table[key.i][c]._key == key.j){
                    return table[key.i][c]._value;
                }
            }
            return 0;
        }
    };
}
//inventoryHash.h
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#ifndef INVENTORYHASH_H
#define INVENTORYHASH_H

class inventoryHash{

private:
        static const int t_s = 150;

        struct item{
                string item_name;
                string item_distributor;
                int item_quantity;
                int item_cost;
                item* next;
        };

        item* hash_table[t_s];
public:
        inventoryHash();
        int hashItem(string key);
        void addItem(string name);
        void addItemInfoIndex(int index,string item_name);
        void addItemInfoPtr(item *ptr, string item_name);
        void printHashTable();
        //void sort_vectors(vector<string> vect1, vector<int> vect2);
};

#endif //HASHER_H

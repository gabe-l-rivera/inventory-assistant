//inventoryHash.cpp
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <limits>
#include "inventoryHash.h"

using namespace std;

/* Author: Gabe Rivera
 * Date: 
 * Purpose: 
 */

void welcomeOption1(){ // print statement for user input
        cout << "Welcome to InvenAssist!" << endl << "Please enter product name then press enter/return to enter the next product." << endl << "When you are done entering products, simply enter \"done\" to continue." << endl;
}

vector <string> enterUserData(){
        string name;
        bool finished = false;
        vector<string> product_name_list;
        while (!finished){
                getline(cin, name);
                if (name == "done")
                        finished = true;
                else
                        product_name_list.push_back(name);
        }
        return product_name_list;
}

void printVector(vector <string> v1){
        for(int i = 0; i < v1.size(); i++)
                cout << v1[i] << endl;
}

inventoryHash::inventoryHash(){ // constructor 
        for(int i = 0; i < t_s; i++){
                hash_table[i] = new item;
                hash_table[i]->item_name = "";
                hash_table[i]->item_distributor = "";
                hash_table[i]->item_quantity = 0;
                hash_table[i]->item_cost = 0;
                hash_table[i]->next = NULL;
        }
}

int inventoryHash::hashItem(string key){
        int hash = 0;
        int index;
        for(int i = 0; i < key.length(); i++){
                hash+=(int)key[i];
        }
        index = hash % t_s;
        return index;
}

void inventoryHash::addItemInfoIndex(int index, string new_item){
        hash_table[index]->item_name = new_item;
        int intInfo;
        string strInfo;
        cout << endl << "Please add the following formation for " << hash_table[index]->item_name << ":" << endl;
        cout << "Distrubutor: ";
        cin.ignore();
        getline(cin, strInfo);
        hash_table[index]->item_distributor = strInfo;
        cout << endl << "Quantity (how many units?): ";
        cin >> intInfo;
        hash_table[index]->item_quantity = intInfo;
        cout << endl << "Cost (per unit): $";
        cin >> intInfo;
        hash_table[index]->item_cost = intInfo;
}

void inventoryHash::addItemInfoPtr(item *ptr, string new_item){
        ptr->item_name = new_item;
        int intInfo;
        string strInfo;
        cout << endl <<"Please add the following formation for " << ptr->item_name << ":" << endl;
        cout << "Distrubutor: ";
         cin.ignore();
        getline(cin, strInfo);
        ptr->item_distributor = strInfo;
        cout << endl << "Quantity (how many units?): ";
        cin >> intInfo;
        ptr->item_quantity = intInfo;
        cout << endl << "Cost (per unit): $";
        cin >> intInfo;
        ptr->item_cost = intInfo;
}

void inventoryHash::addItem(string new_item){
        int index = hashItem(new_item); // word is hashed and stored in index
        for(int i = 0; i < t_s; i++){ // parse thru table
                item *ptr = hash_table[index]; //create pointer of index
                while(ptr!=NULL){
                         if(ptr->item_name.compare(new_item) == 0){ // if item names are equal, theres a douplicate
                                cout << "Duplicate item found, figure ths out later." << endl;
                                return;
                         }
                         ptr = ptr->next;
                }
        }
        if(hash_table[index]->item_name == ""){
                //cout << "new word" << endl;
                addItemInfoIndex(index, new_item);
        }else{
                cout << "new ptr" << endl;
                item *ptr = hash_table[index];
                item *n = new item;
                addItemInfoPtr(n, new_item);
                n->next = NULL;
                while(ptr->next != NULL){
                        ptr = ptr->next;
                }
                ptr->next = n;
        }
}

void inventoryHash::printHashTable(){
        //int total_cost;
        //int running_sum = 0;
        for(int i = 0; i < t_s; i++){
                if(hash_table[i]->item_name == ""){
                        //cout << "" << endl;
                }else{
                        cout << "------------------------------------------" << endl;
                        cout << "Product: " << hash_table[i]->item_name << endl << "Distributor: " << hash_table[i]->item_distributor << endl << "Quantity: " << hash_table[i]->item_quantity << " units" << endl << "Per unit cost: $" <<  hash_table[i]->item_cost << endl << "Total cost: $" << (hash_table[i]->item_quantity * hash_table[i]->item_cost) << endl;
                        //cout << "------------------------------------------" << endl;

                }
        }
}

int main(int argc, char **argv) {
        // Import data via text file
        inventoryHash h_t;
        if(argv[1] != NULL){
                ifstream file(argv[1]); // traverse through file and populate an array of the file's words
                vector <string> getLineVector;
                string str;
                while(getline(file, str)){
                        getLineVector.push_back(str);
                }
                for(int i = 0; i < getLineVector.size(); i++){
                        h_t.addItem(getLineVector[i]); // hash words in word array
                }
                h_t.printHashTable();
        }else{
        // Standard input by user
                welcomeOption1();
                vector <string> name_vector;
                name_vector = enterUserData();
                //printVector(name_vector);
                for(int i = 0; i < name_vector.size(); i++)
                        h_t.addItem(name_vector[i]);
                h_t.printHashTable();
        }
        return 0;
}

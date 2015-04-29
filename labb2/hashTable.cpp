#include <assert.h>
#include <iomanip>

#include "hashTable.h"

const double MAX_LOAD_FACTOR = 0.5;

//Test if a number is prime
bool isPrime( int n )
{
    if( n == 2 || n == 3 )
        return true;

    if( n == 1 || n % 2 == 0 )
        return false;

    for( int i = 3; i * i <= n; i += 2 )
        if( n % i == 0 )
            return false;

    return true;
}


//Return a prime number at least as large as n
int nextPrime( int n )
{
    if( n % 2 == 0 )
        n++;

    for(; !isPrime( n ); n += 2 );

    return n;
}


// Constructor
// IMPLEMENT
HashTable::HashTable(int table_size, HASH f)
    : size(nextPrime(table_size)), h(f), nItems(0)
{
  //  size = table_size;    avkommentera om det beh�vs
    hTable = new Item *[size];
    for(int i = 0; i < size; i ++)
    {
        hTable[i] = nullptr;
    }
}


//destructor
// IMPLEMENT
HashTable::~HashTable()
{
    Item* temp; //= new Item *[size];
    Item* temp_next;// = new Item *[size];

    for(int i = 0; i < size; i++){
        temp = hTable[i];
        while(temp != nullptr){
            temp_next = hTable[i+1];
            delete(temp);
            temp = temp_next;
        }
        hTable[i] = nullptr;
    }

}


//Return the load factor of the table
double HashTable::loadFactor() const
{
    return (double) nItems / size;
}


//Return the value associated with key
//If key does not exist in the table then NOT_FOUND is returned
// IMPLEMENT
int HashTable::find(string key) const
{
    unsigned index = h(key, size);

    while(hTable[index] != nullptr){
    //    cout << "in while" << endl;
        if(hTable[index]->key == key){
  //          cout << "key found!";
                 return hTable[index]->value;
        }
        index++;
        if(index > size)
            index = 0;
    }
    return NOT_FOUND;
}


//Insert the Item (key, v) in the table
//If key already exists in the table then change the associated value to v
//Re-hash if the table becomes 50% full
// IMPLEMENT
void HashTable::insert(string key, int v)
{
    unsigned index = h(key, size);


    while(hTable[index])
    {
        if(index > size){
            index = 0;
        }
        if(hTable[index]->key == key){
            hTable[index]->value = v;
            return;
        }
        index ++;
    }

    Item* item = new Item(key, v);
    hTable[index] = item;
    nItems++;

    if(nItems == (size/2))
        reHash();
}


//Remove Item with key
//If an Item with key belongs to the table then return true,
//otherwise, return false
// IMPLEMENT
bool HashTable::remove(string key)
{
    unsigned index = h(key, size);
    Item* item = new Item("", -1);

    while(hTable[index] != nullptr) {
        if(hTable[index]->key == key){
            delete(hTable[index]);
            hTable[index] = item;
            return true;
        }
        index ++;
    }
    return false;
}


void HashTable::display(ostream& os)
{
    if (!hTable) return;

    os << "-------------------------------\n";

    for (int i = 0; i < size; ++i)
    {
        os << setw(6) << i << ": ";

        if (!hTable[i])
        {
            os << "null" << endl;
        }
        else
        {
            string key = hTable[i]->key;

            os << "key = " << "\"" << key << "\""
               << setw(12) << "value = " << hTable[i]->value
               << "  (" << h(key,size) << ")" << endl;
        }
    }

    os << endl;
}


//Display the table to stream os
// IMPLEMENT
ostream& operator<<(ostream& os, const HashTable& T)
{
    return os;
}

//Private member functions

//Rehashing function
// IMPLEMENT
void HashTable::reHash()
{
    int temp = size;
    size = nextPrime(temp * 2);
    Item** table = hTable;
    hTable = new Item *[size];
    nItems = 0;

    for (int i = 0; i < temp; i++)
    {
        cout << "i forloopen" << endl;
        if(table[i] != nullptr)
        {
            cout << "i if" << i << endl;
            insert(table[i]->key, table[i]->value);
        }
    }
    delete[] table;
}
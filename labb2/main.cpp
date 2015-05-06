#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <stdio.h>
#include <ctype.h>

#include "hashTable.h"

using namespace std;

//A simple hash function
unsigned my_hash(string s, int tableSize)
{
    unsigned hashVal = 0;

    for(unsigned i = 0; i < s.length(); i++)
        hashVal += s[i];

    hashVal %= tableSize;

    return hashVal;
}

bool isNotAlpha(char c)
{
    if(c >= 'a' && c <= 'z')
    {
        return false;
    }
    else
        return true;
}

int main()
{

    const int TABLE_SIZE = 7;

    string textfile = "test_file1.txt";
    string line;
    ifstream inFile;
    bool isAlpha;
    HashTable table(TABLE_SIZE, my_hash);

    // L�sa in fr�n en textfil
    inFile.open(textfile.c_str());

    if(!inFile)
    {
        cout << "could not read file!";
        return 0;
    }


    while(inFile >> line)
    {
        // Ta bort punkt och skit & gjort till lowercase
        transform(line.begin(), line.end(), line.begin(), ::tolower);
        line.erase(remove_if(line.begin(), line.end(), isNotAlpha), line.end());

        // Loopa igenom och l�gg in i hashable
        table[line]++;
    }

    table.display(cout
    //cout << table << endl;

    // Skriv ut i loggen

    return 0;
}
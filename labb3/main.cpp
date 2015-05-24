/**********************************************
* File: main.cpp                              *
* Author: Aida Nordman                        *
* Course: TND004, Lab 3                       *
* Date: VT2, 2015                             *
* Description: frequency table                *
* DO NOT MODIFY                               *
***********************************************/

#include "threaded_BST.h"
#include "BiIterator.h"

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

string SYMB = "(.,'!?:\"();\\)";

/*******************************
* 2. Main function             *
********************************/
bool isNotAlnum(char c){

    for(int i = 0; i < SYMB.size(); i++){
        if(c == SYMB[i])
            return true;
    }

    return false;

}

int main()
{
    MAP table;

    vector<string> find_one;

    string name, s;
    int count = 0;
    /******************************************************
    * PHASE 0: Load the words in the text file            *
    *          into a the table                           *
    *******************************************************/

//    cout << "File name? ";
//    getline(cin, name);
  //  name = "/Users/cecilialagerwall/Documents/Skola/TND004/labb3/mesg.txt";
  name = "mesg.txt";
    ifstream textFile(name);

    if (!textFile)
    {
        cerr << "Text file could not be opened!!" << endl;
        exit(1);
    }

    cout << "Loading the words from " << name << " ...\n";

    //Read words and load them in the table
    while (textFile >> s)
    {
        //remove non-alphanumeric chars
        s.erase(remove_if(s.begin(), s.end(), isNotAlnum), s.end());
        //convert to lower-case letters
        transform(s.begin(), s.end(), s.begin(), ::tolower);

        if (!s.size()) continue; //skip numbers and punctuation signs
        table[s].second++;  //if s is not in the table then it is inserted

        count++;
    }


    /******************************************************
    * PHASE 1: Display                                    *
    * - number of words in the text                       *
    * - number of unique words (occurring only once)      *
    * - frequency table                                   *
    *******************************************************/

    cout << "Number of words in text: " << count << endl <<
    "Number of unique words in text: " << table.size() << endl;
        BiIterator it = table.begin();

    cout << "Frequency table sorted alphabetically..." << endl << endl
            << setw(15) << "KEY" << setw(10) << "" << "COUNTER" << endl
            << "=================================" << endl;
    while(it != table.end())
    {
        cout << setw(15) << right << it->first
             << setw(15) << it->second << endl;

        if (it->second == 1)
        {
            find_one.push_back(it->first);
        }

        it++;
    }


    /******************************************************
    * PHASE 3: remove all words with counter 1            *
    *          and display table again                    *
    *******************************************************/
//
//    string wait;
//    getline(cin, wait);

   // ADD CODE
    for (int i = 0; i < find_one.size(); i++)
    {
        table.remove(find_one.at(i));
    }

    cout << endl << endl;
    it = table.begin();

    cout << "Removed all words with counter = 1" << endl << endl
    << setw(15) << "KEY" << setw(10) << "" << "COUNTER" << endl
    << "=================================" << endl;
    while(it != table.end())
    {
        cout << setw(15) << right << it->first
        << setw(15) << it->second << endl;

        it++;
    }




    /***********************************************************
    * PHASE 4: request two words to the user w1 and w2         *
    *          then display all words in the interval [w1,w2]  *
    ************************************************************/

   string w1, w2;
   cout << "enter w1: ";
   cin >> w1;
   cout << "enter w2: ";
   cin >> w2;
   if(w1>w2)
   {
       string temp = w1;
       w1 = w2;
       w2 = temp;
   }
   if(w1 == w2)
   {
       cout << "the words are the same" << endl;
      // cout << "No words between " << w1 << "and " << w2 << endl;
   }
   else
   {
       it = table.begin();
       cout << "All words between " << w1 <<" and " << w2 << endl << endl
        << setw(15) << "KEY" << setw(10) << "" << "COUNTER" << endl
        << "=================================" << endl;
       while(it != table.end())
       {
           if(it->first > w1 && it->first < w2)
           {
               cout << it->first << endl;
           }
           it++;
       }
   }
    return 0;
}

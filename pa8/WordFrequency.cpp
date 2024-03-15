/***
* Amrita Pasupuleti
* apasupul
* 2024 Winter CSE101 PA8
* WordFrequency.cpp
* places words and their frequencies in a dictionary ADT with a red black tree
***/

#include <fstream>
#include "Dictionary.h"

using namespace std;

int main(int argc, char* argv[]) {
    // check arguments
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return EXIT_FAILURE;
    }
    
    // open input and output files
    ifstream in;
    in.open(argv[1]);
    if (!in.is_open()) {
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return EXIT_FAILURE;
    }
    ofstream out;
    out.open(argv[2]);
    if (!out.is_open()) {
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return EXIT_FAILURE;
    }


    string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";
    size_t begin, end, len;
    string line, key;

    Dictionary D;

    while (getline(in, line)) {
        len = line.length();
        // get first token
        begin = min(line.find_first_not_of(delim, 0), len);
        end = min(line.find_first_of(delim, begin), len);
        key = line.substr(begin, (end - begin));
        // convert to lowercase
        while (key != "") {
            for (size_t i = 0; i < key.length(); i++) {
                key[i] = tolower(key[i]);
            }
            // add to dict
            if (D.contains(key)) {
                D.getValue(key)++;
            }
            else {
                D.setValue(key, 1);
            }
            // get next token
            begin = min(line.find_first_not_of(delim, (end + 1)), len);
            end = min(line.find_first_of(delim, begin), len);
            key = line.substr(begin, (end - begin));
        }
    }

    out << D << endl;
    
    in.close();
    out.close();
    D.clear();

    return EXIT_SUCCESS;
}
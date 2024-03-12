/***
* Amrita Pasupuleti
* apasupul
* 2024 Winter CSE101 PA7
* Order.cpp
* reads strings from an input file and places them into a dictionary
***/

#include <iostream>
#include<fstream>
#include<string>
#include<stdexcept>

#include "Dictionary.h"

using namespace std;

int main(int argc, char* argv[]){
    //check arguments
	if(argc != 3){
		cerr << "Usage: ./Order <input file> <output file>" << endl;
    	exit(EXIT_FAILURE);
    }

    fstream in;
    in.open(argv[1], ios::in);
    if( !in.is_open() ){
      cerr << "Unable to open file " << argv[1] << " for reading" << endl;
      return(EXIT_FAILURE);
   }

    fstream out;
    out.open(argv[2], ios::out);
    if( !out.is_open() ){
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return(EXIT_FAILURE);
    }

    Dictionary D;
    string s = "";
    int i = 1;
    while (getline(in, s)){
    	D.setValue(s, i);
    	i++;
    }
    out << D.to_string() << endl;
    out << D.pre_string() << endl;

    in.close();
    out.close();
    D.clear();
    return 0;
}
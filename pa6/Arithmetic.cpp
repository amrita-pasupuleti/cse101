/***
* Amrita Pasupuleti
* apasupul
* 2024 Winter CSE101 PA6
* Arithmetic.cpp
* performs arithmetic operations on arbitrarily large signed integers
***/ 


#include<iostream>
#include<fstream>
#include<string>
#include<stdexcept>

#include"BigInteger.h"

using namespace std;

int main(int argc, char* argv[]){
	if(argc != 3){
		cerr << "Usage: ./Arithmetic.cpp <input file> <output file>" << endl;
    	exit(EXIT_FAILURE);
    }

    fstream in;
    in.open(argv[1], ios::in);
    if (!in.is_open()){
    	cerr << "Unable to open input file:" << argv[1] << endl;
    	exit(EXIT_FAILURE);
    }

    fstream out;
    out.open(argv[2], ios::out);
    if (!out.is_open()){
    	cerr << "Unable to open output file:" << argv[2] << endl;
    	exit(EXIT_FAILURE);
    }

    string str1; 
    string str2;
    in >> str1;
    in >> str2;
    BigInteger A = str1;
    BigInteger B = str2;

    // A
    out << A << endl << endl;
    // B
    out << B << endl << endl;
    // A+B
    out << A+B << endl << endl;
    // A-B
    out << A-B << endl << endl;
    // A-A
    out << A-A << endl << endl;
    // 3A-2B
    out << 3*A-2*B << endl << endl;
    // AB
    out << A*B << endl << endl;
    // A^2
    out << A*A << endl << endl;
    // B^2
    out << B*B << endl << endl;
    // 9A^4+16B^5
    out << (A*A*A*A)*9+(B*B*B*B*B)*16 << endl << endl;

    in.close();
    out.close();

    return 0;
}
/***
* Amrita Pasupuleti
* apasupul
* 2024 Winter CSE101 PA5
* Shuffle.cpp
* shuffles a list until it matches the original list
***/ 

#include <stdexcept>
#include <iomanip>

#include "List.h"

using namespace std;

void shuffle (List &L) {
    List A, B;
    int lngth = L.length();

    //split list
    L.moveFront();
    while(L.position() < lngth/2) {
        A.insertBefore(L.moveNext());
    }
    while(L.position() < lngth) {
        B.insertBefore(L.moveNext());
    }

    //clear list
    L.clear();

    //insert a and b back into list
    A.moveFront();
	B.moveFront();
	while (A.position() != A.length() || B.position() != B.length()) {
		if (B.position() != B.length()) {
            int b = B.peekNext();
			L.insertBefore(b);
			B.moveNext();
		}
		if (A.position() != A.length()) {
            int a = A.peekNext();
			L.insertBefore(a);
			A.moveNext();
		}
	}
}

int main(int argc, char * argv[]) {
    // check command line for correct number of arguments
    if ( argc != 2 ){
        cerr << "Usage: " << argv[0] << "<positive integer specifying max number of cards>" << endl;
        return(EXIT_FAILURE);
    }
    int num = stoi(argv[1]);
    if (num <= 0) {
        throw invalid_argument("Argument invalid: n must be a positive integer");
    }

    //print first two lines
    cout << "deck size       shuffle count" << endl;
    cout << "------------------------------" << endl;

    List Deck, L;
    int count;
    for (int size = 0; size < num; size++) {
        count = 0;
        //insert numbers to lists
        for (int j = 0; j < (size+1); j++) {
            Deck.insertBefore(j);
    		L.insertBefore(j);
        }
        //shuffle once
        shuffle(Deck);
        count++;
        //shuffle while not the same
        while(!(Deck == L)) {
            shuffle(Deck);
            count++;
        }

        cout << " " << size+1 << "		" << count << endl;
        Deck.clear();
        L.clear();
    }

    return 0;
}
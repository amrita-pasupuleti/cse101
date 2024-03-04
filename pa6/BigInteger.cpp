/***
* Amrita Pasupuleti
* apasupul
* 2024 Winter CSE101 PA6
* BigInteger.cpp
* creates the biginteger adt
***/ 

#include<iostream>
#include<stdexcept>
#include<string>


#include"BigInteger.h"
#include"List.h"

using namespace std;

const int POWER = 9;
const long BASE = 1000000000;

// Class Constructors & Destructors ----------------------------------------

BigInteger::BigInteger() {
    signum = 0;
    digits = List();
}

BigInteger::BigInteger(long x) {
	if (x == 0) {
        signum = 0;
        digits.insertAfter(0);
        return;
    }

    if (x < 0) {
        signum = -1;
        x = -x;
    } 
    else {
        signum = 1;
    }
	long i = x % BASE;
	while (i > 0) {
		digits.insertAfter(i);
		x = x / BASE;
		i = x % BASE;
	}
}

BigInteger::BigInteger(std::string s){
	if(s.length() == 0){
		throw std::invalid_argument("BigInteger: Constructor: empty string");
	}
	if (s[0] == '-'){
		signum = -1; 
	}
    else {
        signum = 1;
    }
    
    string chars = "";
    if (s.length() != 1) {
        chars = s.substr(1, s.length());
        for (char c : chars){
            if (!isdigit(c)){ 
                throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
            }
        }
    } 
    else if (s[0] == '+' || s[0] == '-'){
        throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
    }
    else {
        throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
    }
	

	int i = s.length() - POWER;
	while(i > 0) {
		digits.insertAfter(stol(s.substr(i, POWER)));
		i -= POWER;
	}
	
    if (i == 0){
		digits.insertAfter(stol(s.substr(i, POWER)));
	}
    else if (i < 0) {
		if (s[0] == '+' || s[0] == '-') {
			digits.insertAfter(stol(s.substr(1, i + POWER -1)));
		} 
        else {
			digits.insertAfter(stol(s.substr(0, i + POWER)));
		}
	} 

    for (digits.moveFront(); digits.peekNext() == 0 && digits.length() > 1; ) {
        digits.eraseAfter();
    }
}

BigInteger::BigInteger(const BigInteger& N){
	this->signum = N.signum; 
	this->digits = N.digits;
}

// Access functions --------------------------------------------------------
int BigInteger::sign() const{
	return this->signum;
}

int BigInteger::compare(const BigInteger& N) const {
    if (this->signum == 0 && N.signum == 0){
		return 0;
	}
    if (this->signum > N.signum){
		return 1;
    }
	if (this->signum < N.signum){
		return -1;
	} 

    List A = this->digits;
    List B = N.digits;
    if (A.length() > B.length() && this->signum == 1) {
        return 1;
    } 
    if (A.length() > B.length() && this->signum == -1) {
        return -1;
    } 
    if (A.length() < B.length() && this->signum == 1){
        return -1;
    } 
    if (A.length() < B.length() && this->signum == -1){
        return 1;
    } 

    A.moveFront();
    B.moveFront();
    while(A.position() < A.length()) {
        if(A.peekNext() > B.peekNext() && this->signum == 1){
            return 1;
        } 
        if(A.peekNext() > B.peekNext() && this->signum == -1){
            return -1;
        }
        if (A.peekNext() < B.peekNext() && this->signum == 1){
            return -1;
        }
        if (A.peekNext() < B.peekNext() && this->signum == -1){
            return 1;
        }
        A.moveNext();
        B.moveNext();
    }
    return 0;
}

// Manipulation procedures -------------------------------------------------
void BigInteger::makeZero() {
    digits.clear();
    signum = 0;
}

void BigInteger::negate() {
    signum *= -1;
}

// BigInteger Arithmetic operations ----------------------------------------
BigInteger BigInteger::add(const BigInteger& N) const {
    BigInteger X = *this;
    BigInteger Y = N;
    
    if (X > Y) {
        return Y.add(X);
    }

    if (X.sign() == 1 && Y.sign() == -1) {
        Y.negate();
        return X.sub(Y);
    } 
    if (X.sign() == -1 && Y.sign() == 1) {
        X.negate();
        return Y.sub(X);
    } 
    if (X.sign() == -1 && Y.sign() == -1) {
        X.negate();
        Y.negate();
        BigInteger res = X.add(Y);
        res.negate();
        return res;
    }

    BigInteger Res; 
    List x = X.digits; 
    List y = Y.digits;

    long carry = 0;
    long temp = 0;
    x.moveBack();
    y.moveBack();
    while (x.position() > 0 && y.position() > 0) {
        temp = carry + x.peekPrev() + y.peekPrev();
        Res.digits.insertAfter(temp%BASE);
        carry = temp / BASE;

        x.movePrev();
        y.movePrev();
    }
    while (y.position() > 0) {
        temp = carry + y.peekPrev();
        Res.digits.insertAfter(temp%BASE);
        carry = temp / BASE;

        y.movePrev();
    }
    if (carry > 0) {
        Res.digits.insertAfter(carry);
    }

    Res.signum = 1;
    return Res;
}

BigInteger BigInteger::sub(const BigInteger& N) const {
    BigInteger X = N;
    BigInteger Y = *this;
    BigInteger Res;

    if (X == Y) {
        return Res;  
    }
    if (X < Y) {
        Res = X.sub(Y);
        Res.negate();
        return Res;  
    }
    if (X.sign() == -1 && Y.sign() == -1) {
        X.negate();
        Y.negate();
        Res = Y.sub(X);
        Res.negate();
        return Res;  
    }
    if (X.sign() == -1 && Y.sign() == 1) {
        Y.negate();
        Res = X.add(Y);
        Res.negate();
        return Res;  
    }
    if (X.sign() == 1 && Y.sign() == -1) {
        X.negate();
        Res = X.add(Y);
        return Res;  
    }
    
    List x = X.digits;
    List y = Y.digits;

    long dist = 0;
    long temp = 0;
    x.moveBack();
    for (y.moveBack(); y.position() > 0; y.movePrev()) {
        if (x.peekPrev() - dist >= y.peekPrev())  {
            temp = x.peekPrev() - y.peekPrev() - dist;
            if (!(x.peekPrev() < -1)) {
                dist = 0;
            }
        }
        else if (x.peekPrev() - dist < y.peekPrev()) {
            temp = x.peekPrev() + BASE - y.peekPrev() - dist;
            dist = 1;
        } 
        Res.digits.insertAfter(temp);
        x.movePrev();
    }
    while (x.position() > 0) {
        if (x.peekPrev() - dist >= 0) {
            temp = x.peekPrev() - dist - 0;
            if (!(x.peekPrev() <= 0)) {
                dist = 0;
            }
        }
        else if (x.peekPrev() - dist < 0) {
            temp = x.peekPrev() + BASE - 0 - dist;
            dist = 1;
        } 
        Res.digits.insertAfter(temp);
        x.movePrev();
    }
    Res.digits.moveFront();
    while (!Res.digits.peekNext() && Res.digits.length() > 0) {
        Res.digits.eraseAfter();
    }
    Res.signum = -1;  
    return Res;
}

//helper function for mult
List scalarMultList(long s, List *l, int* num) {
    List L;
    long carry = 0;
    long temp = 0;

    for (l->moveBack(); l->position() > 0; l->movePrev()) {
        temp = l->peekPrev() * s + carry;
        L.insertAfter(temp%BASE);

        carry = temp / BASE;
    }
    if (carry > 0) {
        L.insertAfter(carry);
    }

    L.moveBack();
    for (int i = 0; i < *num; i++) {
        L.insertAfter(0);
    }
    return L;
}

BigInteger BigInteger::mult(const BigInteger& N) const {
    BigInteger X = *this;
    BigInteger Y = N;
    BigInteger Res;
    
    List x = X.digits;
    List y = Y.digits;

    int num = 0;
    x.moveBack();
    for (y.moveBack(); y.position() > 0; y.movePrev()) {
        List temp = scalarMultList(y.peekPrev(), &x, &num);  

        BigInteger Temp;
        Temp.signum = 1;
        Temp.digits = temp;
        Res = Res.add(Temp);  
        num++;
    }

    Res.signum = Y.signum * X.signum;  
    return Res;
}



// Other Functions ---------------------------------------------------------
std::string BigInteger::to_string() {
	if (signum == 0){
		return "0";
	} 

    string res = "";
    //if negative
    if (signum == -1){
		res += "-";
	}

	for (digits.moveFront(); digits.position() < digits.length(); digits.moveNext()) {
		string zeros = "";
        string temp = std::to_string(digits.peekNext());

		while((zeros.length() + temp.length()) < POWER && digits.position() > 0){
			zeros += "0";
		}
		res += zeros + temp;
	}
	return res;
}


// Overriden Operators -----------------------------------------------------
std::ostream& operator<<( std::ostream& stream, BigInteger N ){
	return stream << N.BigInteger::to_string();
}

bool operator==( const BigInteger& A, const BigInteger& B ) {
    if (A.compare(B) == 0) {
        return true;
    }
    return false;
}

bool operator<( const BigInteger& A, const BigInteger& B ) {
    if (A.compare(B) == -1) {
        return true;
    }
    return false;
}

bool operator<=( const BigInteger& A, const BigInteger& B ) {
   if (A.compare(B) == -1 || A.compare(B) == 0) {
        return true;
    }
    return false;
}

bool operator>( const BigInteger& A, const BigInteger& B ) {
    if (A.compare(B) == 1) {
        return true;
    }
    return false;
}

bool operator>=( const BigInteger& A, const BigInteger& B ) {
    if (A.compare(B) == 0 || A.compare(B) == 1) {
        return true;
    }
    return false;
}

BigInteger operator+( const BigInteger& A, const BigInteger& B ) {
    return A.add(B);
} 
BigInteger operator+=( BigInteger& A, const BigInteger& B ) {
    BigInteger R = A.add(B);
    A.signum = R.signum;
    A.digits = R.digits;
    return A; 
}

BigInteger operator-( const BigInteger& A, const BigInteger& B ) {
    return A.sub(B);
}
BigInteger operator-=( BigInteger& A, const BigInteger& B ) {
    BigInteger R = A.sub(B);
    A.signum = R.signum;
    A.digits = R.digits;
    return A; 
}

BigInteger operator*( const BigInteger& A, const BigInteger& B ) {
    return A.mult(B);
}
BigInteger operator*=( BigInteger& A, const BigInteger& B ) {
    BigInteger R = A.mult(B);
    A.signum = R.signum;
    A.digits = R.digits;
    return A; 
}
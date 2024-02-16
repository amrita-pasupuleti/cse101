/***
* Amrita Pasupuleti
* apasupul
* 2024 Winter CSE101 PA5
* List.cpp
* creates List ADT
***/ 

#include<cstring>
#include<stdexcept>

#include"List.h"

using namespace std;

// Class Constructors & Destructors ----------------------------------------
//node
List::Node::Node(ListElement x) {
    data = x;
    next = nullptr;
    prev = nullptr;
}

//new list
List::List() {
    frontDummy = new Node(0);
    backDummy = new Node(0);
    beforeCursor = frontDummy;
    afterCursor = backDummy;
	frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    pos_cursor = 0;
    num_elements = 0;
}

//copy constructor
List::List(const List& L) {
    frontDummy = new Node(0);
    backDummy = new Node(1);
    beforeCursor = frontDummy;
	afterCursor = backDummy;
	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;
	pos_cursor = 0;
	num_elements = 0;

	Node* N = L.frontDummy->next;
	while(N != L.backDummy){
		this->insertBefore(N->data);
		N = N->next;
	}
	this->moveFront();

}

//destructor
List::~List() {
    clear();
    delete frontDummy;
    delete backDummy;
}

// Access functions --------------------------------------------------------
int List::length() const {
	return num_elements;
}

ListElement List::front() const {
	if(length() <= 0){
		throw std::length_error("List: front(): empty list");
	}
	return frontDummy->next->data;
}

ListElement List::back() const {
	if(length() <= 0){
		throw std::length_error("List: back(): empty list");
	}
	return backDummy->prev->data;
}

int List::position() const {
	return pos_cursor;
}

ListElement List::peekNext() const {
	if (position() >= length()){
		throw std::range_error("List: peekNext(): cursor at back");
	}
	return afterCursor->data;
}

ListElement List::peekPrev() const {
	if (position() <= 0){
		throw std::range_error("List: peekPrev(): cursor at front");
	}
	return beforeCursor->data;
}

// Manipulation procedures -------------------------------------------------
void List::clear() {
    moveFront();
    while (length() > 0) {
        eraseAfter();
    }
}

void List::moveFront() {
    pos_cursor = 0;
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
}

void List::moveBack() {
   afterCursor = backDummy;
   beforeCursor = backDummy->prev;
   pos_cursor = num_elements;
}

ListElement List::moveNext() {
   if (position() > length()) {
      throw range_error("List: moveNext(): cursor at front");
   }
   beforeCursor = beforeCursor->next;
   afterCursor = afterCursor->next;
   pos_cursor++;
   return beforeCursor->data;
}

ListElement List::movePrev() {
    if (position() < 0) {
      throw range_error("List: movePrev(): cursor at front");
    }
    beforeCursor = beforeCursor->prev;
    afterCursor = afterCursor->prev;
    pos_cursor--;
    return afterCursor->data;
}

void List::insertAfter(ListElement x) {
	Node* N = new Node(x);
	N->next = afterCursor;
	N->prev = beforeCursor;
	beforeCursor->next = N;
	afterCursor->prev = N;
	afterCursor = N;
	num_elements++;
}

void List::insertBefore(ListElement x) {
	Node* N = new Node(x);
	N->next = afterCursor;
	N->prev = beforeCursor;
	beforeCursor->next = N;
	afterCursor->prev = N;
	beforeCursor = N;
	num_elements++;
	pos_cursor++;
}

void List::setAfter(ListElement x){
	if (pos_cursor > length()) {
      throw range_error("List: setAfter(): cursor at back");
   }
   afterCursor->next->data = x;
}

void List::setBefore(ListElement x) {
   if (pos_cursor < 0) {
      throw range_error("List: setBefore(): cursor at front");
   }
   beforeCursor->prev->data = x;
}

void List::eraseAfter() {
	if(position() >= length()) {
		throw std::range_error("List: eraseAfter(): cursor at back");
	} 	
	Node* N = afterCursor;
	afterCursor = afterCursor->next;
	beforeCursor->next = afterCursor;
	afterCursor->prev = beforeCursor;
	delete N; 
	num_elements--;
}

void List::eraseBefore() {
	if(position() <= 0) {
		throw std::range_error("List: eraseBefore(): cursor at front");
	} 	
	Node* N = beforeCursor;
	beforeCursor = beforeCursor->prev;
	afterCursor->prev = beforeCursor;
	beforeCursor->next = afterCursor;
	delete N; 
	num_elements--;
	pos_cursor--;
}


// Other Functions ---------------------------------------------------------

int List::findNext(ListElement x) {
    while(afterCursor != backDummy) {
		if (afterCursor->data == x) {
			this->moveNext();
			return position();
		}
		this->moveNext();
	}
	return -1;
}

int List::findPrev(ListElement x) {
	while(beforeCursor != frontDummy) {
		if (beforeCursor->data == x) {
			this->movePrev();
			return position();
		}
		this->movePrev();
	}
	return -1;
}

void List::cleanup() {
	int temp = 0, count = 0, saveCursor = pos_cursor; 
	for (Node* N = frontDummy->next; N != backDummy; moveNext()) {
		moveFront();
		findNext(N->data);
		while (temp != -1 && N->next != backDummy) {
			temp = findNext(N->data);
			if (pos_cursor <= saveCursor){
				saveCursor--;
			}
			if (temp != -1){
				eraseBefore();
			}
		}
		N = frontDummy->next;
		count++;
		for (temp = 0; temp < count; ++temp) {
			N = N->next;
		}
	}
	moveFront();
	for (temp = 0; temp < saveCursor; ++temp) {
		moveNext();
	}
}

List List::concat(const List& L) const {
	List K;
	Node* N = this->frontDummy->next;
	Node* M = L.frontDummy->next;
	while(N != this->backDummy){
		K.insertBefore(N->data);
		N = N->next;
	}
	while(M != L.backDummy){
		K.insertBefore(M->data);
		M = M->next;
	}
	K.moveFront();
	return K;
}

std::string List::to_string() const {
    std::string s = "(";
    Node* N = nullptr;
    for (N = frontDummy->next; N != backDummy->prev; N = N->next) {
        s += std::to_string(N->data) + ", ";
    }
    s += std::to_string(N->data);
    s += ")";
    return s;
}

bool List::equals(const List& R) const {
	bool eq = false;
	Node* N = nullptr;
	Node* M = nullptr;

	eq = (this->length() == R.length());
	N = this->frontDummy->next;
	M = R.frontDummy->next;
	while (eq && N != this->backDummy) {
		eq = (N->data==M->data);
		N = N->next;
		M = M->next;
	}
	return eq;
}

// Overriden Operators -----------------------------------------------------
std::ostream& operator<<( std::ostream& stream, const List& L ) {
	return stream << L.List::to_string();
}


bool operator==( const List& A, const List& B ) {
   return A.List::equals(B);
} 

List& List::operator=(const List& L) {
    if (this != &L) {
      List temp = L;
      swap(frontDummy, temp.frontDummy);
      swap(backDummy, temp.backDummy);
	  swap(beforeCursor, temp.beforeCursor);
      swap(afterCursor, temp.afterCursor);
      swap(num_elements, temp.num_elements);
      swap(pos_cursor, temp.pos_cursor);
    }
    return *this;
}
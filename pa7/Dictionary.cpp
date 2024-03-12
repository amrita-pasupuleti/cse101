/***
* Amrita Pasupuleti
* apasupul
* 2024 Winter CSE101 PA7
* Dictionary.cpp
* creates a dictionary ADT using a binary search tree
***/

#include<iostream>
#include<string>
#include<stdexcept>

#include "Dictionary.h"

using namespace std;

// Helper Functions (Optional) ---------------------------------------------
void Dictionary::inOrderString(std::string& s, Node* R) const{
	if (R != nil) {
		inOrderString(s, R->left);
		s.append(R->key + " : " + std::to_string(R->val) + "\n");
		inOrderString(s, R->right);
	}
}

void Dictionary::preOrderString(std::string& s, Node* R) const{
	if(R != nil){
		s.append(R->key + "\n");
		preOrderString(s, R->left);
		preOrderString(s, R->right);
	}
}

void Dictionary::preOrderCopy(Node* R, Node* N) {
    if (R != N) {
        setValue(R->key, R->val);
        preOrderCopy(R->left, N);
        preOrderCopy(R->right, N);
    }
}

void Dictionary::postOrderDelete(Node* R){
	if (R != nil){
		postOrderDelete(R->left);
		postOrderDelete(R->right);

		delete R;
		num_pairs--;
	}
}

Dictionary::Node* Dictionary::search(Node* R, keyType k) const {
	if (R == nil){
		return nil;
	} 
    else if (k == R->key){
		return R;
	} 
    else if (k < R->key){
		return search(R->left, k);
	} 
    else if (k > R->key){
		return search(R->right, k);
	}
	return nil;
}

Dictionary::Node* Dictionary::findMin(Node* R){
	if (R == nil) {
		throw logic_error("Dictionary: findMin(): root is nil");
	}
	while (R->left != nil){
		R = R->left;
	}
	return R;
}

Dictionary::Node* Dictionary::findMax(Node* R){
	if(R == nil) {
		throw logic_error("Dictionary: findMax(): root is nil");
	}
	while (R->right != nil){
		R = R->right;
	}
	return R;
}
 
Dictionary::Node* Dictionary::findNext(Node* N){
	if (N->right != nil){
		return findMin(N->right);
	} 

	Node* X = N->parent;
	while (X != nil && N == X->right) {
        N = X;
        X = X->parent;
	}
	return X;  
}

Dictionary::Node* Dictionary::findPrev(Node* N) {
    if (N->left != nil) {
        return findMax(N->left);
    }

    Node* X = N->parent;
    while (X != nil && N == X->left) {
        N = X;
        X = X->parent;
    }
    return X;
}



// Class Constructors & Destructors ----------------------------------------
Dictionary::Node::Node(keyType k, valType v){
	key = k;
	val = v;
	parent = nullptr;
    left = nullptr;
    right = nullptr;
}

Dictionary::Dictionary() {
	nil = root = current = new Node("", -1);
	num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary& D){
	nil = root = current = new Node("", -1);
	num_pairs = 0;
	preOrderCopy(D.root, D.nil);
}

Dictionary::~Dictionary(){
	clear();
	delete nil; 
}

// Access functions --------------------------------------------------------
int Dictionary::size() const {
	return num_pairs;
}

bool Dictionary::contains(keyType k) const{
	if (search(root, k) != nil) {
		return true;
	}
	return false;
}

valType& Dictionary::getValue(keyType k) const {
    if(!contains(k)){
		throw logic_error("Dictionary: getValue(): key \"" + k + "\" does not exist");
	}
	Node *N = search(root, k);
	return N->val;
}

bool Dictionary::hasCurrent() const {
	if (current != nil && current != nullptr) {
		return true;
	}
	return false;
}

keyType Dictionary::currentKey() const {
	if (!hasCurrent()) {
        throw logic_error("Dictionary: currentKey(): current undefined");
    }
	return current->key;
}

valType& Dictionary::currentVal() const {
    if (!hasCurrent()) {
        throw logic_error("Dictionary: currentVal(): current undefined");
    }
    return current->val;
}

// Manipulation procedures -------------------------------------------------
void Dictionary::clear(){
	postOrderDelete(root);
	root = nil; 
	current = nil;
	num_pairs = 0;
}

void Dictionary::setValue(keyType k, valType v){
	Node* X = root;
    Node* Y = nil;

    Node* N = new Node(k, v);
    N->left = nil;
    N->right = nil;

    while (X != nil) {
        Y = X;
		if (k == X->key) {
			X->val = v;
			delete N;
			return;
		}
		else if (k > X->key) {
            X = X->right;
        } 
        else {
            X = X->left;
        } 
    }

	num_pairs++;

    N->parent = Y;
    if (Y == nil) {
        root = N;
    } 
	else if (k < Y->key) {
        Y->left = N;
    } 
	else {
        Y->right = N;
    }
}

void Dictionary::remove(keyType k) {
    if (!contains(k)) {
        throw logic_error("Dictionary: remove(): key \"" + k + "\" does not exist");
    }

    Node* N = search(root, k);
    if (N == current) {
        current = nil;
    }
	
	if (N->left != nil && N->right != nil) {
		Node* X = findMin(N->right);
        if (X->parent != N) {
            X->parent->left = X->right;

            if (X->right != nil) {
                X->right->parent = X->parent;
            }
            X->right = N->right;
            X->right->parent = X;
        }

        if (N != root) {
			if (N->parent->left == N) {
                N->parent->left = X;
            } 
			else {
                N->parent->right = X;
            }
        } 
		else {
            root = X;
        }

        X->parent = N->parent;
        X->left = N->left;
        X->left->parent = X;
    }

	else if (N->left != nil && N->right == nil) {
		if (N == root) {
			root = N->left;
		}
		else {
			if (N->parent->left != N) {
				N->parent->right = N->left;
			}
			else {
                N->parent->left = N->left;
            }
		}
		N->left->parent = N->parent;
	}

	else if (N->left == nil && N->right != nil) {
        if (N == root) {
            root = N->right;
        } 
		else {
            if (N->parent->left != N) {
                N->parent->right = N->right;
            } 
			else {
				N->parent->left = N->right;
            }
        }
        N->right->parent = N->parent;
    }
	else {
		if (N == root) {
			root = nil;
		} 

		else {
			if (N->parent->left != N) {
				N->parent->right = nil;
			} 
			else {
				N->parent->left = nil;
			}
		}
	}

	delete N;
    num_pairs--;
}

void Dictionary::begin(){
	if (size() > 0) {
		current = findMin(root);
	}
}

void Dictionary::end() {
    if (size() > 0) {
        current = findMax(root);
    }
}

void Dictionary::next(){
	if(!hasCurrent()){
		throw logic_error("Dictionary: next(): current undefined");
	}
	if (findNext(current) == nil) {
		current = nil;
	} 
	else {
		Node* N = findNext(current);
		current = N;
	}
}

void Dictionary::prev(){
	if(!hasCurrent()){
		throw logic_error("Dictionary: prev(): current undefined");
	}
	if (findPrev(current) == nil) {
		current = nil;
	} 
	else {
		Node* N = findPrev(current);
		current = N;
	}
}

// Other Functions ---------------------------------------------------------
std::string Dictionary::to_string() const{
	string S = "";
	inOrderString(S, root);
	return S;
}

string Dictionary::pre_string() const {
    string s;
    preOrderString(s, root);
    return s;
}

bool Dictionary::equals(const Dictionary& D) const {
    if (size() != D.size()) {
        return false;
    }
	
    string s1 = to_string();
    string s2 = D.to_string();
    return s1 == s2;
}

// Overloaded Operators ----------------------------------------------------
std::ostream& operator<<( std::ostream& stream, Dictionary& D ){
	return stream << D.Dictionary::to_string();
}

bool operator==( const Dictionary& A, const Dictionary& B ){
	return A.Dictionary::equals(B);
}

Dictionary& Dictionary::operator=( const Dictionary& D ){
	if (this != &D) {
        clear();
        preOrderCopy(D.root, D.nil);
    }
    return *this;
}


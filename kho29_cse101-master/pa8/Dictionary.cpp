#include<iostream>
#include<string>
#include<cstring>
#include"Dictionary.h"

using namespace std;

Dictionary::Node::Node(keyType k, valType v){
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    color = 0;
}

// Helper Functions (Optional) ---------------------------------------------

// inOrderString()
// Appends a string representation of the tree rooted at R to string s. The
// string appended consists of: "key : value \n" for each key-value pair in
// tree R, arranged in order by keys.
void Dictionary::inOrderString(std::string& s, Node* R) const{
    if(R != nil){
        inOrderString(s,R->left);
        s += R->key;
        s += " : ";
        s += std::to_string(R->val);
        s += "\n";
        inOrderString(s,R->right);
    }
}

// preOrderString()
// Appends a string representation of the tree rooted at R to s. The appended
// string consists of keys only, separated by "\n", with the order determined
// by a pre-order tree walk.
void Dictionary::preOrderString(std::string& s, Node* R) const{
    if(R != nil){
        s += R->key;
        s += "\n";
        preOrderString(s,R->left);
        preOrderString(s,R->right);
    }
}

// preOrderCopy()
// Recursively inserts a deep copy of the subtree rooted at R into this 
// Dictionary. Recursion terminates at N.
void Dictionary::preOrderCopy(Node* R, Node* N){
    if(R != N){
        this->setValue(R->key, R->val);
        preOrderCopy(R->left, N);
        preOrderCopy(R->right, N);
    }
}

// postOrderDelete()
// Deletes all Nodes in the subtree rooted at R, sets R to nil.
void Dictionary::postOrderDelete(Node* R){
    if(R != nil){
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        delete R;
        num_pairs--;
    }
}

// search()
// Searches the subtree rooted at R for a Node with key==k. Returns
// the address of the Node if it exists, returns nil otherwise.
Dictionary::Node* Dictionary::search(Node* R, keyType k) const{
    if(R == nil || k == R->key){
        return(R);
    }else if(k < R->key){
        return(search(R->left, k));
    }else{
        return(search(R->right, k));
    }
}

// findMin()
// If the subtree rooted at R is not empty, returns a pointer to the 
// leftmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMin(Node* R){
    while(R->left != nil){
        R = R->left;
    }
    return(R);
}

// findMax()
// If the subtree rooted at R is not empty, returns a pointer to the 
// rightmost Node in that subtree, otherwise returns nil.
Dictionary::Node* Dictionary::findMax(Node* R){
    if(R != nil){
        while(R->right != nil){
            R = R->right;
        }
    }
    return(R);
}

// findNext()
// If N does not point to the rightmost Node, returns a pointer to the
// Node after N in an in-order tree walk.  If N points to the rightmost 
// Node, or is nil, returns nil. 
Dictionary::Node* Dictionary::findNext(Node* N){
    if(N->right != nil){
        return(findMin(N->right));
    }
    Node* y = N->parent;
    while(y != nil && N == y->right){
        N = y;
        y = y->parent;
    }
    return(y);
}

// findPrev()
// If N does not point to the leftmost Node, returns a pointer to the
// Node before N in an in-order tree walk.  If N points to the leftmost 
// Node, or is nil, returns nil.
Dictionary::Node* Dictionary::findPrev(Node* N){
    if(N->left != nil){
        return(findMin(N->left));
    }
    Node* y = N->parent;
    while(y != nil && N == y->left){
        N = y;
        y = y->parent;
    }
    return(y);
}

// RBT Helper Functions (Optional) -----------------------------------------
   
// LeftRotate()
void Dictionary::LeftRotate(Node* N){
    //set y
    Node* y = N->right;

    // turn y's left subtree into x's right subtree
    N->right = y->left;
    if(y->left != nil){
        y->left->parent = N;
    }

    // link y's parent to x
    y->parent = N->parent;
    if(N->parent == nil){
        root = y;
    }else if(N == N->parent->left){
        N->parent->left = y;
    }else{
        N->parent->right = y;
    }
    // put x on y's left
    y->left = N; 
    N->parent = y;
}

// RightRotate()
void Dictionary::RightRotate(Node* N){
    //set y
    Node* y = N->left;

    // turn y's left subtree into x's right subtree
    N->left = y->right;
    if(y->right != nil){
        y->right->parent = N;
    }

    // link y's parent to x
    y->parent = N->parent;
    if(N->parent == nil){
        root = y;
    }else if(N == N->parent->right){
        N->parent->right = y;
    }else{
        N->parent->left = y;
    }
    // put x on y's left
    y->right = N; 
    N->parent = y;
}

// RB_InsertFixUP()
void Dictionary::RB_InsertFixUp(Node* N){
    Node* y = nil;
    while(N->parent->color == 'r'){
        if(N->parent == N->parent->parent->left){
            y = N->parent->parent->right;
            if(y->color == 'r'){
                N->parent->color = 'b';
                y->color = 'b';
                N->parent->parent->color = 'r';
                N = N->parent->parent;
            }else{
                if(N == N->parent->right){
                    N = N->parent;
                    LeftRotate(N);
                }
                N->parent->color = 'b';
                N->parent->parent->color = 'r';
                RightRotate(N->parent->parent);
            }
        }
        else{
            y = N->parent->parent->left;
            if(y->color == 'r'){
                N->parent->color = 'b';
                y->color = 'b';
                N->parent->parent->color = 'r';
                N = N->parent->parent;
            }else{
                if(N == N->parent->left){
                    N = N->parent;
                    RightRotate(N);
                }
                N->parent->color = 'b';
                N->parent->parent->color = 'r';
                LeftRotate(N->parent->parent);
            }
        }
    }
    root->color = 'b';
}

// RB_Transplant()
void Dictionary::RB_Transplant(Node* u, Node* v){
    if(u->parent == nil){
        root = v;
    }else if(u == u->parent->left){
        u->parent->left = v;
    }else{
        u->parent->right = v;
    }
    v->parent = u->parent;
}

// RB_DeleteFixUp()
void Dictionary::RB_DeleteFixUp(Node* N){
    Node* w = nil;
    while(N != root && N->color == 'b'){
	if(N == N->parent->left){
            w = N->parent->right;
            if(w->color == 'r'){
                w->color = 'b';
                N->parent->color = 'r';
                LeftRotate(N->parent);
                w = N->parent->right;
            }
            if(w->left->color == 'b' && w->right->color == 'b'){
                w->color = 'r';
                N = N->parent;
            }else{
                if(w->right->color == 'b'){
                    w->left->color = 'b';
                    w->color = 'r';
                    RightRotate(w);
                    w = N->parent->right;   
                }
                w->color = N->parent->color;
                N->parent->color = 'b';
                w->right->color = 'b';
                LeftRotate(N->parent);
                N = root;
            }
        }else{
            w = N->parent->left;
            if(w->color == 'r'){
                w->color = 'b';
                N->parent->color = 'r';
                RightRotate(N->parent);
                w = N->parent->left; 
            }
            if(w->right->color == 'b' && w->left->color == 'b'){
                w->color = 'r';
                N = N->parent;
            }else{
                if(w->left->color == 'b'){
                    w->right->color = 'b';
                    w->color = 'r';
                    LeftRotate(w);
                    w = N->parent->left;
                }
                w->color = N->parent->color;
                N->parent->color = 'b';
                w->left->color = 'b';
                RightRotate(N->parent);
                N = root;
            }
        }
    }
    N->color = 'b';
}

// RB_Delete()
void Dictionary::RB_Delete(Node* N){
    Node* y = N;
    Node* x = nil;
    int origin = y->color;
    if(N->left == nil){
        x = N->right;
        RB_Transplant(N, N->right);
    }else if(N->right == nil){
        x = N->left;
        RB_Transplant(N, N->left);
    }else{
        y = findMin(N->right);
        origin = y->color;
        x = y->right;
        if(y->parent == N){
            x->parent = y;
        }else{
            RB_Transplant(y, y->right);
            y->right = N->right;
            y->right->parent = y;
        }
        RB_Transplant(N, y);
        y->left = N->left;
        y->left->parent = y;
        y->color = N->color;
    }
    if(origin == 'b'){
        RB_DeleteFixUp(x);
    }
}


// Class Constructors & Destructors ----------------------------------------
   
// Creates new Dictionary in the empty state. 
Dictionary::Dictionary(){
    nil = new Node("nil", -100);
    nil->left = nil;
    nil->right = nil;
    root = nil;
    current = root;
    num_pairs = 0;
    nil->color = 'b';
}

// Copy constructor.
Dictionary::Dictionary(const Dictionary& D){
    nil = new Node("nil", -100);
    nil->left = nil;
    nil->right = nil;
    root = nil;
    current = root;
    num_pairs = 0;
    nil->color = 'b';
    preOrderCopy(D.root, D.nil);
}

 // Destructor
Dictionary::~Dictionary(){
    clear();
    delete nil;
}

// clear()
// Resets this Dictionary to the empty state, containing no pairs.
void Dictionary::clear(){
    postOrderDelete(root);
    root = nil;
    current = root;
    num_pairs = 0;
}

// Access functions --------------------------------------------------------

// size()
// Returns the size of this Dictionary.
int Dictionary::size() const{
    return(num_pairs);
}

// contains()
// Returns true if there exists a pair such that key==k, and returns false
// otherwise.
bool Dictionary::contains(keyType k) const{
    if(search(root, k) != nil){
        return(true);
    }else{
        return(false);
    }
}

// getValue()
// Returns a reference to the value corresponding to key k.
// Pre: contains(k)
valType& Dictionary::getValue(keyType k) const{
    if(contains(k)){
        Node* N = search(root,k);
        return(N->val);
    }else{
        throw std::logic_error("Dictionary does not have this KeyType, from getValeu()");
    }
}

// hasCurrent()
// Returns true if the current iterator is defined, and returns false 
// otherwise.
bool Dictionary::hasCurrent() const{
    if(current != nil){
        return(true);
    }else{
        return(false);
    }
}

// currentKey()
// Returns the current key.
// Pre: hasCurrent() 
keyType Dictionary::currentKey() const{
    if(hasCurrent() == true && size() != 0){
        return(current->key);
    }else{
        throw std::logic_error("Error, Does not have current, in currentKey()");
    }
}

// currentVal()
// Returns a reference to the current value.
// Pre: hasCurrent()
valType& Dictionary::currentVal() const{
    if(hasCurrent() == true){
        Node* N = current;
        return(N->val);
    }else{
        throw std::logic_error("Error, Does not have current, in currentVal()");
    }
}

// Manipulation procedures -------------------------------------------------

// setValue()
// If a pair with key==k exists, overwrites the corresponding value with v, 
// otherwise inserts the new pair (k, v).
void Dictionary::setValue(keyType k, valType v){
    Node* insert = new Node(k,v);

    Node* Y = nil;
    Node* X = root;
    while(X != nil){
        Y = X;
        if(insert->key < X->key){
            X = X->left;
        }else if(X->key == insert->key){
            X->val = v;
            delete insert;
            return;
        }else{
            X = X->right;
        }
    }
    insert->parent = Y;
    if(hasCurrent() == false){
        current = insert;
    }
    if(Y == nil){
        root = insert;
    }else if(insert->key < Y->key){
        Y->left = insert;
    }else{
        Y->right = insert;
    }
    num_pairs++;

    insert->left = nil;
    insert->right = nil;
    insert->color = 'r';
    RB_InsertFixUp(insert);
}

// remove()
// Deletes the pair for which key==k. If that pair is current, then current
// becomes undefined.
// Pre: contains(k).
void Dictionary::remove(keyType k){
    Node* found = search(root, k);
    if(found != nil){
        RB_Delete(found);
        num_pairs--;
        if(current == found){
            current = nil;
        }
        delete found;
    }else{
        throw std::logic_error("Remove k is not here");
    }
}

// begin()
// If non-empty, places current iterator at the first (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::begin(){
    if(size() != 0){
        Node* min = findMin(root);
        current = min;
    }
}

// end()
// If non-empty, places current iterator at the last (key, value) pair
// (as defined by the order operator < on keys), otherwise does nothing. 
void Dictionary::end(){
    if(size() != 0){
        Node* max = findMax(root);
        current = max;
    }
}

// next()
// If the current iterator is not at the last pair, advances current 
// to the next pair (as defined by the order operator < on keys). If 
// the current iterator is at the last pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::next(){
    if(hasCurrent() == false){
        throw std::logic_error("At the end of tree, next()");
    }
    current = findNext(current);
}

// prev()
// If the current iterator is not at the first pair, moves current to  
// the previous pair (as defined by the order operator < on keys). If 
// the current iterator is at the first pair, makes current undefined.
// Pre: hasCurrent()
void Dictionary::prev(){
    if(hasCurrent() == false){
        throw std::logic_error("At the end of tree, next()");
    }
    current = findPrev(current);
}

// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this Dictionary. Consecutive (key, value)
// pairs are separated by a newline "\n" character, and the items key and value 
// are separated by the sequence space-colon-space " : ". The pairs are arranged 
// in order, as defined by the order operator <.
std::string Dictionary::to_string() const{
    std::string s = "";
    inOrderString(s, root);
    return(s);
}

// pre_string()
// Returns a string consisting of all keys in this Dictionary. Consecutive
// keys are separated by newline "\n" characters. The key order is given
// by a pre-order tree walk.
std::string Dictionary::pre_string() const{
    std::string s = "";
    preOrderString(s, root);
    return(s);
}

// equals()
// Returns true if and only if this Dictionary contains the same (key, value)
// pairs as Dictionary D.
bool Dictionary::equals(const Dictionary& D) const{
    if(D.size() == 0 && this->size() == 0){
        return(true);
        //if size not equal 
    }else if(D.size() != this->size()){
        return(false);
    }else{
        //use to_string function to check
        if(D.to_string() == this->to_string()){
            return(true);
        }else{
            return(false);
        }
    }
}


// Overloaded Operators ----------------------------------------------------
   
// operator<<()
// Inserts string representation of Dictionary D into stream, as defined by
// member function to_string().
std::ostream& operator<<( std::ostream& stream, Dictionary& D ){
    return stream << D.to_string();
}

// operator==()
// Returns true if and only if Dictionary A equals Dictionary B, as defined
// by member function equals(). 
bool operator==( const Dictionary& A, const Dictionary& B ){
    return(A.equals(B));
}

// operator=()
// Overwrites the state of this Dictionary with state of D, and returns a
// reference to this Dictionary.
Dictionary& Dictionary::operator=( const Dictionary& D ){
    if(this != &D){
        Dictionary temp = D;
        std::swap(root, temp.root);
        std::swap(current, temp.current);
        std::swap(nil, temp.nil);
    }
    return(*this);
}


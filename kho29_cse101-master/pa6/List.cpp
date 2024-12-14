#include <iostream>
#include <string>
#include <stdexcept>
#include "List.h"
using namespace std;


// Private Constructor --------------------------------------------------------

// Node constructor
List::Node::Node(ListElement x){
    data = x;
    prev = nullptr;
    next = nullptr;
}

// Class Constructors & Destructors -------------------------------------------

// Creates a new Queue in the empty state.
List::List(){
    frontDummy = new Node(-100);
    backDummy = new Node(-100);
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    beforeCursor->next = afterCursor;
    afterCursor->prev = beforeCursor;
    pos_cursor = 0;
    num_elements = 0;
}

List::List(const List& L){
    frontDummy = new Node(-100);
    backDummy = new Node(-100);
    beforeCursor = frontDummy;
    afterCursor = backDummy;
    beforeCursor->next = afterCursor;
    afterCursor->prev = beforeCursor;
    pos_cursor = 0;
    num_elements = 0;

    Node* N = L.frontDummy->next;
    while(N != L.backDummy){
        this->insertBefore(N->data);
        N = N->next;
    }
    moveFront();
}

List::~List(){
    moveFront();
    while(length() > 0){
        eraseAfter();   
    }
    delete frontDummy;
    delete backDummy;
}

// Access functions --------------------------------------------------------

// length()
// Returns the length of this List.
int List::length() const{
    return(num_elements);
}    

// front()
// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const{
    if(length() > 0) {
        return(frontDummy->next->data);
    }else{
        throw std::length_error("List Error, length less than 0, front()");
    }
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const{
    if(length() > 0){
        return(backDummy->prev->data);
    }else{
        throw std::length_error("List Error, length less than 0, back()");
    }
}

// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const{
    return(pos_cursor);
}

// peekNext()
// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const{
    if(position() < length()){
        return(afterCursor->data);
    }else{
        throw std::range_error("List Error, position > length, peekNext()");
    }
}

// peekPrev()
// Returns the element before the cursor.
// pre: position()>0
ListElement List::peekPrev() const{
    if(position() > 0){
        return(beforeCursor->data);
    }else{
        throw std::range_error("List Error, postion() < 0, peekPrev()");
    }
}

// Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear(){
    moveFront();
    while(length() > 0){
        eraseAfter();
    }
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront(){
    pos_cursor = 0;
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack(){
    pos_cursor = length();  //set position of cursor to end
    afterCursor = backDummy;// |->backdummy
    beforeCursor = backDummy->prev; // before the backdummy<-|
}

// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over. 
// pre: position()<length() 
ListElement List::moveNext(){
    if(position() >= length()){
        throw std::range_error("List Error, postion at back, moveNext()");
    }
    pos_cursor++;
    afterCursor = afterCursor->next;
    beforeCursor = afterCursor->prev;
    return(beforeCursor->data);
}

// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over. 
// pre: position()>0
ListElement List::movePrev(){
    if(position() <= 0){
        throw std::range_error("List Error, position at front, movePrev()");
    }
    pos_cursor--;
    beforeCursor = beforeCursor->prev;
    afterCursor = beforeCursor->next;
    return(afterCursor->data);
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x){
    Node* N = new Node(x);
    N->next = afterCursor;
    N->prev = beforeCursor;
    afterCursor->prev = N;
    afterCursor = N;
    beforeCursor->next = N;
    num_elements++;
}

// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x){
    Node* N = new Node(x);
    N->next = afterCursor;
    N->prev = beforeCursor;
    beforeCursor->next = N;
    beforeCursor = N;
    afterCursor->prev = N;
    pos_cursor++;
    num_elements++;
}

// setAfter()
// Overwrites the List element after the cursor with x.
// pre: position()<length()
void List::setAfter(ListElement x){
    if(position() >= length()){
        throw std::range_error("List Error, position > length, setAfter()");
    }
    afterCursor->data = x; 
}

// setBefore()
// Overwrites the List element before the cursor with x.
// pre: position()>0
void List::setBefore(ListElement x){
    if(position() <= 0){
        throw std::range_error("List Error, position < 0 , setbefore()");
    }
    beforeCursor->data = x;
}

// eraseAfter()
// Deletes element after cursor.
// pre: position()<length()
void List::eraseAfter(){
    if(position() >= length()){
        throw std::range_error("List Error, cusor at end trying to delete dummyBACK, eraseAfter()");
    }
    Node* N = afterCursor;
    afterCursor = afterCursor->next;
    afterCursor->prev = beforeCursor;
    beforeCursor->next = afterCursor;
    num_elements--;
    delete N;
}

// eraseBefore()
// Deletes element before cursor.
// pre: position()>0
void List::eraseBefore(){
    if(position() <= 0){
        throw std::range_error("List Error, cusor at end trying to delete frontDummy, eraseBefore()");
    }
    Node* N = beforeCursor;
    beforeCursor = beforeCursor->prev;
    afterCursor->prev = beforeCursor;
    beforeCursor->next = afterCursor;
    pos_cursor--;
    num_elements--;
    delete N;
}


// Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in 
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then 
// returns the final cursor position. If x is not found, places the cursor 
// at position length(), and returns -1. 
int List::findNext(ListElement x){
    while(afterCursor != backDummy){
        if(moveNext() == x){

            return(pos_cursor);
        }
    }
    return(-1);
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1. 
int List::findPrev(ListElement x){
    while(beforeCursor != frontDummy){
        if(movePrev() == x){
            return(pos_cursor);
        }
    }
    return(-1);
}

// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
//got pseudo code from TAs
void List::cleanup(){
    Node* front = frontDummy->next;
    Node* two = nullptr;
    Node* next = nullptr;
    int inner_tracker = 0; //tracks postion of node to be deleted
    int outer_tracker = 0;

    while(front != backDummy){
        two = front;
        next = front->next;
        inner_tracker = outer_tracker + 1;
        while(next != backDummy){
            if(front->data == next->data){
                if(next == beforeCursor){
                    beforeCursor = two;
                }
                if(next == afterCursor){
                    afterCursor = next->next;
                }
                two->next = next->next;
                next->next->prev = two;
                
                delete next;
                if(inner_tracker < pos_cursor){
                    pos_cursor--;
                    inner_tracker--;
                }
                next = two->next;
                num_elements--;
            }else{
                two = next;
                next = two->next;
            }
            inner_tracker++;
        }
        front = front->next;
        outer_tracker++;
    }
}
 
// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. The cursor in the returned List will be at postion 0.
List List::concat(const List& L) const{
    List n;
    Node* N = this->frontDummy->next;
    while(N != this->backDummy){
        n.insertBefore(N->data);
        N = N->next;
    }
    Node* M = L.frontDummy->next;
    while(M != L.backDummy){
        n.insertBefore(M->data);
        M = M->next;
    }
    n.moveFront();
    return(n);
}

// to_string()
// Returns a string representation of this List consisting of a comma 
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const{
    Node* N = nullptr;
    std::string s = "";

    for(N = frontDummy->next; N != backDummy; N = N->next){
        s += std::to_string(N->data);
    }
    return s;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const{
    bool eq = false;
    Node* N = nullptr;
    Node* M = nullptr;

    eq = (this->length() == R.length());
    N = this->frontDummy->next;
    M = R.frontDummy->next;
    while(eq && N != nullptr){
        eq = (N->data == M->data);
        N = N->next;
        M = M->next;
    }
    return(eq);
}

// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ){
    return stream << L.List::to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The 
// cursors in both Lists are unchanged.
bool operator==( const List& A, const List& B ){
    return A.List::equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ){
    if(this != &L){
        List temp = L;

        std::swap(frontDummy, temp.frontDummy);
        std::swap(backDummy, temp.backDummy);
        std::swap(beforeCursor, temp.beforeCursor);
        std::swap(afterCursor, temp.afterCursor);
        std::swap(pos_cursor, temp.pos_cursor);
        std::swap(num_elements, temp.num_elements);
    }
    return *this;
}

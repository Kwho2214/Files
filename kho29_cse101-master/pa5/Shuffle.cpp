#include <iostream>
#include <fstream>
#include <string>
#include "List.h"
using namespace std;

void shuffle(List& D){
    if(D.length() == 1){
        return;
    }
    List left;
    List right;
    int len = D.length() / 2;
    D.moveFront();
    while(D.position() < len){
        left.insertBefore(D.peekNext());
        D.moveNext();
    }

    while(D.position() < D.length()){
        right.insertBefore(D.peekNext());
        D.moveNext();
    }
    
    D.moveFront();
    left.moveFront();
    right.moveFront();

    while(right.position() != right.length() && left.position() != left.length()){
        D.setAfter(right.peekNext());
        right.moveNext();
        D.moveNext();

        D.setAfter(left.peekNext());
        left.moveNext();
        D.moveNext();
    }
}

int main(int argc, char* argv[]){
    List D;
    if(argc != 2){
        cerr << "Usage: " << argv[0] << " <input>" << endl;
        return(EXIT_FAILURE);
    }

    int input = stoi(argv[1]);
    
 
    D.moveFront();

    cout<<"deck size       shuffle count"<<endl;
    cout<<"------------------------------"<<endl;

    for(int i = 1; i <= input; i++){
        int shuffle_count = 0;
        D.insertBefore(i);
        List copy = D;

        shuffle(copy);
        shuffle_count++;

        while(!(copy == D)){
            shuffle(copy);
            shuffle_count++;
        }
        cout<<i<<"               "<<shuffle_count<<endl;
    }
    D.~List();
    return(0);
}
#include<iostream>
#include<fstream>
#include<string>
#include"Dictionary.h"

using namespace std;

int main(int argc, char* argv[]){
    Dictionary A;
    ifstream in;
    ofstream out;
    std::string s;
    if(argc != 3){
        cerr << "Usage: " << argv[0] << " <input>" << endl;
        return(EXIT_FAILURE);
    }
    // open files for reading and writing 
    in.open(argv[1]);
    if( !in.is_open() ){
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return(EXIT_FAILURE);
    }

    out.open(argv[2]);
    if( !out.is_open() ){
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return(EXIT_FAILURE);
    }

    int x = 0;
    while(std::getline(in, s)){
        A.setValue(s, ++x);
    }

    out<<A.to_string()<<endl;
    out<<endl;
    out<<A.pre_string()<<endl;

    return(0);
}
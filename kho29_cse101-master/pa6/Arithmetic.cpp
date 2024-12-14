#include<iostream>
#include<string>
#include<cstddef>
#include<cmath>
#include<stdexcept>
#include<fstream>
#include"BigInteger.h"

using namespace std;

int main(int argc, char* argv[]){
    ifstream in;
    ofstream out;
    string first;
    string second;
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

    getline(in, first);
    BigInteger A = BigInteger(first);

    getline(in, second);
    BigInteger B = BigInteger(second);

    out<<"A = "<<A<<endl;
    out<<"B = "<<B<<endl;

    BigInteger sum = B + A;
    out<<"A + B = "<<sum<<endl;

    BigInteger diff = A - B;
    out<<"A - B = "<<diff<<endl;

    return(0);
}
#include<iostream>
#include<string>
#include<cstddef>
#include<cmath>
#include<stdexcept>
#include"BigInteger.h"

using namespace std;

int power = 9;
long base = 1000000000;

// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().
BigInteger::BigInteger(){
    signum = 0;
}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s){
    std::string first_char = s.substr(0,1); //string to hold the plus or minus
    if(first_char == "-" || first_char == "+"){
        s.erase(0,1);           //cut off the "+" or "-"
    }
    std::size_t found = s.find_first_not_of("0123456789"); //checks if string is all numbers after cutting off the sign infront of string
    if(found != std::string::npos){
        throw::std::invalid_argument("BigInteger contains non-numeric string");
    }
    if(empty(s) == 1){  //check if string is empty
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }

    std::string copy = s;
    while(copy[0] == '0' && copy.length() > 1){
        copy.erase(0,1);    //erase leading zeros
    }

    int end = power;
    int start = copy.length() - end; //to start at the end of the string

    while(start >= 0){
        std::string r = copy.substr(start, end);
        long st = std::stol(r);

        digits.insertBefore(st);
        digits.moveFront();
        int remain = end - (end - start);
        if((start - end) < 0 && start != 0){
            r = copy.substr(0,remain);
            st = stol(r);
            digits.insertBefore(st);
            digits.moveFront();
        }
        start -= end;
    }

    digits.moveFront();
    if(first_char == "-"){
        signum = -1;
    }else{
        signum = 1;
    }
}

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N){
    this->signum = N.signum;
    digits = N.digits;
}

// Access functions --------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive, 
// negative or 0, respectively.
int BigInteger::sign() const{
    if(signum == 1){
        return(1);
    }else if(signum == -1){
        return(-1);
    }else{
        return(0);
    }
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const{
    List copy = this->digits;
    List N_copy = N.digits;

    if(sign() == 1 && N.sign() == -1){
        return(1);
    }
    if(sign() == -1 && N.sign() == 1){
        return(-1);
    }
    if(sign() == N.sign()){
        if(digits.length() > N.digits.length()){
            return(1);
        }
        if(digits.length() < N.digits.length()){
            return(-1);
        }
        for(int i = 1; i <= digits.length(); i++){
            long a = copy.peekNext();
            long b = N_copy.peekNext();
            if(a == b){
                continue;
            }else{
                if(a < b){
                    return(sign() * -1);
                }else{
                    return(sign());
                }
            }
            copy.moveNext();
            N_copy.moveNext();
        }
    }
    return(0);
}

// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero(){
    digits.clear();
    signum = 0;
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate(){
    if(sign() == 1){
        signum = -1 * signum;
    }else if(sign() == -1){
        signum = -1* signum;
    }
}

// negateList()
// Changes the sign of each integer in List L. Used by sub().
void negateList(List& L){
    L.moveFront();
    while(L.position() != L.length()){
        long num = L.peekNext() * -1;
        L.setAfter(num);
        L.moveNext();
    }
}

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const{
    BigInteger k = *this; //copy this
    BigInteger n = N;     //copy N
    BigInteger fin;       //one to return for actual additions
    if(k.sign() == -1 && n.digits.length() != 0){
        if(n.sign() == 1){
            fin = k.sub(n);
            fin.signum = 1;
            return(fin);
        }else{
            k.signum *= -1;
            n.signum *= -1;
            fin = k.add(n);
            fin.signum = -1;
            return(fin);
        }
    }else{
        k.digits.moveBack();
        n.digits.moveBack();
        int n_sign = n.sign();
        int k_sign = k.sign();
        long carry = 0;
        while(true){
            if(n.digits.position() == 0 || k.digits.position() == 0){
                break;
            }
            long one = k_sign * k.digits.peekPrev();
            long sec = n_sign * n.digits.peekPrev();
            long res = one + sec + carry;

            if(res > base){
                carry = res/base;
                res = res % base;
            }

            if(res < 0){
                carry = res / base - 1;
                res = res % base + 100;
            }
            fin.digits.insertAfter(res);
            k.digits.movePrev();
            n.digits.movePrev();
        }
        if(k.digits.position() != 0){
            while(k.digits.position() != 0){
                long re = k.digits.peekPrev();
                if(carry == -1){
                    re = re - 1;
                }if(carry == 1){
                    re = re + 1;
                }
                fin.digits.insertAfter(re);
                k.digits.movePrev();
            }
        }else if(n.digits.position() != 0){
            while(k.digits.position() != 0){
                long re = k.digits.peekPrev();
                if(carry == -1){
                    re = re - 1;
                }if(carry == 1){
                    re = re + 1;
                }
                fin.digits.insertAfter(re);
                k.digits.movePrev();
            }
        }
        return(fin);
    }
}

// sub()
// Returns a BigInteger representing the difference of this and N.
// this - N
BigInteger BigInteger::sub(const BigInteger& N) const{
    BigInteger k = *this; //copy this
    BigInteger n = N;     //copy N
    BigInteger fin;       //one to return for actual additions
    negateList(n.digits);
    fin = k.add(n);

    return(fin);
}

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const{
    return(N);
}

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string(){
    std::string s = "";
    digits.moveFront();
    while(digits.position() != digits.length()){
        long num = digits.peekNext();
        std::string l = std::to_string(num);
        if(digits.position() == 0 && digits.peekNext() != 0){
            s += l;
        }else if(digits.position() != 0 && (int)l.length() == power){
            s += l;
        }else{
            int x = power - (int)l.length();
            for(int i = 0; i < x; i++){
                s += "0";
            }
            s += l;
        }
        digits.moveNext();
    }
    if(sign() == -1){
        s.insert(0,"-");
    }
    return(s);
}

// Overriden Operators -----------------------------------------------------
   
// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ){
    return stream << N.BigInteger::to_string();
}


// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ){
    if(A.compare(B) == 0){
        return(true);
    }else{
        return(false);
    }
}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ){
    if(A.compare(B) == -1){
        return(true);
    }else{
        return(false);
    }
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ){
    if(A.compare(B) == -1 || A.compare(B) == 0){
        return(true);
    }else{
        return(false);
    }
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ){
    if(A.compare(B) == 1){
        return(true);
    }else{
        return(false);
    }
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ){
    if(A.compare(B) == 1 || A.compare(B) == 0){
        return(true);
    }else{
        return(false);
    }
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ){
    BigInteger N;
    N = A.add(B);
    return(N);
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ){
    A = A.add(B);
    return(A);
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ){
    BigInteger N;
    N = A.sub(B);
    return(N);
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ){
    BigInteger C = A.sub(B);
    A = C;
    return(A);
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ){
    BigInteger N;
    N = A.mult(B);
    return(N);
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ){
    A = A.mult(B);
    return(A);
}

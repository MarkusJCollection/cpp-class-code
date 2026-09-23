#include "aes128_methods.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int countBits(int number) {
    //Our function for counting the number of bits it takes to represent a number.
    int total = 0;
    while (number > 0) {
        //Right bit shift each iteration.
        number >>= 1; 
        total++;
    }
    return total;
}

int aes_mod(int byte) {
        // Takes an input and modulus' it compared to our irreducible polynomial 0x11B.
    int byte_diff;
    do {
        byte_diff = countBits(byte) - 8;
        if (byte_diff > 0) {
            byte ^= 0x11b << (byte_diff - 1);
        }
    } while (byte_diff > 0);
    return byte;
}

void circularShiftL(int byte) {
        // Left circular shift of our byte.
    int sig_bit;
    if ((byte & 0x80) > 0) {
        sig_bit = 1;

    }
    else {
        sig_bit = 0;
    }
    byte <<= 1;
    byte &= 0xFF;
    byte + sig_bit;
}

int circularShiftL(int byte, int amount) {
        // Left circular shift of our byte by a given amount.

    for (int i = 0; i < amount; i++) {
        circularShiftL(byte);
    }
    return byte;
}

int polyMultiply(int byte_one, int byte_two) {
        // Multiply two polynomials in GF(2^m) mod 2.

    int result = 0;
    while (byte_two > 0) {
        byte_one <<= byte_two & 1;
        if (byte_two & 1) {
            result ^= byte_one;
        }
        byte_two >>= 1;
    }
    return result;
}

int polyMultiply(int byte_one, int byte_two, int ip) {
        // Multiply two polynomials with a modulus of an irreducible polynomial ip.

    int result = 0;
    while (byte_two > 0) {
        if (byte_two & 1) {
            result ^= byte_one;
            result = aes_mod(result);
        }
        byte_one <<= 1;
        byte_two >>= 1;
    }
    return result;
}

int polyDivide(int byte_one, int byte_two) {
    int quotient;
    int diff;

    while (byte_one >= byte_two) {
        diff = countBits(byte_one) - countBits(byte_two);
        byte_one ^= byte_two << diff;
        quotient ^= int(pow(2,diff)); 
    }
    return quotient;
}


int eeaGF(int poly_one, int poly_two) {
    // Extended Euclidean Aglorithm used for finding multiplicative inverse of a polynomial for a Galois Field.
    //Currently not used.
    vector<int> s;
    s.push_back(1);
    s.push_back(0);

    vector<int> t;
    t.push_back(0);
    t.push_back(1);

    vector<int> r;
    r.push_back(poly_one);
    r.push_back(poly_two);

    int i = 1;
    int j;
    int q;


    while (r[i] != 0) {
        i++;
        j = countBits(r[i-2]) - countBits(r[i-1]);


        if (j >= 0) {
            q = polyDivide(r[i - 2], r[i - 1]);
            r.push_back(r[i - 2] ^ polyMultiply(r[i - 1], j));
            t.push_back(t[i - 2] ^ polyMultiply(t[i - 1], j));
            s.push_back(s[i - 2] ^ polyMultiply(s[i - 1], j));
        }
        else {
            q = polyDivide(r[i - 1], r[i - 2]);
            r.push_back(r[i - 1] ^ polyMultiply(r[i - 1], j));
            t.push_back(t[i - 1] ^ polyMultiply(t[i - 1], j));
            s.push_back(s[i - 1] ^ polyMultiply(s[i - 1], j));
        }

    }
    
	return t[i-1];
}

int inverse(int byte) {
    //Inverse function used with AES, the standard irreducible polynomial is
    //x^8 + x^4 + x^3 + x + 1
    int irreducible_poly = 0x11b;
    return aes_mod(eeaGF(irreducible_poly, byte));
}

vector<int> stringToBlock(string input_string) {
    vector<int> vec;
    int ctr = 0;
    for (int chr: input_string) {
        //Converting our string to proper form.
        if (vec.size() > 16) {
            break;
        }
        if (chr < 0) {
            vec.push_back(chr + 256);
        }
        else {
            vec.push_back(chr);
        } 
    }
    while (vec.size() < 16) {
        vec.push_back(0);
    }

    return vec;
}
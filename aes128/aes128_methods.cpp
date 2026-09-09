#include "aes128_methods.h"
#include <iostream>
#include <vector>
#include <string>

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
    int byte_diff;
    do {
        byte_diff = countBits(byte) - 8;
        if (byte_diff > 0) {
            byte ^= 0x11b << (byte_diff - 1);
        }
    } while (byte_diff > 0);
    return byte;
}

void circularShiftL(int& byte) {
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
    for (int i = 0; i < amount; i++) {
        circularShiftL(byte);
    }
    return byte;
}

int polyMultiply(int byte_one, int byte_two) {
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


int eeaGF(int poly_one, int poly_two) {
    //Extended Euclidean Aglorithm used for finding multiplicative inverse of a polynomial for a Galois Field.
    std::vector<int> s;
    s.push_back(1);
    s.push_back(0);

    std::vector<int> t;
    t.push_back(0);
    t.push_back(1);

    std::vector<int> r;
    r.push_back(poly_one);
    r.push_back(poly_two);

    int i = 1;
    int j;


    while (r[i] != 0) {
        i++;
        j = countBits(r[i - 2]) - countBits(r[i - 1]);

        if (j >= 0) {
            r.push_back(r[i - 2] ^ (r[i - 1] << j));
            t.push_back(t[i - 2] ^ (t[i - 1] << j));
            s.push_back(s[i - 2] ^ (s[i - 1] << j));
        }
        else {
            r.push_back(r[i - 1] ^ (r[i - 2] << -j));
            t.push_back(t[i - 1] ^ (t[i - 2] << -j));
            s.push_back(s[i - 1] ^ (s[i - 2] << -j));
        }

    }
    
	return t[i-1];
}

int inverse(int byte) {
    //Inverse function used with AES, the standard irreducible polynomial is
    //x^8 + x^4 + x^3 + x + 1
    int irreducible_poly = 0x11b;
    return eeaGF(irreducible_poly, byte);
}

std::vector<int> stringToBlock(std::string input_string) {
    std::vector<int> vec;
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
#ifndef AES_SBOX
#define AES_SBOX
#include <vector>

int substitute(int);

int substitute(int, bool);

int createSbox();

void byteSub(std::vector<int>&);

void inverseByteSub(std::vector<int>&);

#endif
#ifndef AES_METHODS
#define AES_METHODS
#include <vector>
#include <string>

using namespace std;

int eeaGF(int, int);

int countBits(int);

int inverse(int);

void circularShift(int&);

int circularShift(int, int);

int aes_mod(int);

int polyMultiply(int, int);

int polyMultiply(int, int, int);

vector<int> stringToBlock(string);

#endif
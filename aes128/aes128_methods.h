#ifndef AES_METHODS
#define AES_METHODS
#include <vector>
#include <string>

using namespace std;

int eeaGF(int, int);

int countBits(int);

int inverse(int);

void circularShiftL(int);

int circularShiftL(int, int);

int aes_mod(int);

int polyMultiply(int, int);

int polyMultiply(int, int, int);

int polyDivide(int, int);

vector<int> stringToBlock(string);

#endif
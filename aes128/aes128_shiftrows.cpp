#include "aes128_shiftrows.h"
#include <vector> 

using namespace std;

void shiftRows(vector<int>& aes_block) {
	vector<int> new_block;

	for (int i = 0; i < 16; i ++) {
		new_block.push_back(aes_block[(i*5) % 16]);
	}
	aes_block = new_block;
}

void inverseShiftRows(vector<int>& aes_block) {
	vector<int> new_block;

	for (int i = 0; i < 16; i ++) {
		new_block.push_back(aes_block[(13 * i) % 16]);
	}
	aes_block = new_block;
}
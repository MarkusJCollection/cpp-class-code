#include <unordered_map>
#include <iostream>
int affine_transform[8][8] =
{
	{1, 0, 0, 0, 1, 1, 1, 1},
	{1, 1, 0, 0, 0, 1, 1, 1},
	{1, 1, 1, 0, 0, 0, 1, 1},
	{1, 1, 1, 1, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 0, 0, 0},
	{0, 1, 1, 1, 1, 1, 0, 0},
	{0, 0, 1, 1, 1, 1, 1, 0},
	{0, 0, 0, 1, 1, 1, 1, 1},
};


int create_sbox() {
	std::unordered_map<int, int> sbox;
	int b = 0;
	for (int i = 0; i < 128; i++) {
		sbox[i] = b;
		std::cout << (2 << 1);

		
	}
	
	return 0;
}
#include "aes128_mixcolumns.h"
#include "aes128_methods.h"
#include <vector>
#include <iostream>

void mixColumns(vector<int>& aes_block) {

	vector<int> new_block;
	int cur_byte;
	int new_byte;


	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cur_byte = (i * 4) + j;
			switch (j) {
			case 0:
				new_block.push_back(
					aes_mod(
						aes_block[cur_byte] << 1
					) ^
					aes_mod(
						(aes_block[cur_byte + 1] << 1) ^ aes_block[cur_byte + 1]
					) ^
					aes_mod(
						aes_block[cur_byte + 2]
					) ^
					aes_mod(
						aes_block[cur_byte + 3]
					)
				);
				break;
			case 1:
				new_block.push_back(
					aes_mod(
						aes_block[cur_byte - 1]
					) ^
					aes_mod(
						aes_block[cur_byte] << 1
					) ^
					aes_mod(
						(aes_block[cur_byte + 1] << 1) ^ aes_block[cur_byte + 1]
					) ^
					aes_mod(
						aes_block[cur_byte + 2]
					)
				);
				break;
			case 2:
				new_block.push_back(
					aes_mod(
						aes_block[cur_byte - 2]
					) ^
					aes_mod(
						aes_block[cur_byte - 1]
					) ^
					aes_mod(
						aes_block[cur_byte] << 1
					) ^
					aes_mod(
						(aes_block[cur_byte + 1] << 1) ^ aes_block[cur_byte + 1]
					)
				);
				break;
			case 3:
				new_block.push_back(
					aes_mod(
						(aes_block[cur_byte - 3] << 1) ^ aes_block[cur_byte - 3]
					) ^
					aes_mod(
						aes_block[cur_byte - 2]
					) ^
					aes_mod(
						aes_block[cur_byte - 1]
					) ^
					aes_mod(
						aes_block[cur_byte] << 1
					)
				);
				break;
			default:
				cout << "DEFAULTED IN SWITCH";
				std::exit;
				break;
			}

		}

	}
	aes_block = new_block;
}


void inverseMixColumns(vector<int>& aes_block) {

	vector<int> new_block;
	int cur_byte;
	int new_byte;
	int ip = 0x11b;


	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cur_byte = (i * 4) + j;
			switch (j) {
			case 0:
				new_block.push_back(
					polyMultiply(aes_block[cur_byte], 0xE, ip)
					^ polyMultiply(aes_block[cur_byte + 1], 0xB, ip)
					^ polyMultiply(aes_block[cur_byte + 2], 0xD, ip)
					^ polyMultiply(aes_block[cur_byte + 3], 0x9, ip)
				);
				break;
			case 1:
				new_block.push_back(
					polyMultiply(aes_block[cur_byte - 1], 0x9, ip)
					^ polyMultiply(aes_block[cur_byte], 0xE, ip)
					^ polyMultiply(aes_block[cur_byte + 1], 0xB, ip)
					^ polyMultiply(aes_block[cur_byte + 2], 0xD, ip)
				);
				break;
			case 2:
				new_block.push_back(
					polyMultiply(aes_block[cur_byte - 2], 0xD, ip)
					^ polyMultiply(aes_block[cur_byte - 1], 0x9, ip)
					^ polyMultiply(aes_block[cur_byte], 0xE, ip)
					^ polyMultiply(aes_block[cur_byte + 1], 0xB, ip)
				);
				break;
			case 3:
				new_block.push_back(
					polyMultiply(aes_block[cur_byte - 3], 0xB, ip)
					^ polyMultiply(aes_block[cur_byte - 2], 0xD, ip)
					^ polyMultiply(aes_block[cur_byte - 1], 0x9, ip)
					^ polyMultiply(aes_block[cur_byte], 0xE, ip)
				);
				break;
			default:
				cout << "DEFAULTED IN SWITCH";
				std::exit;
				break;
			}

		}

	}
	aes_block = new_block;
}
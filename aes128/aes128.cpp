#include <iostream>
#include <vector>
#include <string>
#include "aes128.h"
#include "aes128_methods.h"
#include "aes128_sbox.h"
#include "aes128_shiftrows.h"
#include "aes128_keyschedule.h"
#include "aes128_mixcolumns.h"
#include "aes128_fileoperations.h"

using namespace std;

AES::AES(vector<int> key) {
	setKey(key);
}

vector<int> AES::getKey() {
	return aes_key;
}

void AES::setKey(vector<int> key) {
	aes_key = key;
	key_schedule = createKeys(aes_key);
}

void AES::encrypt(vector<int>& aes_block) {

	keyAddition(aes_block, key_schedule, 0);

	for (int i = 1; i < 10; i++) {
		byteSub(aes_block);
		shiftRows(aes_block);
		mixColumns(aes_block);
		keyAddition(aes_block, key_schedule, i);
	}

	byteSub(aes_block);
	shiftRows(aes_block);
	keyAddition(aes_block, key_schedule, 10);
}

vector<vector<int>> AES::encrypt(vector<vector<int>> multiple_blocks) {
	vector<vector<int>> encrypted_block;
	for (vector<int> aes_block : multiple_blocks) {
		encrypt(aes_block);
		encrypted_block.push_back(aes_block);
	}
	return encrypted_block;
}

void AES::decrypt(vector<int>& aes_block) {

	keyAddition(aes_block, key_schedule, 10);
	inverseShiftRows(aes_block);
	inverseByteSub(aes_block);

	for (int i = 9; i > 0; i--) {
		keyAddition(aes_block, key_schedule, i);
		inverseMixColumns(aes_block);
		inverseShiftRows(aes_block);
		inverseByteSub(aes_block);
	}

	keyAddition(aes_block, key_schedule, 0);

}

vector<vector<int>> AES::decrypt(vector<vector<int>> multiple_blocks) {
	vector<vector<int>> decrypted_block;
	for (vector<int> aes_block : multiple_blocks) {
		decrypt(aes_block);
		decrypted_block.push_back(aes_block);
	}
	return decrypted_block;
}

bool AES::encrypt(string file_name) {
	vector<vector<int>> original_output;
	vector<vector<int>> encrypted_output;

	original_output = fileToBlocks(file_name);

	encrypted_output = encrypt(original_output);
	blocksToFile("ENCRYPTED_" + file_name, encrypted_output);
	return true;
}

bool AES::decrypt(string file_name) {
	vector<vector<int>> encrypted_output;
	vector<vector<int>> decrypted_output;

	encrypted_output = fileToBlocks(file_name);

	decrypted_output = decrypt(encrypted_output);
	blocksToFile("DECRYPTED_" + file_name, decrypted_output);
	return true;
}

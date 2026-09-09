#include "aes128_keyschedule.h"
#include "aes128_sbox.h"
#include "aes128_methods.h"
#include <vector>
#include <iostream>

using namespace std;

void gTransform(vector<int>& word) {
	int tmp = word.front();
	word.erase(word.begin());
	word.push_back(tmp);
}


vector<vector<int>> createKeys(vector<int> initial_key) {
	vector<vector<int>> key_schedule;
	vector<int> word_vector;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			word_vector.push_back(initial_key[i]);
		}
		key_schedule.push_back(word_vector);
		word_vector.clear();
	}

	int rc = 1;
	vector<int> new_word;


	for (int i = 1; i < 11; i++) {
		word_vector = key_schedule[i];


		for (int j = 0; j < 4; j++) {
			word_vector = key_schedule[(4 * i) + j - 1];
			if (j == 0) {
				gTransform(word_vector);
				for (int k = 0; k < 4; k++) {
					word_vector[k] = substitute(word_vector[k]);
				}
				word_vector[0] ^= rc;
			}
			for (int k = 0; k < 4; k++) {
				new_word.push_back((word_vector[k] ^ key_schedule[(4 * (i - 1)) + j][k]));
			}
			key_schedule.push_back(new_word);
			new_word.clear();
			word_vector.clear();
		}
		rc = aes_mod(rc<<(1));
	}

	return key_schedule;

}


void keyAddition(vector<int>& aes_block, vector<vector<int>> key_schedule, int round_num) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			aes_block[(4 * i) + j] = aes_block[(4 * i) + j] ^ key_schedule[(round_num * 4) + i][j];
		}
	}
}
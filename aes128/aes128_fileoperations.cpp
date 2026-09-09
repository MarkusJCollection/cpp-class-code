#include "aes128_fileoperations.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


void cleanBlock(vector<int>& char_block) {
	if (char_block.size() == 0) {
		return;
	}
	while (char_block.back() == 0) {
		char_block.pop_back();
	}
}



vector<vector<int>> fileToBlocks(const string file_name) {
	ifstream in_stream;
	vector<vector<int>> aes_blocks;
	vector<int> block;

	in_stream.open(file_name, ios::in | ios::binary);

	char inputch;
	int counter = 0;

	while (in_stream.get(inputch)) {
		if (int(inputch) < 0) {
			block.push_back(int(inputch) + 256);
		}
		else {
			block.push_back(int(inputch));
		}
		
		if (counter % 16 == 15) {
			aes_blocks.push_back(block);
			block.clear();
		}
		counter++;
	}

	if (block.size() != 0) {
		while (block.size() < 16) {
			block.push_back(0);
		}
		aes_blocks.push_back(block);
	}
	

	in_stream.close();
	
	return aes_blocks;

}


void blocksToFile(const string file_name, vector<vector<int>> aes_blocks) {
	cleanBlock(aes_blocks.back());
	ofstream out_stream;
	out_stream.open(file_name, ios::out | ios::trunc | ios::binary);

	
	for (vector<int> block : aes_blocks) {
		for (int chr : block) {
			out_stream << char(chr);
		}
	}
	out_stream.close();
}



void test() {

	ifstream in_stream;
	in_stream.open("test.txt", ios::in | ios::binary);
	
	
	char inputch;
	int counter = 0;
	vector<int> aes_block;
	
	while (in_stream.get(inputch)) {
		cout << inputch;
	}




	in_stream.close();


}
#ifndef AES_FILEOPERATIONS
#define AES_FILEOPERATIONS
#include <vector>
#include <string>

using namespace std;

void cleanBlock(vector<int>&);

vector<vector<int>> fileToBlocks(const string);

void blocksToFile(const string, vector<vector<int>>);

void test();

#endif
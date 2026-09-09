#ifndef AES_KEYSCHEDULE
#define AES_KEYSCHEDULE
#include <vector>

using namespace std;

void gTransform(vector<int>&);

vector<vector<int>> createKeys(vector<int>);

void keyAddition(vector<int>&, vector<vector<int>>, int);

#endif
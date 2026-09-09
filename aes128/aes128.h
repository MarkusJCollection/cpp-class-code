#ifndef _AES_
#define _AES_
#include <vector>
#include <string>

using namespace std;

class AES {
private:
	vector<vector<int>> key_schedule;
	vector<int> aes_key;

public:

	AES(vector<int>);

	vector<int> getKey();

	void setKey(vector<int>);

	void encrypt(vector<int>&);

	vector<vector<int>> encrypt(vector<vector<int>>);

	void decrypt(vector<int>&);

	vector<vector<int>> decrypt(vector<vector<int>>);

	bool encrypt(string);

	bool decrypt(string);


};

#endif
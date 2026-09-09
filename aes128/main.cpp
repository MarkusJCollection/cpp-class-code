#include "aes128.h"
#include "aes128_methods.h"
#include "aes128_fileoperations.h"
#include "aes128_userinput.h"
#include <iostream>

using namespace std;

string directory_path = ""; // Leave empty for relative to project.
vector<int> key = 
{ 
	0,0,0,0,
	0,0,0,0,
	0,0,0,0,
	0,0,0,0 
};

static AES aes(key);

void fullShowcase() {
	const string KEY_STRING = "MARKUS_JESSE_CPP"; //String must be 16 bytes
	key = stringToBlock(KEY_STRING);
	aes.setKey(key);
	cout << "AES Key set as '" << KEY_STRING << "'.\n";

	string file_name = directory_path + "showcase.txt";

	aes.encrypt(file_name);
	cout << "File showcase.txt encrypted as 'ENCRYPTED_showcase.txt'.\n";

	aes.decrypt("ENCRYPTED_" + file_name);
	cout << "File ENCRYPTED_showcase.txt decrypted as 'DECRYPTED_ENCRYPTED_showcase.txt'\n";
}

void encryptFile(string file_name) {
	aes.encrypt(directory_path + file_name);

	cout << "AES key used: \n\t[";
	for (int byte : key) {
		cout << byte << " ";
	}
	cout << "].\n";

	cout << "File '" << file_name << "' encrypted as 'ENCRYPTED_" << file_name << "'.\n";	
}

void decryptFile(string file_name) {
	aes.decrypt(directory_path + file_name);

	cout << "AES key used: \n\t[";
	for (int byte : key) {
		cout << byte << " ";
	}
	cout << "].\n";

	cout << "File '" << file_name << "' decrypted as 'DECRYPTED_" << file_name << "'\n";
}

void consoleQuestions() {
	int choice;
	bool continuing = true;
	while (continuing) {
		choice = askOption();

		switch (choice) {
		case 0:
			continuing = false;
			break;
		case 1:
			directory_path = askDirectory();
			cout << "Directory set as '" << directory_path << "'.\n";
			break;
		case 2:
			key = stringToBlock(askKey());
			aes.setKey(key);
			cout << "Key set as [ ";
			for (int byte : key) {
				cout << byte << " ";
			}
			cout << "].\n";
			break;
		case 3:
			fullShowcase();
		case 4:
			encryptFile(askFileName());
			break;
		case 5:
			decryptFile(askFileName());
			break;
		default:
			cout << "Invalid option chosen, please pick another.\n\n";
			break;
		}

	}
	
}

int main() {

	consoleQuestions();

	return 0;
}
#include "aes128_userinput.h"
#include <string>
#include <iostream>

using namespace std;

string askDirectory() {
	cout << "Give the absolute path to the file directory you would like to use: ";

	string usr_in;
	cin >> usr_in;

	return usr_in;
}

int askOption() {
	cout << "\n\nPlease choose an option by typing the appropriate number -" << "\n";
	cout << "\t0: Exit the program.\n";
	cout << "\t1: Change directory path.\n";
	cout << "\t2: Change AES Key.\n";
	cout << "\t3: Create an initial test file to encrypt and decrypt.\n";
	cout << "\t4: Encrypt your own file.\n";
	cout << "\t5: Decrypt your own file.\n";

	int usr_in;
	cin >> usr_in;
	
	return usr_in;
}

string askFileName() {
	cout << "Please enter file name with extension: ";

	string usr_in;
	cin >> usr_in;
	
	return usr_in;

}

string askKey() {
	cout << "Please enter what you would like the encryption key to be: ";

	string usr_in;
	cin >> usr_in;

	return usr_in;
}
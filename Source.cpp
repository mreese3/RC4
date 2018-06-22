

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

void rc4Encrypt(unsigned char * ByteInput, unsigned char * pwd,
	unsigned char * &ByteOutput) // Takes in bytes to decrypt, seed, and variable name to store end result
{
	// Variable declarations
	unsigned char * temp;
	int i, j = 0, t, tmp, tmp2, s[256], k[256];

	for (tmp = 0; tmp < 256; tmp++) {
		s[tmp] = tmp; // Array to store locations
		k[tmp] = pwd[(tmp % strlen((char *)pwd))]; // Array that stores byte string value at location tmp % length of password string
	}
	cout << "\nAfter initial permutation of S (Decimal Values): \n\n";
	for (i = 0; i < 256; i++) {
		j = (j + s[i] + k[i]) % 256; // j is equal to itself + the location value in array S + value stored from previous for loop at location i in array K
		tmp = s[i]; // tmp stores the location to be looked at
		s[i] = s[j]; // S array at location j is stored in S at location i
		s[j] = tmp; // S array at location j is set to i
		cout << setw(4) << s[i]; // Print the permutation of S with standard width for neatness
	}
	cout << endl << endl; // Separate sections
	temp = new unsigned char[(int)strlen((char *)ByteInput) + 1]; // Create new temp variable of type char array with size of length of message
	i = j = 0; // Zero everything out
	cout << "Keys generated for plaintext (Decimal Representation):\n";
	for (tmp = 0; tmp < (int)strlen((char *)ByteInput); tmp++) {
		i = (i + 1) % 256; // i = itself + 1 % 256
		j = (j + s[i]) % 256; // j = itself + array S at location i % 256
		tmp2 = s[i]; // At location i of array S, store in tmp2
		s[i] = s[j]; // At location j of array S, store in location i of array S
		s[j] = tmp2; // At location j of array S, store value in tmp2
		t = (s[i] + s[j]) % 256; // t = array S at i and j added together % 256
		cout << setw(4) << s[t]; // Print keystring
		if (s[t] == ByteInput[tmp]) // If value at location t is the same byte as the byte in the message, store the byte
			temp[tmp] = ByteInput[tmp];
		else
			temp[tmp] = s[t] ^ ByteInput[tmp]; // If the value at location t is not the same byte in the message, XOR the bytes
	}
	cout << "\nCiphertext generated (Hexidecimal Representation):\n";
	for (tmp = 0; tmp < (int)strlen((char *)ByteInput); tmp++) {
		printf("%02x %-4", temp[tmp]); // Print out the hex values of the ciphertext		
	}
	temp[tmp] = '\0'; // End the cipher array
	ByteOutput = temp; // Set the cipher array to the encrypted variable
	
}

void rc4Decrypt(unsigned char * ByteInput, unsigned char * pwd,
	unsigned char * &ByteOutput) // Takes in bytes to decrypt, seed, and variable name to store end result
{
	unsigned char * temp;
	int i, j = 0, t, tmp, tmp2, s[256], k[256];
	for (tmp = 0; tmp < 256; tmp++) {
		s[tmp] = tmp;
		k[tmp] = pwd[(tmp % strlen((char *)pwd))];
	}
	for (i = 0; i < 256; i++) {
		j = (j + s[i] + k[i]) % 256;
		tmp = s[i];
		s[i] = s[j];
		s[j] = tmp;
	}
	cout << endl << endl;
	temp = new unsigned char[(int)strlen((char *)ByteInput) + 1];
	i = j = 0;
	for (tmp = 0; tmp < (int)strlen((char *)ByteInput); tmp++) {
		i = (i + 1) % 256;
		j = (j + s[i]) % 256;
		tmp2 = s[i];
		s[i] = s[j];
		s[j] = tmp2;
		t = (s[i] + s[j]) % 256;
		if (s[t] == ByteInput[tmp])
			temp[tmp] = ByteInput[tmp];
		else
			temp[tmp] = s[t] ^ ByteInput[tmp];
	}
	temp[tmp] = '\0'; // Set end of array
	ByteOutput = temp; // Set array to decrypted variable
}

int main() {
	//create character pointers to store the plaintext and password 
	unsigned char * message; 
	unsigned char * pwd;
	unsigned char * encrypted;
	unsigned char * decrypted;
	message = (unsigned char *)"We are able to implement the RC4 algorithm!"; //set plaintext to message 
	pwd = (unsigned char *)"rc4"; //set seed to password
	cout << "########################################################\n";
	cout << "Test Case 1\n";
	cout << "########################################################\n";
	cout << "Plaintext: " << message << endl; //print plaintext 
	cout << "Seed Used: " << pwd << endl; //print seed
	rc4Encrypt(message, pwd, encrypted); //jump to rc4Encrypt function to generate key string and cypher text 
	rc4Decrypt(encrypted, pwd, decrypted); //jump to rc4Decrypt function to decrypt cypher text 
	cout << "Message encrypted: " << encrypted << endl; //print out encrypted message 
	cout << "Message decrypted: " << decrypted << endl << endl << endl; //print out decrypted message 

	message = (unsigned char *)"For byte XOR, see www.cplusplus.com/forum"; //set plaintext to message 
	pwd = (unsigned char *)"google search"; //aet seed to password
	cout << "########################################################\n";
	cout << "Test Case 2\n";
	cout << "########################################################\n";
	cout << "Plaintext: " << message << endl; //print plaintext
	cout << "Seed Used: " << pwd << endl; //print seed 
	rc4Encrypt(message, pwd, encrypted); //jump to rc4Encrypt function to generate key string and cypher text 
	rc4Decrypt(encrypted, pwd, decrypted); //jump to rc4Decrypt function to decrypt cypher text
	cout << "Message encrypted: " << encrypted << endl; //print out encrypted message 
	cout << "Message decrypted: " << decrypted << endl; //print out decrypted message 

	system("pause");
	return 0;
}
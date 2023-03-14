#include <iostream>
#include <fstream>
#include "vigenere.h"

using namespace std;

void banner()
{
	cout << R"(
	██╗  ██╗ █████╗ ███████╗██╗███████╗██╗  ██╗██╗
	██║ ██╔╝██╔══██╗██╔════╝██║██╔════╝██║ ██╔╝██║
	█████╔╝ ███████║███████╗██║███████╗█████╔╝ ██║
	██╔═██╗ ██╔══██║╚════██║██║╚════██║██╔═██╗ ██║
	██║  ██╗██║  ██║███████║██║███████║██║  ██╗██║
	╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝╚═╝╚══════╝╚═╝  ╚═╝╚═╝

	██████╗██████╗  █████╗  ██████╗ ██╗  ██╗███████╗ ██████╗ 
	██╔════╝██╔══██╗██╔══██╗██╔════╝██║ ██╔╝██╔════╝██╔══██╗
	██║     ██████╔╝███████║██║     █████╔╝ █████╗  ██████╔╝
	██║     ██╔══██╗██╔══██║██║     ██╔═██╗ ██╔══╝  ██╔══██╗
	╚██████╗██║  ██║██║  ██║╚██████╗██║  ██╗███████╗██║  ██║
	 ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝ ╚═════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝

					Vigenère Cipher Tool                                                                                            
	)" << endl;
}

string reader(string filename)
{
	int bufferSize = 8192;
	char bufferClose[bufferSize];
	fstream yfile;
	yfile.open(filename);
	yfile.read(bufferClose, bufferSize);
	yfile.close();
	string pBuffer = (string) bufferClose;
	return pBuffer;
}

int main(int argc, char* argv[]){

	Vigenere *vigenere;
	string lang1 = "english";
	string lang2 = "portuguese";
	string fileName;
	int choice = 0;
	string divisor = "--------------------------------------------------------------------";
	banner();
	if(argc >= 3)
	{
		cout << divisor << endl << endl;
		string fileName = (string) argv[1];
		string mode = (string) argv[2];
		string mode1 = "decrypt_with_key";
		string mode2 = "decrypt_without_key";
		string mode3 = "encrypt"; 
		string bufferFile = reader(fileName);
		string key;

		if(mode == mode1)
		{
			cout << " [ Insert the key ]  ";
			cin >> key;
			cout << endl;
			cout << divisor << endl << endl;
			cout << bufferFile << endl << endl;
			cout << divisor << endl << endl;
			cout << vigenere->encryptDecrypt(bufferFile, key, true) << endl << endl;
			cout << divisor << endl << endl;
		}

		else if(mode == mode2)
		{
			int lang = (argv[3] == lang1) ? 0 : 1;
			string y = vigenere->staticFilter(bufferFile);
			int* h = vigenere->repeatedSequencesLength(y);
			int keyL = vigenere->possibleKeyLength(h);
			string k = vigenere->possibleKey(y, lang, keyL);
			cout << " key [ " << k << " ]" << endl << endl;
			cout << divisor << endl << endl;
			cout << bufferFile << endl << endl;
			cout << divisor << endl << endl;
			cout << vigenere->encryptDecrypt(bufferFile, k, true) << endl << endl;
			cout << divisor << endl << endl;
		}

		else if(mode == mode3)
		{
			cout << " [ Insert the key ]  ";
			cin >> key;
			cout << endl;
			cout << divisor << endl << endl;
			cout << bufferFile << endl << endl;
			cout << divisor << endl << endl;
			cout << vigenere->encryptDecrypt(bufferFile, key) << endl << endl;
			cout << divisor << endl << endl;
		}
	}

	else
	{	
		cout << divisor << endl << endl;
		cout << " [ Modes ]  'decrypt_with_key', 'decrypt_without_key', 'encrypt'" << endl << endl;
	}

	return(0);
}
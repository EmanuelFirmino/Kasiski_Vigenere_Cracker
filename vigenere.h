#define MIN_ASCII 97
#define MAX_ASCII 122
#define MIN_UPPER_ASCII 65
#define MAX_UPPER_ASCII 90
#define FLOOR_FACTOR 32

#include <string>

class Vigenere 
{
public:
	int* repeatedSequencesLength(std::string);
	int possibleKeyLength(int*);
	std::string encryptDecrypt(std::string, std::string, bool);
	std::string possibleKey(std::string, int, int);
	std::string staticFilter(std::string);

private:
	bool isValid(char);
	bool isUpper(char);
	char floorFilter(char);
};

// Método que encripta ou decripta o texto fornecido, levando em consideração também a chave atribuída a 'keyString'.

std::string Vigenere::encryptDecrypt(std::string cryptoGram, std::string keyString, bool decrypt=false)
{
	std::string newGram;
	int tempChar; 
	int factorEncDec = decrypt ? -1 : 1;
	int keyIndice = 0, cryptoIndice = 0;
	int sizekeyGram = keyString.size();
	unsigned char resChar;


	while(cryptoGram[cryptoIndice])
	{	
		tempChar = cryptoGram[cryptoIndice];

		if(isValid(tempChar))
		{
			tempChar = (isUpper(tempChar)) ? floorFilter(tempChar) : tempChar;	
		
			tempChar = tempChar + (keyString[keyIndice]-MIN_ASCII)*factorEncDec;

			if(tempChar > MAX_ASCII)
			{
				resChar = MIN_ASCII + (tempChar - MAX_ASCII - 1);
			}

			else if(tempChar < MIN_ASCII)
			{
				resChar = MAX_ASCII - (MIN_ASCII - tempChar - 1);
			}

			else
			{
				resChar = tempChar;
			}

			keyIndice = (keyIndice+1) % sizekeyGram;
		}
		else
		{
			resChar = tempChar;
		}

		newGram.push_back(resChar);
		cryptoIndice++;
	}

	return newGram;
}

bool Vigenere::isValid(char chr)
{
	if((chr >= MIN_ASCII && chr <= MAX_ASCII) || (chr >= MIN_UPPER_ASCII && chr <= MAX_UPPER_ASCII))
	{
		return true;
	}
	return false;
}

bool Vigenere::isUpper(char chr)
{
	if(chr >= MIN_UPPER_ASCII && chr <= MAX_UPPER_ASCII)
	{
		return true;
	}
	return false;
}

char Vigenere::floorFilter(char chr)
{
	return chr + FLOOR_FACTOR;
}

std::string Vigenere::staticFilter(std::string cryptoGram)
{
	int count = 0;
	std::string newText;
	char tempChar;

	while(cryptoGram[count])
	{
		tempChar = cryptoGram[count];

		if(isValid(tempChar))
		{
			tempChar = isUpper(tempChar) ? floorFilter(tempChar) : tempChar;
			newText.push_back(tempChar);
		}
		count++;
	}
	return newText;
}

int* Vigenere::repeatedSequencesLength(std::string cryptoGram)
{
	const int buffer = 100;
	int count, memIndice = 0;
	int xount, maxIndice;
	std::string subString, xubString;
	static int mem[buffer] = { 0 };
	int temp, initialLength = 4;

	for(int range=initialLength; range>=initialLength-1; range--)
	{	
		maxIndice = cryptoGram.size()-range;
		count = 0;

		while((count <= maxIndice) && (memIndice < buffer))
		{
			subString = cryptoGram.substr(count, range);
			xount = count+range;

			while((xount <= maxIndice) && (memIndice < buffer))
			{
				xubString = cryptoGram.substr(xount, range);
				if (xubString == subString)
				{
					temp = (xount+range)-(count+range);
					mem[memIndice] = temp;	
					memIndice++;
				}
				xount++;
			}
			count++;
		}
	}

	return mem;
}

int Vigenere::possibleKeyLength(int* repeatedLength)
{
	int candidate, nLength, greater;
	int repeatedIndice = 0;
	int buffer = 100;
	int probability[23] = { 0 };

	while(repeatedLength[repeatedIndice])
	{
		nLength = repeatedLength[repeatedIndice];

		for(int size=2; size<25; size++)
		{
			if(!(nLength % size))
			{
				probability[size-2]++;
			}
		}

		if(repeatedIndice >= buffer-1) {
			break;
		}

		repeatedIndice++;
	}

	greater = probability[0];
	candidate = 2;

	for(int siz=3; siz<25; siz++)
	{
		if(probability[siz-2]+siz > greater)
		{
			greater = probability[siz-2];
			candidate = siz;
		}
	}

	return candidate;
}

std::string Vigenere::possibleKey(std::string filteredGram, int language, int rangeKey)
{
	float frequency_EN[] = {
		0.082, 0.015, 0.028, 0.043, 0.127, 0.022,
		 0.02, 0.061,  0.07, 0.015, 0.077,  0.04,
		0.024, 0.067, 0.075, 0.019,  0.01,  0.06,
		0.063, 0.091, 0.028, 0.098, 0.024, 0.015,
		 0.02, 0.007  
	};

	float frequency_PT[] = {
		0.146,  0.01, 0.039,  0.05, 0.126,  0.01,
		0.013, 0.008, 0.062, 0.004, 0,002, 0.028,
		0.047, 0.045, 0.097, 0.025, 0.012, 0.065,
		0.068, 0.043, 0.036, 0.016, 0.004, 0.025, 
		0.001, 0.047 
	};

	std::string key;
	int keyLength = rangeKey;
	int filteredLength = filteredGram.size();
	int tempLetter, total;
	int shift, perIndice;
	char possibleChar;
	float sumPer, tempSum, lowerFrequency;


	for(int letter=0; letter<keyLength; letter++)
	{
		float frequencies[26] = { 0 };
		tempLetter = letter;
		total = 0;
		shift = 0;
			
		while(tempLetter <= filteredLength-1)
		{
		frequencies[filteredGram[tempLetter]-MIN_ASCII]++;
			tempLetter = tempLetter + keyLength;
			total++;
		}

		for(int per=0; per<26; per++)
		{
			frequencies[per] = frequencies[per] / (float) total;	
		}

		while(shift < 26)
		{
			sumPer = 0;

			for(int pos=0; pos<26; pos++)
			{
				perIndice = pos + shift;

				if(perIndice > 25)
				{
					perIndice = perIndice - 26;
				}

				if(!language)
				{
					tempSum = frequency_EN[pos] - frequencies[perIndice];
				}

				else
				{
					tempSum = frequency_PT[pos] - frequencies[perIndice];

				}

				tempSum = (tempSum < 0) ? -tempSum : tempSum;
				sumPer = sumPer + tempSum;
			}

			if(shift)
			{
				if(sumPer < lowerFrequency)
				{
					lowerFrequency = sumPer;
					possibleChar = MIN_ASCII + shift;
				}
			}

			else
			{
				lowerFrequency = sumPer;
				possibleChar = MIN_ASCII + shift;
			}

			shift++;
		}

		key.push_back(possibleChar);	
	}

	return key;
}
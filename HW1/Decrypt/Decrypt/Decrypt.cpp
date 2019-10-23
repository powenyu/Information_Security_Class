#include <iostream>
#include <string>
#include <bitset>
#include <map>
#include <vector>
using namespace std;
typedef string(*funcPtr)(string key, string cipherText);
string Caesar(string key, string cipherText);
string Playfair(string key, string cipherText);
string Vernam(string key, string cipherText);
string Row(string key, string cipherText);
string RailFence(string key, string cipherText);

string Decrypt(string cipher, string key, string cipherText)
{
	funcPtr func[5] =
	{
		Caesar,
		Playfair,
		Vernam,
		Row,
		RailFence
	};

	string ciphers[5] =
	{
		"caesar",
		"playfair",
		"vernam",
		"row",
		"rail_fence"
	};

	for (int i = 0; i < 5; i++)
	{
		if (cipher == ciphers[i])
			return func[i](key, cipherText);
	}
	return "Error";
}
int main(int argc, char *argv[])
{
	//cout << argv[3] << endl;
	cout << Decrypt(argv[1], argv[2], argv[3]) << endl;
	system("pause");
}
//////////////////////////////
//abcdefghijklmnopqrstuvwxyz//
//vwxyzabcdefghijklmnopqrstu//
//////////////////////////////
string Caesar(string key, string cipherText)
{
	int offset = stoi(key);
	string plainText;
	char c;
	for (int i = 0; i < cipherText.size(); i++)
	{
		c = tolower(cipherText[i]) - offset;
		c = c < 'a' ? c + 26 : c;
		plainText.push_back(c);
	}
	return plainText;
}

/////////////
//C O M P A//
//B D E F G//
//H I K L N//
//Q R S T U//
//V W X Y Z//
/////////////
void Find(int& x, int& y, const char table[5][5], const char& c)
{
	for (x = 0; x < 5; x++)
		for (y = 0; y < 5; y++)
			if (table[y][x] == c) return;
}

string Playfair(string key, string cipherText)
{
	string plainText;
	const char alphabets[26] = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
	int count = 0;
	int fill = 0;
	bool repeated[25] = { false };
	char table[5][5];

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (count == key.length())
			{
				while (repeated[fill])
					fill++;
				table[i][j] = alphabets[fill++];
			}
			else
			{
				while (repeated[key[count] - 'A'])
					count++;
				table[i][j] = (key[count] == 'J') ? 'I' : key[count];
				repeated[(key[count] > 'I') ? key[count++] - 'B' : key[count++] - 'A'] = true;
			}
		}
	}

	for (int i = 0; i < cipherText.length(); i += 2)
	{
		int x1 = 0, y1 = 0;
		int x2 = 0, y2 = 0;
		Find(x1, y1, table, cipherText[i]);
		Find(x2, y2, table, cipherText[i + 1]);

		if (x1 == x2)
		{
			plainText.push_back(table[(y1 - 1 == -1) ? 4 : y1 - 1][x1] + 32);
			plainText.push_back(table[(y2 - 1 == -1) ? 4 : y2 - 1][x2] + 32);
		}
		else if (y1 == y2)
		{
			plainText.push_back(table[y1][(x1 - 1 == -1) ? 4 : x1 - 1] + 32);
			plainText.push_back(table[y2][(x2 - 1 == -1) ? 4 : x2 - 1] + 32);
		}
		else
		{
			plainText.push_back(table[y2][x1] + 32);
			plainText.push_back(table[y1][x2] + 32);
		}
	}
	/*
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cout << table[i][j] << " ";
		}
		cout << endl;
	}
	*/
	return plainText;
}
//////////////////////////
//doyourbestandthenletgo//
//TECdoyourbestandthenle//
//QK[N[JPQDSE`QTKH_MA_NK//
//////////////////////////
string Vernam(string key, string cipherText)
{
	/*
		int len = cipherText.length() - key.length();
	for (int i = 0; i < len; i++)
	{
		key.push_back(cipherText[i]);
	}

	cout << key << endl;
	for (int i = 0; i < cipherText.length(); i++)
	{
		bitset<5> keyBits(unsigned long(key[i] - 'A'));
		bitset<5> cipherBits(unsigned long (cipherText[i] - 'A'));

		char c = (keyBits^cipherBits).to_ulong();
		c = c > 25 ? c - 26 + 'a' : c + 'a';
		plainText.push_back(c);
	}
	*/
	string plainText;
	bitset<5> cipherBits;
	bitset<5> keyBits;
	for (int i = 0; i < cipherText.length(); i++)
	{
		keyBits = key[i] - 'A';
		cipherBits = cipherText[i] - 'A';
		//cout << keyBits << "  " << cipherBits << endl;
		char c = (keyBits^cipherBits).to_ulong();
		c = c > 25 ? c + 'a' - 26 : c + 'a';
		//cout << c << endl;
		key.push_back(c);
		plainText.push_back(c);
	}
	return plainText;
}
////////////
//45362178//
//doyourbe//
//standthe//
//nletgo  //
//////////////////////////
//RTOUDGYAEDSNOTLONTBHEE//
//////////////////////////
string Row(string key, string cipherText)
{
	const int cipherLen = cipherText.length();
	const int keyLen = key.length();
	int div = cipherLen / keyLen;
	int mod = cipherLen % keyLen;
	string plainText;
	map<int, string> table;
	int index = 0;
	int count = mod > 0 ? div + 1 : div;
	for (int i = 0; i < keyLen; i++)
	{
		table.insert(make_pair(i, cipherText.substr(index, count)));
		index += count;
		count = --mod > 0 ? div + 1 : div;
	}
	for (int i = 0; i < cipherLen; i++)
	{
		plainText.push_back(table[key[i % keyLen] - '1'][0] + 32);
		table[(key[i % keyLen] - '1')].erase(0, 1);
	}

	return plainText;
}
//////////////////////////
//d y u b s a d h n e g //
// o o r e t n t e l t o//
//DYUBSADHNEGOORETNTELTO//
//////////////////////////
string RailFence(string key, string cipherText)
{
	string plainText;
	vector<vector<int>> rails(stoi(key));
	int nowIndex = 0;
	int offset = 1;
	for (int i = 0; i < cipherText.length(); i++)
	{
		rails[nowIndex].push_back(i);
		if (nowIndex == stoi(key) - 1) offset = -1;
		if (nowIndex == 0) offset = 1;
		nowIndex += offset;
	}
	plainText.resize(cipherText.length());
	nowIndex = 0;
	for (int i = 0; i < rails.size(); i++)
	{
		for (int j = 0; j < rails[i].size(); j++)
		{
			plainText[rails[i][j]] = cipherText[nowIndex++] + 32;
		}
	}
	return plainText;
}
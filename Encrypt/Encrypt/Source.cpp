#include <iostream>
#include <string>
#include <vector>

using namespace std;

void select(string Cipher, string key, string cipherText);
string caesar(string key, string cipherText);
string vernam(string key, string cipherText);
string decToBin(int alp);
void setBininVec(string bin, vector<string> &bitAry);
int xorVec(string S1, string S2);
string row(string key, string cipherText);
string rail_fence(string key, string cipherText);
string play_fair(string key, string cipherText);
string checkalpha(string anser);

int main(int argc, char *argv[])
{

	select(argv[1], argv[2], argv[3]);
	system("pause");
}



void select(string Cipher, string key, string cipherText)
{
	string Ans;
	if (Cipher == "caesar")
	{
		Ans = caesar(key, cipherText);
	}
	else if (Cipher == "playfair")
	{
		Ans = play_fair(key, cipherText);
	}
	else if (Cipher == "vernam")
	{
		Ans = vernam(key, cipherText);
	}
	else if (Cipher == "row")
	{
		Ans = row(key, cipherText);
	}
	else if (Cipher == "rail_fence")
	{
		Ans = rail_fence(key, cipherText);
	}
	else {
		cout << "error input";
	}

	cout << Ans << endl;
}



string caesar(string key, string cipherText)
{
	int keyNum = key[0] - '0';
	for (int i = 0; i < cipherText.size(); i++)
	{
		cipherText[i] += keyNum - 'a' + 'A';
		if (cipherText[i] > 'Z')
		{
			cipherText[i] -= 26;
		}
		if (cipherText[i] < 'A')
		{
			cipherText[i] += 26;
		}
	}
	return cipherText;
}

string vernam(string key, string cipherText)
{
	vector<string> cipherTextBit;
	vector<string> keyBit;
	vector<string> end;
	int gap;

	for (int i = 0; i < key.size(); i++) //key大寫 先換小寫 幹你娘有夠麻煩
	{
		key[i] += ('a' - 'A');
	}

	gap = cipherText.size() - key.size();

	for (int i = 0; i < gap; i++) //填充key
	{
		key += cipherText[i];
	}

	setBininVec(cipherText, cipherTextBit);
	setBininVec(key, keyBit);
	cipherText.clear(); //沒用了直接清空拿來裝密文

	for (int i = 0; i < cipherTextBit.size(); i++)
	{

		char a;
		a = xorVec(cipherTextBit[i], keyBit[i]) + 'A';
		cipherText += a;
	}

	return cipherText;
}

void setBininVec(string bin, vector<string> &bitAry)
{
	for (int i = 0; i < bin.size(); i++)
	{
		string s(decToBin(bin[i] - 'a'));
		bitAry.push_back(s);
	}
}

int xorVec(string S1, string S2)
{
	int sum = 0;
	for (int i = 0; i < 5; i++)
	{
		if (S1[i] != S2[i])
		{
			sum += pow(2, 4 - i);
		}
	}
	return sum;
}

string decToBin(int alp)
{
	string bin;
	for (int i = 0; i < 5; i++)
	{
		bin += to_string(alp % 2);
		alp /= 2;
	}

	for (int i = 0; i < bin.size() / 2; i++)
	{
		char temp = bin[i];
		bin[i] = bin[bin.size() - i - 1];
		bin[bin.size() - i - 1] = temp;
	}
	return bin;
}

string row(string key, string plaintext)
{
	int digit;
	string ciphertest;
	digit = key.size();
	string* row = new string[digit];

	for (int i = 0; i < plaintext.size(); i++)
	{
		row[i%digit] += plaintext[i];
	}

	for (int i = 0; i < digit; i++)
	{
		int position = key.find(to_string(i + 1), 0);
		ciphertest += row[position];
	}

	for (int i = 0; i < ciphertest.size(); i++)
	{
		ciphertest[i] = ciphertest[i] - 'a' + 'A';
	}

	return ciphertest;
}

string rail_fence(string key, string plaintext)
{
	string ciphertext = "";
	int keyNum = key[0] - '0';
	int groupindex = 0;
	int control = -1;

	string *group = new string[keyNum];

	for (int i = 0; i < plaintext.size(); i++)
	{
		if (groupindex == 0 || groupindex == (keyNum - 1))
		{
			control *= -1;
		}
		group[groupindex] += plaintext[i];
		groupindex += control;
	}


	for (int i = 0; i < keyNum; i++)
	{
		ciphertext += group[i];
	}

	for (int i = 0; i < ciphertext.size(); i++)
	{
		ciphertext[i] += ('A' - 'a');
	}

	return ciphertext;
}

string play_fair(string key, string plaintext)
{
	string Encrypt;
	string alphabet;
	char table[5][5];

	//刪key重複
	for (int i = 0; i < key.size(); i++)
	{
		bool dup = false;
		for (int j = 0; j < alphabet.size(); j++)
		{
			if (alphabet[j] == key[i])
			{
				dup = true;
			}
		}
		if (!dup)
			alphabet += key[i];
	}
	//排順序
	for (int i = 0; i < 26; i++)
	{
		bool dup = false;
		for (int j = 0; j < alphabet.size(); j++)
		{
			if (alphabet[j] == ('A' + i))
			{
				dup = true;
			}
		}
		if (!dup)
			alphabet += ('A' + i);
	}
	//建表
	int k = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (alphabet[i * 5 + j + k] == 'J')
				k = 1;

			table[i][j] = alphabet[i * 5 + j + k];
		}
	}
	//TEST CODE
	/*for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cout << table[i][j];
		}
		cout << endl;
	}*/

	//把key的J拿掉
	for (int i = 0; i < plaintext.length(); i++)
	{
		if (plaintext[i] == 'j')
			plaintext[i] = 'i';
	}

	//倆倆分組建表
	for (int i = 0; i < plaintext.length(); i++)
	{
		int x1, x2, y1, y2;
		//找位置
		for (int j = 0; j < 5; j++)
		{
			for (int k = 0; k < 5; k++)
			{
				if (table[j][k] == plaintext[i] - 'a' + 'A')
				{
					x1 = j;
					y1 = k;
				}
				if (table[j][k] == plaintext[i + 1] - 'a' + 'A')
				{
					x2 = j;
					y2 = k;
				}
			}
		}

		if (x1 == x2)
		{
			if (y1 == 4)
			{
				Encrypt += table[x1][0];
			}
			else
			{
				Encrypt += table[x1][y1 + 1];
			}
			if (y2 == 4)
			{
				Encrypt += table[x2][0];
			}
			else
			{
				Encrypt += table[x2][y2 + 1];
			}
		}
		else if (y1 == y2)
		{
			if (x1 == 4)
			{
				Encrypt += table[0][y1];
			}
			else
			{
				Encrypt += table[x1 + 1][y1];
			}
			if (x2 == 4)
			{
				Encrypt += table[0][y2];
			}
			else
			{
				Encrypt += table[x2 + 1][y2];
			}
		}
		else
		{
			Encrypt += table[x2][y1];
			Encrypt += table[x1][y2];
		}
		i++;
	}

	return Encrypt;
}

string checkalpha(string anser)
{
	string Ans;
	for (int i = 0; i < anser.size(); i++)
	{
		if (anser[i] >= 'A' && anser[i] <= 'Z')
		{
			Ans += anser[i];
		}
	}
	return Ans;
}
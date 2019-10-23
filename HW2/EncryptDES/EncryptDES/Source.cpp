#include <iostream>
#include <string>
#include <vector>


using namespace std;
//變數宣告
vector<int> Ip = { 58,50,42,34,26,18,10,2,
				   60,52,44,36,28,20,12,4,
				   62,54,46,38,30,22,14,6,
				   64,56,48,40,32,24,16,8,
				   57,49,41,33,25,17,9,1,
				   59,51,43,35,27,19,11,3,
				   61,53,45,37,29,21,13,5,
				   63,55,47,39,31,23,15,7 };




string rePosition(string text,vector<int> &a);
string iniPlaintext(string text);
string hecTobin(string hex);
int main()
{
	string ini;
	iniPlaintext(ini);
	ini = hecTobin("0xabcdef0123456789");
	cout << ini << endl;
	cout << rePosition(ini,Ip);
	system("pause");
}

string iniPlaintext(string text) //初始化陣列
{
	text.clear();
	for (int i = 0; i < 64; i++)
	{
		 text += '2'; //只會有1 跟 0 所以跑出2代表有誤
	}
	return text;
}

string hecTobin(string hex) //16 進位轉二進位
{
	string bin;
	for (int i = 17; i > 1; i--)
	{
		int num;
		if(hex[i] >= '0' && hex[i] <= '9')
			num = hex[i] - '0';
		else if(hex[i] >= 'a' && hex[i] <= 'f')
			num = hex[i] - 'a' + 10;
		else if(hex[i] >= 'A' && hex[i] <= 'F')
			num = hex[i] - 'A' + 10;

		for (int time = 0; time < 4; time++)
		{
			bin += to_string(num & 1)[0];
			num = num >> 1;
		}
	}

	for (int i = 0; i < 32; i++)
	{
		char temp = bin[i];
		bin[i] = bin[63 - i];
		bin[63 - i] = temp;
	}
	return bin;
}

string rePosition(string text,vector<int> &a)//照表重排
{
	string translated;
	for (int i = 0; i < a.size(); i++)
	{
		translated += text[a[i]-1];
	}
	return translated;
}
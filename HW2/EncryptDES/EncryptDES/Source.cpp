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
vector<int> Fp = { 40,8,48,16,56,24,64,32,
				   39,7,47,15,55,23,63,31,
				   38,6,46,14,54,22,62,30,
				   37,5,45,13,53,21,61,29,
				   36,4,44,12,52,20,60,28,
				   35,3,43,11,51,19,59,27,
				   34,2,42,10,50,18,58,26,
				   33,1,41,9,49,17,57,25 };
vector<int> E = { 32,1,2,3,4,5,
				  4,5,6,7,8,9,
				  8,9,10,11,12,13,
				  12,13,14,15,16,17,
				  16,17,18,19,20,21,
				  20,21,22,23,24,25,
				  24,25,26,27,28,29,
				  28,29,30,31,32,1,};
vector<int> S1 = { 14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
				   0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
				   4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
				   15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13};
vector<int> S2 = { 15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
				   3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
				   0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
				   13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9,};
vector<int> S3 = { 10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
				   13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
				   13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
				   1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12, };
vector<int> S4 = { 7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
				   13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
				   10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
				   3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14,};
vector<int> S5 = { 2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
				   14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
				   4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
				   11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3, };
vector<int> S6 = { 12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
				   10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
				   9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
				   4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13,};
vector<int> S7 = { 4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
				   13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
				   1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
				   6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12,};
vector<int> S8 = { 13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
				   1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
				   7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
				   2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11,};
vector<int> CP1 = {
	57,49,41,33,25,17,9,
	1,58,50,42,34,26,18,
	10,2,59,51,43,35,27,
	19,11,3,60,52,44,36,
	63,55,47,39,31,23,15,
	7,62,54,46,38,30,22,
	14,6,61,53,45,37,29,
	21,13,5,28,20,12,4,
};
vector<int> CP2 = {
	14,17,11,24,1,5,
	3,28,15,6,21,10,
	23,19,12,4,26,8,
	16,7,27,20,13,2,
	41,52,31,37,47,55,
	30,40,51,45,33,48,
	44,49,39,56,34,53,
	46,42,50,36,29,32,
};
vector<int> P = {
	16,7,20,21,29,12,28,17,
	1,15,23,26,5,18,31,10,
	2,8,24,14,32,27,3,9,
	19,13,30,6,22,11,4,25,
};



//function 宣告
string rePosition(string text,vector<int> &a);
string iniPlaintext(string text,int length);
string hecTobin(string hex);
string PartofString(string text, int first, int end);
string xorVec(string S1, string S2);
string rotateShift(string key, int time);
string Sbox(string textR);
string SSbox(string textR,int first, int end , vector<int> &S);
string binToHec(string text);
int bintoDec(string num);

int main(int argc, char *argv[])
{
	string inputtext;
	string inputkey;

	inputkey = argv[1];
	inputtext = argv[2];

	int shiftTime;
	string ini;
	iniPlaintext(ini,64);
	ini = hecTobin(inputtext);
	ini = rePosition(ini, Ip);
	string key; //第一次輸入的64bits key
	iniPlaintext(key, 64);
	key = hecTobin(inputkey);
	key = rePosition(key, CP1); //第一次換位
	for (int i = 0; i < 16; i++)
	{
		if (i == 0 || i == 1 || i == 8 || i == 15)
		{
			shiftTime = 1;
		}
		else
		{
			shiftTime = 2;
		}
		string keyL;
		string keyR;
		string Roundkey;


		string R;
		string L;
		string RE; //右邊展開過的
		//明文分左右
		L = PartofString(ini, 0, 32);
		R = PartofString(ini, 32, 64);
		//右邊加長
		RE = rePosition(R, E);
		//key schedule
		
		//key分左右
		keyL = PartofString(key, 0, 28);
		keyR = PartofString(key, 28, 56);
		//依次數shift
		keyL = rotateShift(keyL, shiftTime);
		keyR = rotateShift(keyR, shiftTime);
		//獲得新keybase
		key.clear();
		key += keyL;
		key += keyR;
		//這輪的子key
		Roundkey = rePosition(key, CP2);//第二次換位

		//明文右半跟子key XOR
		RE = xorVec(RE, Roundkey);

		//SBOX
		RE = Sbox(RE);

		//跟P做轉換
		RE = rePosition(RE, P);
		
		//跟左半XOR
		RE = xorVec(RE, L);

		//新的明文 要左右相反
		ini.clear();
		ini += R;
		ini += RE;

	}

	string lastL;
	string lastR;
	lastL = PartofString(ini, 0, 32);
	lastR = PartofString(ini, 32, 64);
	ini.clear();
	ini += lastR;
	ini += lastL;
	ini = rePosition(ini, Fp); //最後轉換
	ini = binToHec(ini);
	cout << ini << endl;


	
	system("pause");


}


//初始化陣列
string iniPlaintext(string text, int length)
{
	text.clear();
	for (int i = 0; i < length; i++)
	{
		 text += '2'; //只會有1 跟 0 所以跑出2代表有誤
	}
	return text;
}
//16 進位轉二進位
string hecTobin(string hex) 
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
//照表重排
string rePosition(string text,vector<int> &a)
{
	string translated;
	for (int i = 0; i < a.size(); i++)
	{
		translated += text[a[i]-1];
	}
	return translated;
}
//分割字串
string PartofString(string text, int first, int end)
{
	string part;
	for (int i = first; i < end; i++)
	{
		part += text[i];
	}
	return part;
}
//Xor實作
string xorVec(string S1, string S2)
{
	string Xor;
	for (int i = 0; i < S1.size(); i++)
	{
		if (S1[i] != S2[i])
		{
			Xor += '1';
		}
		else
		{
			Xor += '0';
		}
	}
	return Xor;
}
//key always 28 bits
string rotateShift(string key, int time) 
{
	string temp;
	string shiftKey;
	for (int i = 0; i < time; i++)
	{
		temp += key[i];
	}
	for (int i = time; i < 28 ; i++)
	{
		shiftKey += key[i];
	}
	shiftKey += temp;
	return shiftKey;
}

int bintoDec(string num)
{
	int sum = 0;
	for (int i = 0; i < num.size(); i++)
	{
		sum += pow(2, (num.size() - i - 1))*(num[i] - '0');
	}
	return sum;
}

string Sbox(string textR)
{
	string result;
	result += SSbox(textR, 0, 6, S1);
	result += SSbox(textR, 6, 12, S2);
	result += SSbox(textR, 12, 18, S3);
	result += SSbox(textR, 18, 24, S4);
	result += SSbox(textR, 24, 30, S5);
	result += SSbox(textR, 30, 36, S6);
	result += SSbox(textR, 36, 42, S7);
	result += SSbox(textR, 42, 48, S8);
	return result;
}

string SSbox(string textR, int first, int end, vector<int> &S)
{
	string Result;
	string temp;
	string rowTemp;
	int Row;
	int Col;
	temp = PartofString(textR, first, end);
	rowTemp += temp[0];
	rowTemp += temp[5];
	Row = bintoDec(rowTemp);
	rowTemp.clear();
	for (int i = 1; i < 5; i++)
	{
		rowTemp += temp[i];
	}
	Col = bintoDec(rowTemp);
	//============================= 
	temp.clear();
	int fuckNum = S[Row * 16 + Col];
	for (int time = 0; time < 4; time++)
	{
		temp += to_string(fuckNum & 1)[0];
		fuckNum = fuckNum >> 1;
	}

	for (int i = 0; i < 2; i++)
	{
		char swap = temp[i];
		temp[i] = temp[3 - i];
		temp[3 - i] = swap;
	}
	//================================
	return temp;
}

string binToHec(string text)
{
	string result = "0x";
	for (int j = 0; j < 16; j++)
	{
		int sum = 0;
		for (int i = 0; i < 4; i++)
		{
			sum += pow(2, 3 - i)*(text[j * 4 + i] - '0');
		}
		if (sum <= 9)
		{
			result += to_string(sum);
		}
		else
		{
			sum += ('A' - 10);
			result += sum;
		}
	}
	return result;

}
#include "iostream"
#include "string"
#include "algorithm"
using namespace std;

string Encrypt(string plaintext, int n, int e);
string Decrypt(string plaintext, int n, int e);
int getNum(int num,int pow,int n);
void switchcase(char **argv);
int main(int argc, char **argv)
{
	if(argc > 1)
	  switchcase(argv);

	/*cout<<Encrypt("apple", 187, 3);
	cout << endl;
	cout<<Decrypt("113/184/184/80/118/", 187, 107);*/
	system("pause");
}

string Encrypt(string plaintext,int n,int e)
{
	string cipher;
	string cipherval;
	for (int i = 0; i < plaintext.length(); i++)
	{
		int temp;
		cipherval = to_string(getNum(plaintext[i], e, n));
		cipher += cipherval;
		cipher += "/";
	}
	return cipher;
}

string Decrypt(string plaintext, int n, int e)
{
	char flag = '/';
	int position = 0;
	int start = 0;
	string cipher;
	char cipherchar;
	while ((position = plaintext.find_first_of(flag, position)) != string::npos)
	{

		int charnum = stoi(plaintext.substr(start, position - start));
		cipherchar = getNum(charnum, e, n);
		cipher += cipherchar;
		position++;
		start = position;
	}

	return cipher;
}

void switchcase(char **argv)
{
	int p = 11;
	int q = 17;
	int n = p * q;
	int e = 3;
	int d = 107;
	string temp = argv[1];
	if (temp == "init")
	{
		cout << "p: " << p << " q: " << q << " n: " << n << " e: " << e << " d: " << d;
	}
	else if (temp == "-e")
	{
		cout<<Encrypt(argv[2], stoi(argv[3]), stoi(argv[4]));
	}
	else if (temp == "-d")
	{
		cout<< Decrypt(argv[2], stoi(argv[3]), stoi(argv[4]));
	}
}


int getNum(int num, int pow ,int n)
{
	int ans = num;
	for (int i = 1; i < pow; i++)
	{
		ans *= num;
		ans %= n;
	}
	return ans;
}

#include <iostream>
#include <string>

//Создать функции для кодирования и декодирования строки используя “Rail Fence Cipher”.
//“WEAREDISCOVEREDFLEEATONCE” --> “WECRLTEERDSOEEFEAOCAIVDEN”

using namespace std;

void encryption(string& str)
{
    int length = str.length();
//“Rail Fence Cipher”
    string str1(length, '\t');
    string str2(length, '\t');
    string str3(length, '\t');
    for(int i = 0; i < length; i++)
    {
        if(i % 4 == 0) str1[i] = str[i];
        else if(i % 2 == 1) str2[i] = str[i];
        else str3[i] = str[i];
    }

    string Tstr1(length, '.');
    string Tstr2(length, '.');
    string Tstr3(length, '.');
    for(int i = 0; i < length; i++)
    {
        if(i % 4 == 0) Tstr1[i] = str[i];
        else if(i % 2 == 1) Tstr2[i] = str[i];
        else Tstr3[i] = str[i];
    }
    cout << "\tOutputting test strings\n\t" << Tstr1 << "\n\t" << Tstr2 << "\n\t" << Tstr3 << endl;



    int j = 0;

    for(int i = 0; i < length; i++) if(str1[i] != '\t') str[j++] = str1[i];
    for(int i = 0; i < length; i++) if(str2[i] != '\t') str[j++] = str2[i];
    for(int i = 0; i < length; i++) if(str3[i] != '\t') str[j++] = str3[i];

}

void decryption(string& str)
{
    int length = str.length();
//“Rail Fence Cipher”
    string str1(length, '.');
    string str2(length, '.');
    string str3(length, '.');

    int firstN = ((length - 1) / 4) + 1;
    int secondN = length / 2;
    int thirdN = (length + 1) / 4;

    //first
    int j = 0;

    for(int n = 0, i = 0; n < firstN; i += 4, n++) str1[i] = str[j++];
    for(int n = 0, i = 1; n < secondN; i += 2, n++) str2[i] = str[j++];
    for(int n = 0, i = 2; n < thirdN; i += 4, n++) str3[i] = str[j++];

    cout << "\tTransformation back in decryption\n\t" << str1 << "\n\t" << str2 << "\n\t" << str3 << endl;

    for(int i = 0; i < length; i++)
    {
        if(i % 4 == 0) str[i] = str1[i];
        else if(i % 2 == 1) str[i] = str2[i];
        else str[i] = str3[i];
    }
}


int main()
{
    cout << "Enter your string:";
    string str;
    getline(cin, str);

    if (!str.empty())
    {
        encryption(str);
        cout << "Encrypted string: " << str << endl;
        decryption(str);

        cout << "Decrypted string: " << str << endl;

    }
    else cout << "Your string is empty\n";

    return 0;
}
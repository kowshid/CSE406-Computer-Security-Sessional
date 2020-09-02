#include <bits/stdc++.h>

using namespace std;

#define N 8

int PI[64] =
{
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

int CP_1[] =
{
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4
};

int CP_2[] =
{
    14, 17, 11, 24, 1, 5, 3, 28,
    15, 6, 21, 10, 23, 19, 12, 4,
    26, 8, 16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55, 30, 40,
    51, 45, 33, 48, 44, 49, 39, 56,
    34, 53, 46, 42, 50, 36, 29, 32
};

int SHIFT[] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};

int E[] =
{
    32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1
};

int P[] =
{
    16, 7, 20, 21, 29, 12, 28, 17,
    1, 15, 23, 26, 5, 18, 31, 10,
    2, 8, 24, 14, 32, 27, 3, 9,
    19, 13, 30, 6, 22, 11, 4, 25
};

int PI_1[] =
{
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25
};

int PI_2[] =
{
    35, 38, 46, 6, 43, 40, 14, 45,
    33, 19, 26, 15, 23, 8, 22, 10,
    12, 11, 5, 25, 27, 21, 16, 31,
    28, 32, 34, 24, 9, 37, 2, 1
};

string key0, text0;
vector <string> textVector; //8 character chunk of whole input
vector <string> bsVector; //64 bitstream chunk of textVectors
vector <string> transposedVector; //64 bitstream after using PI matrix for transposition
vector <string> keyVector; //generatedKeys with initial 64 bit key at index 0 and 56 bit key at index 1
int chunks;
string encryptedBits, encryptedText, decryptedBits, decryptedText;

string charToBits(char c)
{
    unsigned char ch = c;
    string bits = "";
    int charASCII = (int) ch;

    //cout << charASCII << endl;

    for(int i = 0; i < N; i++)
    {
        bits.push_back(charASCII%2+48);
        charASCII = charASCII/2;
    }

    reverse(bits.begin(), bits.end());

    //cout << "bits for " << c << " : " << bits << endl;

    return bits;
}

string stringToBits(string str)
{
    string bitStream = "";

    for(int i = 0; i < N; i++)
    {
        bitStream += charToBits(str[i]);
    }

    //cout << "bitStream for " << str << " : " << bitStream << endl;

    return bitStream;
}

string padding(string text)
{
    int textLen = text.length();

    if(textLen%N != 0)
    {
        int req = N -  (textLen % N);
        for(int i = 0; i < req; i++)
        {
            text.push_back('0');
        }
    }

    //cout << text << endl;

    return text;
}

string antiPadding (string text)
{
    int len = text.length() - 1;

    while(text[len] == '0')
    {
        text[len] = ' ';
        len--;
    }

    return text;
}

void textToBitstreams(string str)
{
    string text = padding(str);

    //cout << text << endl;

    int textLen = text.length();

    //cout << textLen << endl;

    chunks = textLen/N;

    cout << "chunks : " << chunks << endl;

    textVector.resize(chunks);
    bsVector.resize(chunks);
    transposedVector.resize(chunks);

    for(int i = 0; i < chunks; i++)
    {
        for(int j = 0; j < N; j++)
        {
            textVector[i].push_back(text[i*N+j]);
        }
    }

    for(int i = 0; i < chunks; i++)
    {
        bsVector[i] = stringToBits(textVector[i]);
        //cout << bsVector[i] << endl;
    }
}

string bsTransposition(string bs)
{
    string transposed = "";
    transposed.resize(64);

    for(int i = 0; i < 64; i++)
    {
        transposed[i] = bs[PI[i] - 1];
    }

    return transposed;
}

void transposedVecGenerator()
{
    for(int i = 0; i < chunks; i++)
    {
        transposedVector[i] = bsTransposition(bsVector[i]);
        //cout << "transposed " << transposedVector[i] << endl;
    }
}

string _64to56(string key)
{
    string key1 = "";
    for(int i = 0; i < 56; i++)
    {
        key1.push_back(key[CP_1[i] - 1]);
    }

    //cout << key1 << endl;

    return key1;
}

string leftShift(string str, int place)
{
    int strLen = str.length();
    string temp = "";
    string shiftedString = "";

    for(int i = 0; i < place; i++)
    {
        temp.push_back(str[i]);
    }

    //cout << temp << endl;

    for(int i = place; i < strLen; i++)
    {
        shiftedString.push_back(str[i]);
    }

    shiftedString += temp;
    //cout << shiftedString << endl;
    return shiftedString;
}

string _56to48(string key)
{
    string newKey = "";
    for(int i = 0; i < 48; i++)
    {
        newKey.push_back(key[CP_2[i] - 1]);
    }
    //cout << newKey << endl;

    return newKey;
}

string keyGenerator(string key, int place)
{
    string left = "";
    string right = "";
    string newKey = "";

    for(int i = 0; i < 28; i++)
    {
        left.push_back(key[i]);
        right.push_back(key[28+i]);
    }

    //cout << left << endl;
    //cout << right << endl;
    left = leftShift(left, place);
    right = leftShift(right, place);

    newKey = left + right;

    newKey = _56to48(newKey);

    //cout << newKey << endl;
    return newKey;
}

void keyVecGeneration()
{
    for(int i = 0; i < 16; i++)
    {
        keyVector[i + 2] = keyGenerator(keyVector[1], SHIFT[i]);
        //cout << keyVector[i+2] << endl;
    }
}

string encryptionIteration(string str, int iteration)
{
    string oldL = "", oldR = "", newL = "", newR = "";
    string temp1 = "", temp2 = "", temp3 = "", temp4 = "", temp5 = "";

    for(int i = 0; i < 32; i++)
    {
        oldL.push_back(str[i]);
        oldR.push_back(str[32+i]);
    }

    newL = oldR;

    for(int i = 0; i < 48; i++)
    {
        temp1.push_back(oldR[E[i] - 1]);
    }

    for(int i = 0; i < 48; i++)
    {
        if(temp1[i] == keyVector[iteration + 2][i])
            temp2.push_back('1');
        else
            temp2.push_back('0');
    }

    for(int i = 0; i < 32; i++)
    {
        temp3.push_back(temp2[PI_2[i] - 1]);
    }

    for(int i = 0; i < 32; i++)
    {
        temp4.push_back(temp3[P[i] - 1]);
    }

    //XOR of  P box and L(i-1)
    for(int i = 0; i < 32; i++)
    {
        if(temp4[i] == oldL[i])
            newR.push_back('1');
        else
            newR.push_back('0');
    }

    string result = newL + newR;

    return result;
}

string encryption(string str)
{
    string text = str, temp = "", result = "";
    string oldL = "", oldR = "", newL = "", newR = "";

    for(int i = 0; i < 16; i++)
    {
        text = encryptionIteration(text, i);
    }

    for(int i = 0; i < 32; i++)
    {
        oldL.push_back(text[i]);
        oldR.push_back(text[32+i]);
    }

    newL = oldR;
    newR = oldL;

    temp = newL + newR;

    for(int i = 0; i < 64; i++)
    {
        result.push_back(temp[PI_1[i] - 1]);
    }

    //cout<<"result "<<result<<endl;

    return result;
}

string decryption(string str)
{
    string text = str, temp = "", result = "";
    string oldL = "", oldR = "", newL = "", newR = "";
    int len;

    for(int i = 15; i >= 0; i--)
    {
        text = encryptionIteration(text, i);
    }

    for(int i = 0; i < 32; i++)
    {
        oldL.push_back(text[i]);
        oldR.push_back(text[32+i]);
    }

    newL = oldR;
    newR = oldL;

    temp = newL + newR;

    for(int i = 0; i < 64; i++)
    {
        result.push_back(temp[PI_1[i] - 1]);
    }

    //cout<<"result "<<result<<endl;

    return result;
}

string bitsToChar(string str)
{
    int multi = 1, result = 0;
    for(int i = 7; i >= 0; i--)
    {
        if(str[i] == '1')
            result += multi;
        multi = multi*2;
    }

    char c = (char) result;
    string strresult = "";
    strresult.push_back(c);
    //cout << strresult << endl;
    return strresult;
}

string bitsToString(string str)
{
    string temp = "", result = "";
    for(int i = 0; i < chunks*N; i++)
    {
        temp.clear();
        for(int j = 0; j < N; j++)
        {
            temp.push_back(str[i*N+j]);
        }

        result += bitsToChar(temp);
    }

    return result;
}

int main()
{
    freopen("in.txt", "r", stdin); //input is taken from a file
    freopen("outputDES1505102.txt", "w", stdout); //output is given in a file
    keyVector.resize(18);

    //string encryptedBits = "", encryptedText = "";
    //cout << "Please, enter your key: ";
    getline(cin, key0); //key must be of 8 characters
    //cout << key0 << endl;
    keyVector[0] = stringToBits(key0);
    // cout << keyVector[0] << endl;
    //cout << "Please, enter your text: ";
    getline(cin, text0);
    //cout << text0 << endl;

    textToBitstreams(text0);
    transposedVecGenerator();
    keyVector[1] = _64to56(keyVector[0]);
    keyVecGeneration();

    for(int i = 0; i < chunks; i++)
    {
        encryptedBits += encryption(transposedVector[i]);
    }

    cout << "encryptedBits : " << encryptedBits << endl;

    //encryplen = encryptedBits.length();

    encryptedText = bitsToString(encryptedBits);

    cout << "encryptedText : " << encryptedText << endl;

    textVector.clear();
    bsVector.clear();
    transposedVector.clear();

    textToBitstreams(encryptedText);
    transposedVecGenerator();

    for(int i = 0; i < chunks; i++)
    {
        decryptedBits += decryption(transposedVector[i]);
    }

    cout << "decryptedBits : " << decryptedBits << endl;

    //encryplen = encryptedBits.length();

    decryptedText = bitsToString(decryptedBits);
    decryptedText = antiPadding(decryptedText);

    cout << "decryptedText : " << decryptedText << endl;

    return 0;
}

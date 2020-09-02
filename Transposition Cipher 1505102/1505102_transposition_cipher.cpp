#include<bits/stdc++.h>

using namespace std;

#define N 4

string format(string str)
{
    int len = str.length() - 1;
    if(str[len] == ',')
        str[len] = '\0';

    return str;
}

int main()
{
    freopen("transposition-102.txt", "r", stdin);
    freopen("outputTC102.txt", "w", stdout);

    int k = 5, m, n, mx = 0, cipherLen; //k = 5; //key length, column count, hard coded
    //k = 6 for sample sample_transposition_cipher.txt, 5 for most of other given text file to other roll
    int order[k];
    string cipher, str, ans, hints[N];
    vector <string> vec;
    //cipher = "EAEAKWEATTTATVSECPHURLENXTLRLADOEAAINWRETSCNDTFTIDDFWTANTNOPCCHOIEHOEAILNMXEOITTMHZEOOTBHNAEIARNATOXHTCLCAVPRSNTIAIHTKTQEUTOE";
    //string h[] = {"headquarter",  "checkpoint", "attention", "contact"};

    cin >> cipher;

    for(int i = 0; i < N; i++)
    {
        cin >> hints[i];
        hints[i] = format(hints[i]);
    }

//    cout << "cipher : " << cipher << endl << "\nkeys : ";
//    for(int i = 0; i < N; i++)
//    {
//        cout << i << " " << h[i] << " ";
//    }

    cipherLen = cipher.length();

    for(int i = 0; i < cipherLen; i++) //converting the whole cipher to lower case as hints are lower case
    {
        cipher[i] = tolower(cipher[i]);
    }

    n = cipherLen/k; //number of chunks, row count

    for(int i = 0; i < cipherLen; i += n) //dividing the chunks
    {
        str = "";

        for(int j = i; j < i + n; j++)
        {
            str.push_back(cipher[j]);
        }

        vec.push_back(str);
    }

    int arr[k]; //for using in permutation

    for(int i = 0; i < k; i++)
    {
            arr[i] = i;
    }

    //trying out all possible permutation
    do{
        str = "";

        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < k; j++)
            {
                str += vec[arr[j]][i];
            }
        }

        int c = 0;

        for(int i = 0; i < N; i++)
        {
            if(str.find(hints[i]) == string :: npos)
                continue;

            c++;
        }

        if(c > mx)
        {
            mx = c;

            for(int i = 0; i < k; i++)
            {
                order[i] = arr[i];
            }

            ans = str;
        }
    }while(next_permutation(arr, arr + k));

    //printing
    cout << "decyphered text : \n" << ans << "\norder is ";

    for(int i = 0; i < k; i++)
    {
        cout << order[i] + 1 <<" ";
    }

    return 0;
}

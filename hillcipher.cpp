#include "hillcipher.h"

bool HillCipher::setKey(int k[N][N])
{
    Matrix tmp = Matrix(k),rev;

    if( tmp.inverse(rev) )
    {
        encryptKey = Matrix(k);
        decryptKey = rev;
        return true;
    }

    return false;
}

bool HillCipher::encrypt(std::string plain, std::string &cipher)
{
    if(plain.empty())
        return false;

    std::string result;

    int len = plain.size();

    std::vector<std::vector<int>> v;
    for(int i = 0 ; i<len; )
    {
        std::string sub = plain.substr(i,3);

        std::vector<int> tmp(3);
        int cnt = 0;
        for(int j = 0 ; j<3 && j<int(sub.size());j++)
        {
            tmp[j] = sub[j] - 'A';
            cnt++;
        }
        while(cnt<3)
            tmp[cnt++] = spx;

        v.push_back(tmp);

        i += sub.size();
    }

    int vlen = v.size();

    for(int i = 0 ;i<vlen;i++)
    {
        std::vector<int> tmp = v[i];
        std::vector<int> r = encryptKey * tmp;
        result.append(alphabet[r[0]]+alphabet[r[1]]+alphabet[r[2]]);
    }

    cipher = result;

    return true;
}

bool HillCipher::decrypt(std::string cipher, std::string &plain)
{
    if(cipher.empty())
        return false;

    std::string result;

    int len = cipher.size();

    std::vector<std::vector<int>> v;
    for(int i = 0 ; i<len; )
    {
        std::string sub = cipher.substr(i,3);

        std::vector<int> tmp(3);
        int cnt = 0;
        for(int j = 0 ; j<3 && j<int(sub.size());j++)
        {
            tmp[j] = sub[j] - 'A';
            cnt++;
        }
        while(cnt<3)
            tmp[cnt++] = spx;

        v.push_back(tmp);

        i += sub.size();
    }

    int vlen = v.size();

    for(int i = 0 ;i<vlen;i++)
    {
        std::vector<int> tmp = v[i];
        std::vector<int> r = decryptKey * tmp;
        result.append(alphabet[r[0]]+alphabet[r[1]]+alphabet[r[2]]);
    }

    plain = result;
    return true;
}

#include "caesarcipher.h"

bool CaesarCipher::encrypt(std::string plain, std::string& cipher)
{
    if( plain.empty() )
        return false;

    int len = plain.size();

    std::string result;

    for(int i = 0;i<len;i++)
    {
        int num = std::toupper(plain[i]) - 'A';
        int nxt = (num+offset+26) % 26;
        result.append(alphabet[nxt]);
    }

    cipher = result;

    return true;
}

bool CaesarCipher::decrypt(std::string cipher, std::string& plain)
{
    if( cipher.empty() )
        return false;

    int len = cipher.size();

    std::string result;

    for(int i = 0;i<len;i++)
    {
        int num = std::toupper(cipher[i]) - 'A';
        int nxt = (num-offset+26) % 26;
        result.append(alphabet[nxt]);
    }

    plain = result;

    return true;
}

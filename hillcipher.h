#ifndef HILLCIPHER_H
#define HILLCIPHER_H

#include <string>
#include <vector>

#include <QDebug>

#include "matrix.h"

class HillCipher
{
public:
    HillCipher() {}

    static const int N = 3;

    bool setKey(int k[N][N]);
    bool encrypt(std::string plain,std::string& cipher);
    bool decrypt(std::string cipher,std::string& plain);


private:

    Matrix encryptKey,decryptKey;

    int spx = 23;

    const std::vector<std::string> alphabet = {
        "A","B","C","D","E","F","G",
        "H","I","J","K","L","M","N",
        "O","P","Q","R","S","T","U",
        "V","W","X","Y","Z"
    };

};

#endif // HILLCIPHER_H

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

    bool setKey(int k[N][N]); // 计算矩阵的有效性，有效则更新加密矩阵和解密矩阵
    bool encrypt(std::string plain,std::string& cipher);
    bool decrypt(std::string cipher,std::string& plain);


private:

    Matrix encryptKey,decryptKey; // 加密矩阵和解密矩阵

    int spx = 23; // x 是第24个字母，作为特殊判断

    const std::vector<std::string> alphabet = {
        "A","B","C","D","E","F","G",
        "H","I","J","K","L","M","N",
        "O","P","Q","R","S","T","U",
        "V","W","X","Y","Z"
    };

};

#endif // HILLCIPHER_H

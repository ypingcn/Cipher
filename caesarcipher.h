#ifndef CAESARCIPHER_H
#define CAESARCIPHER_H

#include <QObject>

#include <string>
#include <vector>

class CaesarCipher
{
public:
    CaesarCipher() {} ;

    bool encrypt(std::string plain,std::string &cipher);
    bool decrypt(std::string cipher,std::string &plain);

private:

    std::vector<std::string> alphabet = {
        "A","B","C","D","E","F","G",
        "H","I","J","K","L","M","N",
        "O","P","Q","R","S","T","U",
        "V","W","X","Y","Z"
    };
    const int offset = 3;
};

#endif // CAESARCIPHER_H

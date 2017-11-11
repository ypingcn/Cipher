#ifndef PLAYFAIRCIPHER_H
#define PLAYFAIRCIPHER_H

#include <string>
#include <vector>

#include <QString>
#include <QDebug>

class PlayfairCipher
{
public:
    PlayfairCipher() {}

    bool encrypt(std::string plain,std::string& cipher);
    bool decrypt(std::string cipher,std::string& plain);

    void setWord(std::string w) { word = w; updateMatrix(); }
    void updateMatrix();


private:

    std::pair<int,int> getLocation(int alpha);
    int getAlpha(std::pair<int,int> location);

    const std::vector<std::string> alphabet = {
        "A","B","C","D","E","F","G",
        "H","I","J","K","L","M","N",
        "O","P","Q","R","S","T","U",
        "V","W","X","Y","Z"
    };

    std::string word;
    int spi = 8,spj = 9,spk = 10;

    static const int N = 5;
    int matrix[N][N],have;
};

#endif // PLAYFAIRCIPHER_H

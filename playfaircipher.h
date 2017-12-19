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

    std::pair<int,int> getLocation(int alpha); // 字母的位置，第一个是行，第二个是列
    int getAlpha(std::pair<int,int> location); // 求某行某列上的字母

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

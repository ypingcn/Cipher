#include "playfaircipher.h"

bool PlayfairCipher::encrypt(std::string plain, std::string& cipher)
{
    if(plain.empty())
        return false;

    std::string result;

    std::vector<std::pair<int,int>> v;

    int len = plain.size();

    // 每两个字母分一组，非字母略过
    for(int i = 0;i<len; )
    {
        if(!isalpha(plain[i]))
        {
            i++;
            continue;
        }

        int num1 = toupper(plain[i]) - 'A',num2;
        if(i+1 < len)
            num2 = toupper(plain[i+1]) - 'A';
        else
        {
            v.push_back(std::make_pair(num1,spk));
            break;
        }

        if(num1 == spi || num1 == spj)
            num1 = spi;
        if(num2 == spi || num2 == spj)
            num2 = spi;

        // 两个数字相同则拆分开，中间添加k
        if(num1 == num2)
        {
            v.push_back(std::make_pair(num1,spk));
            v.push_back(std::make_pair(num2,spk));
        }
        else
        {
            v.push_back(std::make_pair(num1,num2));
        }
        i+=2;
    }

    // 将数字转换成对应的字母

    int vlen = v.size();
    for(int i = 0;i<vlen;i++)
    {
        std::pair<int,int> p = v[i];
        std::pair<int,int> local1 = getLocation(p.first),local2 = getLocation(p.second);

        if(local1.first == local2.first)
        {
            int new1 = getAlpha( std::make_pair( local1.first , (local1.second+1)%N ) );
            int new2 = getAlpha( std::make_pair( local2.first , (local2.second+1)%N ) );

            result.append(alphabet[new1]+alphabet[new2]);
        }
        else if(local1.second == local2.second)
        {
            int new1 = getAlpha( std::make_pair( (local1.first+1)%N , local1.second ) );
            int new2 = getAlpha( std::make_pair( (local2.first+1)%N , local2.second ) );

            result.append(alphabet[new1]+alphabet[new2]);
        }
        else
        {
            int new1 = getAlpha( std::make_pair(  local1.first , local2.second ) );
            int new2 = getAlpha( std::make_pair(  local2.first , local1.second ) );

            result.append(alphabet[new1]+alphabet[new2]);
        }
    }

    cipher = result;

    return true;
}

bool PlayfairCipher::decrypt(std::string cipher, std::string& plain)
{
    if(cipher.empty())
        return false;

    std::string result;

    std::vector<std::pair<int,int>> v;

    int len = cipher.size();
    for(int i = 0;i<len;i+=2)
    {
        int num1 = toupper(cipher[i]) - 'A';
        int num2 = toupper(cipher[i+1]) - 'A';

        if(num1 == spj)
            num1 = spi;
        if(num2 == spj)
            num2 = spi;

        v.push_back(std::make_pair(num1,num2));
    }

    int vlen = v.size();
    std::vector<std::pair<int,int>> v1;
    v1.clear();

    for(int i = 0;i<vlen;i++)
    {
        std::pair<int,int> p = v[i];

        std::pair<int,int> local1 = getLocation(p.first) , local2 = getLocation(p.second);

        if(local1.first == local2.first)
        {
            int new1 = getAlpha( std::make_pair( local1.first , (local1.second-1+N)%N ) );
            int new2 = getAlpha( std::make_pair( local2.first , (local2.second-1+N)%N ) );

            v1.push_back(std::make_pair(new1,new2));
        }
        else if(local1.second == local2.second)
        {
            int new1 = getAlpha( std::make_pair( (local1.first-1+N)%N , local1.second ) );
            int new2 = getAlpha( std::make_pair( (local2.first-1+N)%N , local2.second ) );

            v1.push_back(std::make_pair(new1,new2));
        }
        else
        {
            int new1 = getAlpha( std::make_pair(  local1.first , local2.second ) );
            int new2 = getAlpha( std::make_pair(  local2.first , local1.second ) );

            v1.push_back(std::make_pair(new1,new2));
        }
    }

    for(auto it = v1.begin();it + 1 < v1.end(); it++)
    {
        if(it->first == (it+1)->first && it->second == (it+1)->second && it->second == spk)
        {
            v1.erase(it,it+2);
            v1.insert(it,std::make_pair(it->first,it->first));
        }
    }

    for(int i=0;i<(int)v1.size();i++)
    {
        int x = v1[i].first, y = v1[i].second;
            result.append(alphabet[x]+alphabet[y]);
    }

    plain = result;

    return true;
}

void PlayfairCipher::updateMatrix()
{
    // 根据选定的单词更新加解密矩阵 I J 视为同一个
    bool yes[26];
    for(int i = 0;i<26;i++)
        yes[i] = false;

    have = 0;

    int len = word.size();
    for(int i=0;i<len;i++)
    {
        int num = toupper(word[i]) - 'A';

        if(num == spi || num == spj)
            num = spi;

        if(!yes[num])
        {
            int row = have / N , column = have % N;

            matrix[row][column] = num;

            if(num == spi)
            {
                yes[spi] = yes[spj] = true;
            }
            else
            {
                yes[num] = true;
            }

            have ++;
        }
    }

    for(int i = 0 ; i < 26 ;i++)
    {
        if(have >= 25)
            break;

        if(i == spj)
            continue;

        if(!yes[i])
        {
            int row = have / N , column = have % N;
            matrix[row][column] = i;
            yes[i] = true;

            have ++;
        }
    }
}

std::pair<int,int> PlayfairCipher::getLocation(int alpha)
{
    std::pair<int,int> ans;

    for(int i = 0;i<N;i++)
    {
        for(int j = 0;j<N;j++)
        {
            if(matrix[i][j] == alpha)
            {
                ans =  std::make_pair(i,j);
                goto END;
            }

        }
    }

END:
    return ans;
}

int PlayfairCipher::getAlpha(std::pair<int, int> location)
{
    int x = location.first,y = location.second;
    return matrix[x][y];
}

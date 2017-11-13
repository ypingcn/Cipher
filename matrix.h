#ifndef MATRIX_H
#define MATRIX_H

#include <QString>
#include <QDebug>

#include <vector>

class Matrix
{
public:
    static const int N = 3;
    static const int MOD = 26;

    Matrix(){}
    Matrix(int (*k)[N]);

    std::vector<int> operator*(std::vector<int> v);

    bool inverse(Matrix& result);

    void debug()
    {
        for(int i = 0;i<N;i++)
        {
            for(int j = 0;j<N;j++)
            {
                qDebug()<<"$$$  "<<QString::number(value[i][j]);
            }
        }
    }

private:

    int value[N][N];

    int getDet();
    int getDets(int (*ks)[N],int n);
    int getModInverse(int val);
    int gcd(int a,int b){ return b==0?a:gcd(b,a%b); }


};

#endif // MATRIX_H

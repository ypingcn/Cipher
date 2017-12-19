#ifndef MATRIX_H
#define MATRIX_H

#include <QString>
#include <QDebug>

#include <vector>

class Matrix
{
public:
    static const int N = 3; // 矩阵大小
    static const int MOD = 26;

    Matrix(){}
    Matrix(int (*k)[N]);

    std::vector<int> operator*(std::vector<int> v); // 重载乘号运算符，简化使用

    bool inverse(Matrix& result); // 求矩阵的逆

private:

    int value[N][N];

    int getDet(); // 求矩阵的行列式
    int getDets(int (*ks)[N],int n);
    int getModInverse(int val); // 求逆元
    int gcd(int a,int b){ return b==0?a:gcd(b,a%b); }


};

#endif // MATRIX_H

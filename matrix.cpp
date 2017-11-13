#include "matrix.h"

Matrix::Matrix(int (*k)[N])
{
    for(int i = 0 ;i<N;i++)
    {
        for(int j = 0;j<N;j++)
        {
            value[i][j] = k[i][j];
        }
    }
}

int Matrix::getDet()
{
    return getDets(value,N);
}

int Matrix::getDets(int (*ks)[N],int n)
{
    if(n == 1)
        return ks[0][0];

    int ans = 0 , tmp[N][N];

    for(int i = 0 ; i < N ; i ++)
        for(int j = 0 ; j < N ; j ++)
            tmp[i][j] = 0;

    for(int i = 0;i<n;i++)
    {
        for(int j = 0;j<n-1;j++)
            for(int k = 0;k<n-1;k++)
                tmp[j][k] = ks[j+1][(k>=i)?k+1:k];

        int t = getDets(tmp,n-1);

        if(i%2 == 0)
            ans += ks[0][i]*t;
        else
            ans -= ks[0][i]*t;
    }

    return ans;
}

int Matrix::getModInverse(int val)
{
    if( val == 0 || gcd(val,MOD) > 1)
        return -1;

    int ans = 1;
    while( (ans*val)%MOD != 1)
        ans++;

    return ans;
}

bool Matrix::inverse(Matrix& result)
{
    int det = (getDet()%26+26)%26;
    int rev = getModInverse(det);

//    qDebug()<<"det"<<QString::number(det);
//    qDebug()<<"rev"<<QString::number(rev);

    if(rev == -1)
        return false;

    int r[N][N];

    for(int i = 0;i<N;i++)
    {
        for(int j = 0;j<N;j++)
        {
            int tmp[N][N];

            for(int k = 0;k<N-1;k++)
                for(int t = 0;t<N-1;t++)
                    tmp[k][t] = value[k>=i?k+1:k][t>=j?t+1:t];

            r[j][i] = getDets(tmp,N-1);

//            qDebug()<<QString::number(i)<<QString::number(j)<<QString::number(r[i][j]);

            if((i+j)%2 == 1)
                r[j][i] = -r[j][i];

            r[j][i] = ((r[j][i]*rev)%26+26)%26;
        }
    }

    result = Matrix(r);
//    result.debug();

    return true;
}


std::vector<int> Matrix::operator *(std::vector<int> v)
{
    std::vector<int> result(N);
    for(int i = 0 ;i<N;i++)
    {
        int sum = 0;
        for(int j = 0;j<N;j++)
            sum += v[j]*value[i][j];
        result[i] = sum % MOD;
    }
    return result;
}

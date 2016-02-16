#include <iostream>
#include <QTime>
#include <cmath>

using namespace std;

int fib(int k)
{
    return k < 2? 1: fib(k-2) + fib(k-1);
}

void fib2(int k, int& ck, int& ck1)
{
    if(k<2)
        ck = ck1 = 1;
    else
    {
        fib2(k-1, ck1, ck);
        ck += ck1;
    }
}

int fib2a(int k)
{
    int ck, ck1;
    fib2(k, ck, ck1);
    return ck;
}

double limfib()
{
    const double tolerance = 1e-12;
    double r = 0;
    for (int k=1; ; ++k)
    {
        int ck, ck1;
        fib2(k, ck, ck1);
        double rk = double(ck) / ck1;
        if (fabs(r - rk) < tolerance)
            return rk;
        r = rk;
    }
}

// Returns square of x
double sqr(double x) { return x*x; }

// Computes real roots of polynomial
// with integer coefficients a, b, c
bool realRoots(
        int a, int b, int c,
        double& x1, double& x2)
{
    double b2a = b/(2.*a);
    double D = sqr(b2a) - double(c)/a;
    if (D < 0)
        return false;
    double d = sqrt(D);
    x1 = -b2a - d;
    x2 = -b2a + d;
    return true;
}

// Finds polynomial having x mong its roots
bool identify(double x, int& a, int& b, int& c)
{
    int N = 10;
    const double tolerance = 1e-10;
    for (a=-N; a<=N; ++a)
        for (b=-N; b<=N; ++b)
            for (c=-N; c<=N; ++c)
            {
                double x1, x2;
                if (realRoots(a, b, c, x1, x2))
                {
                    if (fabs(x1-x) < tolerance)
                        return true;
                    if (fabs(x2-x) < tolerance)
                        return true;
                }
            }
    return false;
}

int main()
{
    cout << limfib() << endl;
    int a, b, c;
    if (identify(limfib(), a, b, c))
        cout << a << endl << b << endl << c << endl;
    else
        cout << "Oh no..." << endl;
    return 0;
}


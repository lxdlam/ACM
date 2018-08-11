#include <bits/stdc++.h>

namespace FFT
{
typedef std::complex<double> Complex;
typedef std::vector<Complex> vc;

const double EPS = 0.5;

const int MaxL = 18, MaxN = 1 << MaxL;
vc eps(MaxN), inv_eps(MaxN);

void init_eps(int p)
{
    double pi = acos(-1);
    double angle = 2.0 * pi / p;
    for (int i = 0; i != p; i++)
    {
        eps[i] = Complex(cos(i * angle), sin(i * angle));
        inv_eps[i] = conj(eps[i]);
    }
}

void transform(int n, vc &x, const vc &w)
{
    for (int i = 0, j = 0; i != n; ++i)
    {
        if (i > j)
            swap(x[i], x[j]);
        for (int l = n >> 1; (j ^= l) < l; l >>= 1)
            ;
    }

    for (int i = 2; i <= n; i <<= 1)
    {
        int m = i >> 1;
        for (int j = 0; j < n; j += i)
        {
            for (int k = 0; k != m; ++k)
            {
                Complex z = x[j + m + k] * w[n / i * k];
                x[j + m + k] = x[j + k] - z;
                x[j + k] += z;
            }
        }
    }
}
} // namespace FFT

namespace NTT
{
typedef long long ll;
typedef std::vector<ll> vll;

/*
 * P = Rx2^K+1, G is pr
 * Three recommend choices:
 * p = 2281701377, r = 17, g = 3, k = 27
 * p = 1004535809, r = 479, g = 3, k = 21
 * p = 998244353, r = 119, g = 3, k = 23
 * For more, see NTT_table.md
 */
const int P = 998244353, R = 119, G = 3, K = 2;

inline ll fp(ll base, ll expr, ll mod = P)
{
    ll ans = 1;
    base %= mod;
    while (expr)
    {
        if (expr & 1LL)
            ans = (ans * base) % mod;
        base = (base * base) % mod;
        expr >>= 1LL;
    }
    return ans % mod;
}

inline ll add(ll n, ll m)
{
    n += m;
    if (n >= P)
        n -= P;
    return n;
}

inline ll sub(ll n, ll m)
{
    n -= m;
    if (n < 0)
        n += P;
    return n;
}

inline ll mul(ll n, ll m)
{
    return (n % P) * (m % P) % P;
}

inline ll div(ll n, ll m)
{
    ll inv = fp(m, P - 2);
    return mul(n, inv);
}

void transform(int n, vll &x, bool idft = false)
{
    for (int i = 0, j = 0; i != n; ++i)
    {
        if (i > j)
            swap(x[i], x[j]);
        for (int l = n >> 1; (j ^= l) < l; l >>= 1)
            ;
    }

    for (int i = 2; i <= n; i <<= 1)
    {
        int m = i >> 1;
        ll eps = fp(G, idft ? (P - 1) / i : P - 1 - (P - 1) / i, P);
        for (int j = 0; j < n; j += i)
        {
            ll t = 1;
            for (int k = 0; k != m; ++k)
            {
                ll z = mul(x[j + m + k], t);
                x[j + m + k] = sub(x[j + k], z);
                x[j + k] = add(x[j + k], z);
                t = mul(t, eps);
            }
        }
    }

    if (idft)
    {
        ll inv = fp(n, P - 2, P);
        for (int i = 0; i < n; i++)
            x[i] = mul(x[i], inv);
    }
}
} // namespace NTT
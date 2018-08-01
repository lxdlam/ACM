#include <bits/stdc++.h>

using namespace std;

#define TemplateVersion "3.2.0"
// Useful Marcos
//====================START=====================
// Compile use C++11 and above
#ifdef LOCAL
#define debug(args...)                           \
    {                                            \
        string _s = #args;                       \
        replace(_s.begin(), _s.end(), ',', ' '); \
        stringstream _ss(_s);                    \
        istream_iterator<string> _it(_ss);       \
        err(_it, args);                          \
    }
void err(istream_iterator<string> it)
{
}
template <typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args)
{
    cerr << *it << " = " << a << endl;
    err(++it, args...);
}
#define MSG cout << "Finished" << endl
#else
#define debug(args...)
#define MSG
#endif
#if __cplusplus >= 201703L
template <typename... Args>
void readln(Args &... args)
{
    ((cin >> args), ...);
}
template <typename... Args>
void writeln(Args... args)
{
    ((cout << args << " "), ...);
    cout << endl;
}
#elif __cplusplus >= 201103L
void readln()
{
}
template <typename T, typename... Args>
void readln(T &a, Args &... args)
{
    cin >> a;
    readln(args...);
}
void writeln()
{
    cout << endl;
}
template <typename T, typename... Args>
void writeln(T a, Args... args)
{
    cout << a << " ";
    writeln(args...);
}
#endif
#if __cplusplus >= 201103L
#define FOR(_i, _begin, _end) for (auto _i = _begin; _i < _end; _i++)
#define FORR(_i, _begin, _end) for (auto _i = _begin; _i > _end; _i--)
#else
#define FOR(_i, _begin, _end) for (int _i = (int)_begin; _i < (int)_end; _i++)
#define FORR(_i, _begin, _end) for (int _i = (int)_begin; _i > (int)_end; _i--)
#define nullptr NULL
#endif
#if __cplusplus >= 201103L
#define VIS(_kind, _name, _size) \
    vector<_kind> _name(_size);  \
    for (auto &i : _name)        \
        cin >> i;
#else
#define VIS(_kind, _name, _size)    \
    vector<_kind> _name;            \
    _name.resize(_size);            \
    for (int i = 0; i < _size; i++) \
        cin >> _name[i];
#endif
// alias
#define mp make_pair
#define pb push_back
#define eb emplace_back
// Swap max/min
template <typename T>
bool smax(T &a, const T &b)
{
    if (a > b)
        return false;
    a = b;
    return true;
}
template <typename T>
bool smin(T &a, const T &b)
{
    if (a < b)
        return false;
    a = b;
    return true;
}
// ceil divide
template <typename T>
T cd(T a, T b)
{
    return (a + b - 1) / b;
}
// min exchange
template <typename T>
bool se(T &a, T &b)
{
    if (a < b)
        return false;
    swap(a, b);
    return true;
}
// A better MAX choice
const int INF = 0x3f3f3f3f;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef set<int> si;
typedef vector<string> cb;
//====================END=====================

// Constants here
const int SIZE = 1e5 + 10;
map<ll, ll> t;

ll num[SIZE];

ll Mod(ll n, ll m)
{
    return n < m ? n : (n % m + m);
}

ll Phi(ll n)
{
    ll k = n;
    if (!t[n])
    {
        ll phi = n;
        for (ll i = 2; i * i <= n; i++)
        {
            if (n % i == 0)
            {
                phi /= i;
                phi *= i - 1;
                while (n % i == 0)
                    n /= i;
            }
        }
        if (n != 1)
        {
            phi /= n;
            phi *= n - 1;
        }
        t[k] = phi;
    }
    return t[k];
}

ll fp(ll base, ll expr, ll mod = 1e9 + 7)
{
    ll ans = 1;
    while (expr)
    {
        if (expr & 1LL)
            ans = Mod(ans * base, mod);
        base = Mod(base * base, mod);
        expr >>= 1LL;
    }
    return Mod(ans, mod);
}

ll work(int l, int r, ll m)
{
    if (l == r || m == 1)
        return Mod(num[l], m);
    return fp(num[l], work(l + 1, r, Phi(m)), m);
}

// Pre-Build Function
inline void build()
{
}

// Actual Solver
inline void solve()
{
    int n;
    ll m;
    // scanf("%d%lld", &n, &m);
    readln(n, m);
    FOR(i, 1, n + 1)
    // scanf("%lld", &num[i]);
    cin >> num[i];
    int q;
    int l, r;
    // scanf("%d", &q);
    cin >> q;
    while (q--)
    {
        // scanf("%d%d", &l, &r);
        readln(l, r);
        // printf("%lld\n", work(l, r, m) % m);
        cout << work(l, r, m) % m << '\n';
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

#ifdef LOCAL
    clock_t _begin = clock();
#endif

    build();
    solve();

#ifdef LOCAL
    cerr << "Time elapsed: " << (double)(clock() - _begin) * 1000 / CLOCKS_PER_SEC << "ms." << endl;
#endif

    return 0;
}
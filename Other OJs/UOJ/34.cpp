#include <bits/stdc++.h>

using namespace std;

#define TemplateVersion "3.2.0"
// Useful Marcos
//====================START=====================
// Compile use C++11 and above
#ifdef LOCAL
#define debug(args...)                       \
  {                                          \
    string _s = #args;                       \
    replace(_s.begin(), _s.end(), ',', ' '); \
    stringstream _ss(_s);                    \
    istream_iterator<string> _it(_ss);       \
    err(_it, args);                          \
  }
void err(istream_iterator<string> it) {}
template <typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
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
void readln(Args &... args) {
  ((cin >> args), ...);
}
template <typename... Args>
void writeln(Args... args) {
  ((cout << args << " "), ...);
  cout << endl;
}
#elif __cplusplus >= 201103L
void readln() {}
template <typename T, typename... Args>
void readln(T &a, Args &... args) {
  cin >> a;
  readln(args...);
}
void writeln() { cout << endl; }
template <typename T, typename... Args>
void writeln(T a, Args... args) {
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
  vector<_kind> _name(_size);    \
  for (auto &i : _name) cin >> i;
#else
#define VIS(_kind, _name, _size) \
  vector<_kind> _name;           \
  _name.resize(_size);           \
  for (int i = 0; i < _size; i++) cin >> _name[i];
#endif
// alias
#define mp make_pair
#define pb push_back
#define eb emplace_back
// Swap max/min
template <typename T>
bool smax(T &a, const T &b) {
  if (a > b) return false;
  a = b;
  return true;
}
template <typename T>
bool smin(T &a, const T &b) {
  if (a < b) return false;
  a = b;
  return true;
}
// ceil divide
template <typename T>
T cd(T a, T b) {
  return (a + b - 1) / b;
}
// min exchange
template <typename T>
bool se(T &a, T &b) {
  if (a < b) return false;
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
namespace FFT {
typedef std::complex<double> Complex;
typedef std::vector<Complex> vc;

const double EPS = 0.5;

const int MaxL = 18, MaxN = 1 << MaxL;
vc eps(MaxN), inv_eps(MaxN);

void init_eps(int p) {
  double pi = acos(-1);
  double angle = 2.0 * pi / p;
  for (int i = 0; i != p; i++) {
    eps[i] = Complex(cos(i * angle), sin(i * angle));
    inv_eps[i] = conj(eps[i]);
  }
}

void transform(int n, vc &x, const vc &w) {
  for (int i = 0, j = 0; i != n; ++i) {
    if (i > j) swap(x[i], x[j]);
    for (int l = n >> 1; (j ^= l) < l; l >>= 1)
      ;
  }

  for (int i = 2; i <= n; i <<= 1) {
    int m = i >> 1;
    for (int j = 0; j < n; j += i) {
      for (int k = 0; k != m; ++k) {
        Complex z = x[j + m + k] * w[n / i * k];
        x[j + m + k] = x[j + k] - z;
        x[j + k] += z;
      }
    }
  }
}
}  // namespace FFT

// Pre-Build Function
inline void build() {}

// Actual Solver
inline void solve() {
  int n, m;
  cin >> n >> m;

  int p = 1;
  while (p < n + m + 1) p <<= 1;

  FFT::init_eps(p);
  FFT::vc f(p), g(p);
  for (int i = 0; i < n + 1; i++) cin >> f[i];
  for (int i = 0; i < m + 1; i++) cin >> g[i];

  FFT::transform(p, f, FFT::eps);
  FFT::transform(p, g, FFT::eps);

  for (int i = 0; i < p; i++) f[i] *= g[i];

  FFT::transform(p, f, FFT::inv_eps);

  for (int i = 0; i < n + m + 1; i++)
    cout << (int)(f[i].real() / p + FFT::EPS) << ' ';
  cout << endl;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

#ifdef LOCAL
  clock_t _begin = clock();
#endif

  build();
  solve();

#ifdef LOCAL
  cerr << "Time elapsed: " << (double)(clock() - _begin) * 1000 / CLOCKS_PER_SEC
       << "ms." << endl;
#endif

  return 0;
}
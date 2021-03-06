#include <bits/stdc++.h>

using namespace std;

#define TemplateVersion "3.7.1"
// Useful Marcos
//====================START=====================
// Compile use C++11 and above
#ifdef LOCAL
#define debug(args...)                       \
  do {                                       \
    string _s = #args;                       \
    replace(_s.begin(), _s.end(), ',', ' '); \
    stringstream _ss(_s);                    \
    istream_iterator<string> _it(_ss);       \
    err(_it, args);                          \
  } while (0)
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
void readln(Args&... args) {
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
void readln(T& a, Args&... args) {
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
  for (auto& i : _name) cin >> i;
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
#define all(x) (x).begin(), (x).end()
#define clr(x) memset((x), 0, sizeof(x))
#define infty(x) memset((x), 0x3f, sizeof(x))
#define tcase() \
  int T;        \
  cin >> T;     \
  FOR(kase, 1, T + 1)

// Swap max/min
template <typename T>
bool smax(T& a, const T& b) {
  if (a > b) return false;
  a = b;
  return true;
}
template <typename T>
bool smin(T& a, const T& b) {
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
bool se(T& a, T& b) {
  if (a < b) return false;
  swap(a, b);
  return true;
}
// A better MAX choice
const int INF = 0x3f3f3f3f;
const long long INFLL = 0x3f3f3f3f3f3f3f3fLL;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef set<int> si;
typedef vector<string> cb;
//====================END=====================

// Constants here
const int BASE = 1e6;
const int SIZE = 2e6 + 10;

int num[SIZE];

struct Line {
  ll a, b;

  // how the line evaluates
  ll eval(ll x) { return a * a + b - 2 * a * x + 2 * a * BASE; };
};

// Based on https://cp-algorithms.com/geometry/convex_hull_trick.html
struct LiChaoTree {
  // here, size is the maximum point coordinate
  // i.e., maximum possible x
  Line tr[SIZE << 2];

  // fill with the starting line
  void init(Line l) { fill(tr, tr + (SIZE << 2), l); }

  // in below functions
  // the initial call must using
  // the maximum possible x
  // as argument r
  // NOT THE SIZE OF THE TREE!

  void add(Line li, int l, int r, int cur) {
    int m = (l + r) >> 1;

    // change the behavior here to maintain maximum or minimum
    bool le = li.eval(l) < tr[cur].eval(l);
    bool mid = li.eval(m) < tr[cur].eval(m);

    if (mid) swap(tr[cur], li);
    if (l == r)
      return;
    else if (le != mid)
      add(li, l, m, cur << 1);
    else
      add(li, m + 1, r, cur << 1 | 1);
  }

  ll query(int pos, int l, int r, int cur) {
    if (l == r) return tr[cur].eval(pos);

    int m = (l + r) >> 1;

    // change the behavior here to query maximum or minimum
    if (pos < m)
      return min(tr[cur].eval(pos), query(pos, l, m, cur << 1));
    else
      return min(tr[cur].eval(pos), query(pos, m + 1, r, cur << 1 | 1));
  }
} LCT;

// Pre-Build Function
inline void build() {}

// Actual Solver
inline void solve() {
  int n;
  scanf("%d", &n);

  for (int i = 0; i < n; i++) scanf("%d", &num[i]);

  ll t;
  scanf("%lld", &t);

  LCT.init({num[0], t});

  for (int i = 1; i < n; i++) {
    scanf("%lld", &t);
    LCT.add({num[i], t}, 1, SIZE, 1);
  }

  int q;
  scanf("%d", &q);

  while (q--) {
    scanf("%lld", &t);
    printf("%lld ", t * t + LCT.query(t + BASE, 1, SIZE, 1));
  }
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
  cerr << "Time elapsed: " << (double)(clock() - _begin) * 1000 / CLOCKS_PER_SEC << "ms." << endl;
#endif

  return 0;
}
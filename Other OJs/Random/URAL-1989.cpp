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

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef set<int> si;
typedef vector<string> cb;
//====================END=====================

// Constants here
const ll MOD = 1e9 + 7;
const int SIZE = 1e5 + 10;

ull ps[SIZE] = {1};

template <typename T>
class FenTree {
private:
  vector<T> v;
  size_t size;

  inline int lowbit(int k) { return k & -k; }

public:
  void init(size_t size) {
    this->size = size + 1;
    v.clear();
    v.resize(size + 1);
  }

  void update(int pos, T val) {
    while (pos < size) {
      v[pos] = v[pos] + val;
      pos += lowbit(pos);
    }
  }

  T get(int pos) {
    T res = 0;
    while (pos) {
      res = res + v[pos];
      pos -= lowbit(pos);
    }
    return res;
  }

  T getSeg(int l, int r) { return get(r) - get(l - 1); }
};

// Pre-Build Function
inline void build() {
  FOR(i, 1, SIZE)
  ps[i] = ps[i - 1] * 27;
}

// Actual Solver
inline void solve() {
  string s, op;
  cin >> s;
  FenTree<ull> sf, rv;
  int len = s.size();
  sf.init(len + 1);
  rv.init(len + 1);
  FOR(i, 0, len) {
    sf.update(i + 1, (s[i] - 'a' + 1) * ps[i]);
    rv.update(i + 1, (s[i] - 'a' + 1) * ps[len - i - 1]);
  }
  int n, l, r;
  char ch;
  cin >> n;
  while (n--) {
    cin >> op;
    if (op == "palindrome?") {
      cin >> l >> r;
      ull ans1 = sf.getSeg(l, r) * ps[len - r];
      ull ans2 = rv.getSeg(l, r) * ps[l - 1];
      if (ans1 == ans2)
        cout << "Yes" << endl;
      else
        cout << "No" << endl;
    } else {
      cin >> l >> ch;
      sf.update(l, (ch - s[l - 1]) * ps[l - 1]);
      rv.update(l, (ch - s[l - 1]) * ps[len - l]);
      s[l - 1] = ch;
    }
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
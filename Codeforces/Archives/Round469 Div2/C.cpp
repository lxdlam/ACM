#include <bits/stdc++.h>

using namespace std;

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
#define FOR(_i, _begin, _end) \
  for (auto _i = _begin - (_begin > _end); _i != _end - (_begin > _end); _i += 1 - 2 * (_begin > _end))
#define FORE(_i, _c) for (auto _i : _c)
#define FORER(_i, _c) for (auto& _i : _c)
#else
#define FOR(_i, _begin, _end) \
  for (__typeof(_end) _i = _begin - (_begin > _end); _i != _end - (_begin > _end); _i += 1 - 2 * (_begin > _end))
#define FORE(_i, _c)
#define FORER(_i, _c)
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
//====================END=====================

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef set<int> si;

// Constants here

// Pre-Build Function
void build() {}

// Actual Solver
void solve() {
  string s;
  cin >> s;
  si z, o;

  FOR(i, 0, s.size()) {
    if (s[i] == '1')
      o.insert(i);
    else
      z.insert(i);
    if (z.size() < o.size()) {
      cout << -1 << endl;
      return;
    }
  }

  vector<vi> ans;
  FOR(i, 0, s.size()) {
    if (s[i] == '.' || s[i] == '1') continue;
    vi v;
    ans.push_back(v);
    ans.back().push_back(i);

    while (true) {
      // find 1
      auto oi = o.upper_bound(ans.back().back());
      if (oi == o.end()) break;
      s[*oi] = '.';
      ans.back().push_back(*oi);
      o.erase(*oi);

      // find 0
      auto zi = z.upper_bound(ans.back().back());
      if (zi == z.end()) {
        cout << -1 << endl;
        return;
      }
      s[*zi] = '.';
      ans.back().push_back(*zi);
      z.erase(*zi);
    }
  }
  if (ans.empty()) {
    cout << -1 << endl;
    return;
  }
  cout << ans.size() << endl;
  for (auto i : ans) {
    cout << i.size() << " ";
    for (auto j : i) cout << j + 1 << " ";
    cout << endl;
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
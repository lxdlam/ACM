#include <bits/stdc++.h>

// Useful Marcos
//====================START=====================
#define FOR(_i, _s, _e) for (int _i = _s; _i < _e; _i++)
#ifdef LOCAL
#define debug1(_a) cout << #_a << ": " << _a << endl
#define debug2(_a, _b) cout << #_a << ": " << _a << " " << #_b << ": " << _b << " " << endl
#define debug3(_a, _b, _c) \
  cout << #_a << ": " << _a << " " << #_b << ": " << _b << " " << #_c << ": " << _c << " " << endl
#define debug4(_a, _b, _c, _d)                                                                                         \
  cout << #_a << ": " << _a << " " << #_b << ": " << _b << " " << #_c << ": " << _c << " " << #_d << ": " << _d << " " \
       << endl
#else
#define debug1(_a)
#define debug2(_a, _b)
#define debug3(_a, _b, _c)
#define debug4(_a, _b, _c, _d)
#endif
#if __cpluscplus > 201103L
#define FORE(_c) for (auto i : _c)
#define FORER(_c) for (auto& i : _c)
#else
#define FORE(_c)
#define FORER(_c)
#define nullptr NULL
#endif
#if __cplusplus > 201402L
#define VIS(_kind, _name, _size) \
  vector<_kind> _name(_size);    \
  for (auto& i : v) cin >> i;
#elif __cpluscplus > 201103L
#define VIS(_kind, _name, _size) \
  vector<_kind> _name;           \
  _name.resize(_size);           \
  for (auto& i : v) cin >> i;
#else
#define VIS(_kind, _name, _size) \
  vector<_kind> _name;           \
  _name.resize(_size);           \
  for (int i = 0; i < _size; i++) cin >> v[i];
#endif
//====================END=====================

using namespace std;

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
  int t;
  int n, k;
  cin >> t;
  while (t--) {
    cin >> n >> k;
    VIS(int, v, k);
    int d = 0;
    FOR(i, 0, k - 1) { d = max(v[i + 1] - v[i], d); }
    if (v[0] != 1) d = max(2 * (v[0] - 1), d);
    if (v.back() != n) d = max(2 * (n - v.back()), d);
    cout << d / 2 + 1 << endl;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);

#ifdef LOCAL
  clock_t begin = clock();
#endif

  build();
  solve();

#ifdef LOCAL
  cout << "Runtime: " << (double)(clock() - begin) * 1000 / CLOCKS_PER_SEC << "ms." << endl;
#endif

  return 0;
}